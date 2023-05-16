#ifndef INPUTMONITOR_H
#define INPUTMONITOR_H

#include <QObject>
#include <QThread>
class InputMonitor : public QObject
{
    Q_OBJECT
public:
    explicit InputMonitor(QObject *parent = nullptr);

signals:
    void variableChanged(int newValue);
};

#endif // INPUTMONITOR_H
