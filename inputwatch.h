#ifndef INPUTWATCH_H
#define INPUTWATCH_H

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

    int variableValue = 0;
};

#endif // INPUTWATCH_H
