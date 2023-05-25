#include "rpmmeasurewidget.h"
#include <QtSql>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimer>
#include <cmath>

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
    query.exec("SELECT speed, data_update FROM Inverter_running_status ORDER BY id DESC LIMIT 5");

    QList<double> speeds;
    QDateTime lastUpdateTime;
    while (query.next()) {
        // 添加到速度列表中
        double speed = query.value(0).toDouble();
        speeds.append(speed);
        QString updateTime = query.value(1).toString();
        m_textEditSpeeds->append(QString("转速：%1，时间：%2").arg(speed).arg(updateTime));
        if (lastUpdateTime.isNull()) {
            lastUpdateTime = QDateTime::fromString(updateTime, "yyyy-MM-dd hh:mm:ss");
        }
    }

    // 计算标准差
    double sum = 0;
    for (double speed : speeds) {
        sum += speed;
    }
    double mean = sum / speeds.size();

    double squaredDiffSum = 0;
    for (double speed : speeds) {
        squaredDiffSum += std::pow(speed - mean, 2);
    }
    double variance = squaredDiffSum / speeds.size();
    double standardDeviation = std::sqrt(variance);

    // 判断转速稳定性
    if (standardDeviation < 0.1 * mean) {
        m_labelStable->setText("转速稳定");
        emit handleSteady(true);
    } else {
        m_labelStable->setText("转速异常");
    }


    // 显示当前转速
    m_labelCurrentSpeed->setText(QString::number(speeds.first()));


    // 清空速度列表
    m_textEditSpeeds->clear();
    for (double speed : speeds) {
        m_textEditSpeeds->append(QString::number(speed));
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
