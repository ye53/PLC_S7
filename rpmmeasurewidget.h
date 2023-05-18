#ifndef RPMMESUREWIDGET_H
#define RPMMESUREWIDGET_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTextEdit;
class QTimer;
QT_END_NAMESPACE

class RpmMeasureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RpmMeasureWidget(QWidget *parent = nullptr);

private:
    QLabel *m_labelCurrentSpeed;
    QLineEdit *m_lineEditInterval;
    QLineEdit *m_lineEditBaseSpeed;
    QTextEdit *m_textEditSpeeds;
    QLabel *m_labelStable;
    QPushButton *m_btnStart;
    QPushButton *m_btnEnd; // 新增
    QTimer *m_timer;
    QList<double> m_speeds;

    void startMeasure();
    void measure();
    void endMeasure(); // 新增
};

#endif // RPMMESUREWIDGET_H
