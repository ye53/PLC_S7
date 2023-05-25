#include "sqlite.h"

sqlite::sqlite()
{
    qDebug()<<QSqlDatabase::drivers();//打印驱动列表

    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if(db.open()){
        qDebug()<<"open success";
    }
}

sqlite::~sqlite()
{
    db.close();
}

void sqlite::CreateTable()
{
    QSqlQuery sql_query(db);

    const QString sql=R"(
                      CREATE TABLE IF NOT EXISTS  Motor_switch_status (
                      id   INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,
                      status VERCHAR (50)  NOT NULL,
                      data_update VERCHAR(50)
                      );)";
    sql_query.exec(sql);

    const QString sql1=R"(
                      CREATE TABLE IF NOT EXISTS  IP_address (
                      id   INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,
                      address VERCHAR (50)  NOT NULL,
                      data_update VERCHAR(50)
                      );)";
    sql_query.exec(sql1);

    const QString sql2=R"(
                      CREATE TABLE IF NOT EXISTS  Inverter_running_status (
                      id   INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,
                      status VERCHAR (50)  NOT NULL,
                      speed FLOAT,
                      data_update VERCHAR(50)
                      );)";
    sql_query.exec(sql2);

    const QString sql3=R"(
                      CREATE TABLE IF NOT EXISTS  Inverter_running_frequency (
                      id   INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,
                      frequency FLOAT,
                      data_update VERCHAR(50)
                      );)";
    sql_query.exec(sql3);

    const QString sql4=R"(
                      CREATE TABLE IF NOT EXISTS  Sort_mod (
                      id   INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,
                      mod VERCHAR(50),
                      data_update VERCHAR(50)
                      );)";
    sql_query.exec(sql4);
}

void sqlite::InsertMotorTable(QString status)
{

    QSqlQuery query;
    QString dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    query.exec(QString(R"(INSERT INTO Motor_switch_status(id,status,data_update) VALUES(NULL,'%1','%2');)").arg(status).arg(dataTime));

}

void sqlite::InsertIpTable(QString ip)
{
    QSqlQuery query;
    QString dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    query.exec(QString(R"(INSERT INTO IP_address(id,address,data_update) VALUES(NULL,'%1','%2');)").arg(ip).arg(dataTime));
}

void sqlite::InsertInverterTable(QString status, int speed)
{
    QSqlQuery query;
    QString data = QString("%1").arg(speed);
    QString dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    query.exec(QString(R"(INSERT INTO Inverter_running_status(id,status,speed,data_update) VALUES(NULL,'%1','%2','%3');)").arg(status).arg(data).arg(dataTime));
}

void sqlite::InsertFrequencyTable(float freq)
{
    QSqlQuery query;
    QString data = QString("%1").arg(freq);
    QString dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    query.exec(QString(R"(INSERT INTO Inverter_running_frequency(id,frequency,data_update) VALUES(NULL,'%1','%2');)").arg(data).arg(dataTime));
}

void sqlite::InsertSortTable(QString mod)
{
    QSqlQuery query;
    QString dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    query.exec(QString(R"(INSERT INTO Sort_mod(id,address,data_update) VALUES(NULL,'%1','%2');)").arg(mod).arg(dataTime));
}

void sqlite::InsertTest()
{
//    QSqlQuery query;
//    QString dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//    query.exec(QString(R"(INSERT INTO IP_address(id,address,data_update) VALUES(NULL,%1,'%2');)").arg("1").arg(dataTime));

}


