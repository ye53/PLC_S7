#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->verticalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(slot_ScroolWidget(int)));

}

Login::~Login()
{
    delete ui;
}

void Login::slot_ScroolWidget(int value)
{
    double p=static_cast<double>(value)/static_cast<double>(ui->verticalScrollBar->maximum());
    ui->label->move(0,-(ui->label->height()-350)*p);
}

void Login::wheelEvent(QWheelEvent *event)
{
    int para=event->angleDelta().y();//获得鼠标滚轮的滚动距离para，para<0向下滚动，>0向上滚动
    if (para<0)
    {
        //向下滚动，设定鼠标滚轮每滚动一个单位，滑块就移动20个单位
        //加入此判断的理由是，若当时滑块处于90的位置上，一旦继续下滑20个单位，就会超过最大范围100，show界面就会移动超出范围。
        if (ui->verticalScrollBar->value()+20<=100)
        {
            //发射verticalScrollBar的信号valueChange（value+20），连接到了我们之前写的slot_ScrollWidget(int)槽上
            emit ui->verticalScrollBar->valueChanged(ui->verticalScrollBar->value()+20);
            //设定滚动之后的滑块位置
            ui->verticalScrollBar->setSliderPosition(ui->verticalScrollBar->value()+20);
        }
        else
        {
            emit ui->verticalScrollBar->valueChanged(ui->verticalScrollBar->maximum());
            ui->verticalScrollBar->setSliderPosition(ui->verticalScrollBar->maximum());
        }
    }
    else
    {
        //向上滚动
        if (ui->verticalScrollBar->value()-20>=0)
        {
            emit ui->verticalScrollBar->valueChanged(ui->verticalScrollBar->value()-20);
            ui->verticalScrollBar->setSliderPosition(ui->verticalScrollBar->value()-20);
        }
        else
        {
            emit ui->verticalScrollBar->valueChanged(ui->verticalScrollBar->minimum());
            ui->verticalScrollBar->setSliderPosition(ui->verticalScrollBar->minimum());
        }
    }
}
