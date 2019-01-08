#include "controldatabase.h"

ControlDatabase::ControlDatabase(QString type, QString address, quint16 port, QString databasename, QString username, QString password)
{
    this->db = QSqlDatabase::addDatabase(type);
    this->db.setHostName(address);
    this->db.setPort(port);
    this->db.setDatabaseName(databasename);
    this->db.setUserName(username);
    this->db.setPassword(password);
}

void ControlDatabase::init()
{
    if(!this->db.open())
    {
        QMessageBox::about(nullptr, "提示", this->db.lastError().text());
        return;
    }
    this->query = QSqlQuery(db);
}

QMap<QString, Location> ControlDatabase::getData()
{
    QMap<QString, Location> ret;
    if(this->query.exec("select * from MapPath"))
    {
        while(this->query.next())
        {
            QVector<QString> items;
            for (int i = 0; i < 3; i++)
            {
                items.push_back(this->query.value(i).toString());
            }
            if(ret.find(items[0]) == ret.end())
            {
                Location tmp(items[0]);
                tmp.addPath(items[1], static_cast<quint16>(items[2].toInt()));
                ret[items[0]] = tmp;
            }
            else
            {
                ret[items[0]].addPath(items[1], static_cast<quint16>(items[2].toInt()));
            }
        }
    }
    return ret;
}

bool ControlDatabase::addData(QString str1, QString str2, quint16 len)
{
    QString sql1 = QString("insert into MapPath values(\'%1\', \'%2\', %3, null)").arg(str1).arg(str2).arg(len);
    QString sql2 = QString("insert into MapPath values(\'%1\', \'%2\', %3, null)").arg(str2).arg(str1).arg(len);
    return this->query.exec(sql1) && this->query.exec(sql2);
}

bool ControlDatabase::delData(QString str1, QString str2, quint16 len)
{
    QString sql1 = QString("delete from MapPath where origin=\'%1\' and destination=\'%2\' and length=%3").arg(str1).arg(str2).arg(len);
    QString sql2 = QString("delete from MapPath where origin=\'%1\' and destination=\'%2\' and length=%3").arg(str2).arg(str1).arg(len);
    return this->query.exec(sql1) && this->query.exec(sql2);
}

bool ControlDatabase::updateData(QString str1, QString str2, quint16 len)
{
    QString sql1 = QString("update MapPath set length=%1 where origin=\'%2\' and destination=\'%3\'").arg(len).arg(str1).arg(str2);
    QString sql2 = QString("update MapPath set length=%1 where origin=\'%2\' and destination=\'%3\'").arg(len).arg(str2).arg(str1);
    return this->query.exec(sql1) && this->query.exec(sql2);
}

ControlDatabase::~ControlDatabase()
{
    this->db.close();
}

QString ControlDatabase::getInformation(QString origin)
{
    QString str = QString("select information from MapPath where origin = \'%1\'").arg(origin);
    if(this->query.exec(str))
    {
        QString tmp;
        if(this->query.next())
        {
            tmp = this->query.value(0).toString();
        }
        return tmp;
    }
    return "";
}

bool ControlDatabase::changeInformation(QString origin, QString information)
{
    QString str = QString("update MapPath set information = \'%1\' where origin = \'%2\'").arg(information).arg(origin);
    return this->query.exec(str);
}
