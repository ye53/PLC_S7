#include "basechange.h"
#include "ui_basechange.h"
#include <QMessageBox>

QString inputBase;
QString outputBase;

baseChange::baseChange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::baseChange)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/actions/stock_about.png"));
    connect(ui->binI,&QRadioButton::clicked,this,[=]{baseChange::baseRadioChanged("I","bin");});
    connect(ui->octI,&QRadioButton::clicked,this,[=]{baseChange::baseRadioChanged("I","oct");});
    connect(ui->decI,&QRadioButton::clicked,this,[=]{baseChange::baseRadioChanged("I","dec");});
    connect(ui->hexI,&QRadioButton::clicked,this,[=]{baseChange::baseRadioChanged("I","hex");});
    connect(ui->binO,&QRadioButton::clicked,this,[=]{baseChange::baseRadioChanged("O","bin");});
    connect(ui->octO,&QRadioButton::clicked,this,[=]{baseChange::baseRadioChanged("O","oct");});
    connect(ui->decO,&QRadioButton::clicked,this,[=]{baseChange::baseRadioChanged("O","dec");});
    connect(ui->hexO,&QRadioButton::clicked,this,[=]{baseChange::baseRadioChanged("O","hex");});
    connect(ui->btnChange,&QPushButton::clicked,this,[=]{baseChange::changeBtnPushed();});
}

void baseChange::baseRadioChanged(QString io, QString base)
{
    if(io == "I"){
        inputBase = base;
    }
    else{
        outputBase = base;
    }
}

void baseChange::changeBtnPushed()
{
    ui->outputText->setText("");
    int number;
    int base;
    QString result;
    bool isChangeSuccessful;
    if(inputBase == "bin"){
        base = 2;
    }
    else if(inputBase == "oct"){
        base = 8;
    }
    else if(inputBase == "dec"){
        base = 10;
    }
    else{
        base = 16;
    }
    number = ui->inputText->text().toInt(&isChangeSuccessful,base);
    if(isChangeSuccessful){
        if(outputBase == "bin"){
            result = QString("%1").arg(number,0,2);
        }
        else if(outputBase == "oct"){
            result = QString("%1").arg(number,0,8);
        }
        else if(outputBase == "dec"){
            result = QString("%1").arg(number,0,10);
        }
        else{
            result = QString("%1").arg(number,0,16);
        }
        ui->outputText->setText(result);
    }
    else{
        QMessageBox::information(NULL,"提示","请输入正确的数字");
    }
}

baseChange::~baseChange()
{
    delete ui;
}
