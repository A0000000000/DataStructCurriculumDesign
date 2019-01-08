#ifndef LOADINFO_H
#define LOADINFO_H

#include <QString>
#include <QDomDocument>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
#include <QDomNode>
#include <QDomNodeList>

class LoadInfo
{
public:
    LoadInfo(QString path);
    void init();
    void setPath(QString path);
    QString getPath();
    QString getType();
    QString getDataBaseName();
    QString getAddress();
    quint16 getPort();
    QString getUserName();
    QString getPassword();
private:
    QString path;
    QDomDocument doc;
    QDomNode root;
    QDomNodeList nodes;
};

#endif // LOADINFO_H
