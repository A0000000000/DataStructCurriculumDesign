#ifndef CONTROLDATABASE_H
#define CONTROLDATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>
#include <QMap>
#include <QVector>
#include <QVariant>
#include "location.h"

class ControlDatabase
{
public:
    ControlDatabase(QString type, QString address, quint16 port, QString databasename, QString username, QString password);
    void init();
    QMap<QString, Location> getData();
    bool addData(QString str1, QString str2, quint16 len);
    bool delData(QString str1, QString str2, quint16 len);
    bool updateData(QString str1, QString str2, quint16 len);
    QString getInformation(QString origin);
    bool changeInformation(QString origin, QString information);
    ~ControlDatabase();
private:
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // CONTROLDATABASE_H
