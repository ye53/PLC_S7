#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCharts>
#include <QMainWindow>
#include <snap7.h>
#include <QWidget>
#include <QStackedWidget>
#include <QTimer>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include "login.h"
#include <QSystemTrayIcon>
#include "sqlite.h"
#include "myworker.h"

QT_BEGIN_NAMESPACE
using namespace QtCharts;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    TS7Client *client=new TS7Client();
    byte buff_M[10] = {0};
    byte buff_V[10] = {0};
    byte buff_Q[10] = {0};
    ushort freq;
    QChart* chart ;
    QLineSeries *series;
    quint32 counter;
    sqlite *sql = new sqlite();

    //托盘相关
    QSystemTrayIcon *trayIcon;
    QAction *tray_hide;
    QAction *tray_show;
    QAction *tray_exit;
    QMenu *trayIconMenu;

    void executeFunction(int num);
    void Output0();
    void Output1();
    void Output2();
    void Output3();
    void Output4();
    void Output5();
    void Output6();
    void Output7();
    void Output8();
    void Output9();

private slots:
    void on_connect_clicked();

    void on_disconnect_clicked();

    void on_pushButton_3_clicked();

    void slotBtnClear();

    void slotBtnStartAndStop();

    void slotTimeout();

    void activatedSystemIcon(QSystemTrayIcon::ActivationReason reason);

    void CreatSystemTray();

    void Creatcurve();

    void on_pushButton_14_clicked();

    void on_FW_run_clicked();

    void on_stop_clicked();

    void on_RW_run_clicked();

    void on_Freq_set_clicked();

    void on_action_4_triggered();

    void on_action_11_triggered();

    void on_action_18_triggered();

    void on_actionASCII_triggered();

    void on_pushButton_17_clicked();

    void on_put_list_clicked();

    void handleWorkFinished(int num, int state);


private:
    Ui::MainWindow *ui;
    /* 用于模拟生成实时数据的定时器 */
    QTimer* m_timer;

    /* 图表对象 */
    QChart* m_chart;

    /* 横纵坐标轴对象 */
    QValueAxis *m_axisX, *m_axisY;

    /* 曲线图对象 */
    QLineSeries* m_lineSeries;

    /* 横纵坐标最大显示范围 */
    const int AXIS_MAX_X = 5, AXIS_MAX_Y = 20;

    /* 用来记录数据点数 */
    int pointCount = 0;

    QThreadPool m_threadPool;
            int index=0;
};


#endif // MAINWINDOW_H
