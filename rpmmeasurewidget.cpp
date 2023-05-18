#include "rpmmeasurewidget.h"
#include <QtSql>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimer>

RpmMeasureWidget::RpmMeasureWidget(QWidget *parent) : QWidget(parent)
{
    // 创建控件
    m_labelCurrentSpeed = new QLabel;
    m_labelCurrentSpeed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_lineEditInterval = new QLineEdit;
    m_lineEditBaseSpeed = new QLineEdit;
    m_textEditSpeeds = new QTextEdit;
    m_labelStable = new QLabel;
    m_labelStable->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_btnStart = new QPushButton("开始测量");
    connect(m_btnStart, &QPushButton::clicked, this, &RpmMeasureWidget::startMeasure);
    m_btnEnd = new QPushButton("结束测量");
    connect(m_btnEnd, &QPushButton::clicked, this, &RpmMeasureWidget::endMeasure);

    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("当前转速："));
    layout->addWidget(m_labelCurrentSpeed);
    layout->addWidget(new QLabel("测量间隔（秒）："));
    layout->addWidget(m_lineEditInterval);
    layout->addWidget(new QLabel("基础转速（Hz）："));
    layout->addWidget(m_lineEditBaseSpeed);
    layout->addWidget(m_btnStart);
    layout->addWidget(m_btnEnd);
    layout->addWidget(new QLabel("最新5次转速："));
    layout->addWidget(m_textEditSpeeds);
    layout->addWidget(m_labelStable);

    // 设置布局
    setLayout(layout);

    // 创建定时器
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &RpmMeasureWidget::measure);
}

void RpmMeasureWidget::startMeasure()
{
    // 设置最新5次转速为只读
    m_textEditSpeeds->setReadOnly(true);

    // 启用结束按钮，禁用开始按钮
    m_btnEnd->setEnabled(true);
    m_btnStart->setEnabled(false);

    // 启动定时器
    m_timer->start(m_lineEditInterval->text().toInt() * 1000);
}

void RpmMeasureWidget::measure()
{
    // 从输入框中读取测量间隔和基础转速
    int interval = m_lineEditInterval->text().toInt();
    double baseSpeed = m_lineEditBaseSpeed->text().toDouble();

    // 读取最新的转速数据
    QSqlQuery query;
    query.exec("SELECT speed FROM speed ORDER BY id DESC LIMIT 1");

    if (query.next()) {
        // 添加到速度列表中
        double speed = query.value(0).toDouble();
        m_speeds.prepend(speed);
        if (m_speeds.size() > 5) {
            m_speeds.removeLast();
        }

        // 计算平均值和误差
        double average = 0;
        for (double speed : m_speeds) {
            average += speed;
        }
        average /= m_speeds.size();

        // 如果平均值大于基础转速的10%，则调整转速
        if (average > baseSpeed * 1.1) {
            // 执行调速操作
        }

        double error = 0;
        for (double speed : m_speeds) {
            error += qAbs(speed - average) / average;
        }
        error *= 100 / m_speeds.size();

        // 显示当前转速
        m_labelCurrentSpeed->setText(QString::number(speed));

        // 显示最新5次转速
        m_textEditSpeeds->clear();
        for (double speed : m_speeds) {
            m_textEditSpeeds->append(QString::number(speed));
        }

        // 显示转速稳定
        if (m_speeds.size() == 5 && error < 10) {
            m_labelStable->setText("转速稳定");
            m_timer->stop();

            // 隐藏速度列表和稳定标签
            m_textEditSpeeds->setVisible(false);
            m_labelStable->setVisible(false);
        }
    }
}

void RpmMeasureWidget::endMeasure()
{
    // 停止定时器
    m_timer->stop();

    // 启用开始按钮，禁用结束按钮
    m_btnStart->setEnabled(true);
    m_btnEnd->setEnabled(false);

    // 清空速度列表和稳定标签
    m_speeds.clear();
    m_textEditSpeeds->clear();
    m_labelStable->setText("");

    // 显示速度列表和稳定标签
    m_textEditSpeeds->setVisible(true);
    m_labelStable->setVisible(true);
}
