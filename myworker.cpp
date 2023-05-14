#include "myworker.h"
#include <QThread>

MyWorker::MyWorker(int num, QObject *parent) : QObject(parent), m_num(num)
{

}

void MyWorker::run()
{
    QEventLoop eventLoop;

    // 创建定时器对象
    QTimer timer;
    connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);

    // 启动定时器并等待
    timer.start(1500);
    eventLoop.exec();

    // 定时器超时后发送信号
    QThread::msleep(2000 + m_num * 2000);
    emit workFinished(m_num, 1);
    QThread::msleep(1000);
    emit workFinished(m_num, 0);
}


