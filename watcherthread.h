#ifndef WATCHERTHREAD_H
#define WATCHERTHREAD_H

#include <QThread>

class WatcherThread : public QThread
{
    Q_OBJECT

public:
    WatcherThread(QObject *parent = nullptr) : QThread(parent) {}

signals:
    void variableChanged(int newValue);

protected:
    void run() override;

private:
    int getVariableValue();

    int variableValue;
};

#endif // WATCHERTHREAD_H
