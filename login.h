#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMouseEvent>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
    void wheelEvent(QWheelEvent *event);

private slots:
      void slot_ScroolWidget(int);
};

#endif // LOGIN_H
