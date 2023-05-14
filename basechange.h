#ifndef BASECHANGE_H
#define BASECHANGE_H

#include <QWidget>

namespace Ui {
class baseChange;
}

class baseChange : public QWidget
{
    Q_OBJECT

public:
    explicit baseChange(QWidget *parent = nullptr);
    ~baseChange();
    void baseRadioChanged(QString io, QString base);
    void changeBtnPushed();

private:
    Ui::baseChange *ui;
};

#endif // BASECHANGE_H
