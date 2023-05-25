#ifndef SQLITE_H
#define SQLITE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QCoreApplication>
#include <QTime>
class sqlite
{
public:
    QSqlDatabase db;

    sqlite();
    ~sqlite();
    void initDb();
    void CreateTable();
    void InsertMotorTable(QString status);
    void InsertIpTable(QString ip);
    void InsertInverterTable(QString status,int speed);
    void InsertFrequencyTable(float freq);
    void InsertSortTable(QString mod);
    void InsertTest();
};


#endif // SQLITE_H
