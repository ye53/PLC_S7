#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>
#include <QRunnable>
#include <QPair>
#include <QTimer>
#include <QEventLoop>
class MyWorker : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit MyWorker(int num, QObject *parent = nullptr);

signals:
    void workFinished(int num, int state);

protected:
    void run() override;

private:
    int m_num;


};

#endif // MYWORKER_H
