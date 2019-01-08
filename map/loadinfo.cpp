#include "loadinfo.h"

LoadInfo::LoadInfo(QString path)
{
    this->path = path;
}

void LoadInfo::init()
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::about(nullptr, "提示", "配置文件打开失败!");
        return;
    }
    if(!this->doc.setContent(&file))
    {
        QMessageBox::about(nullptr, "提示", "配置文件解析失败");
        return;
    }
    this->root = this->doc.firstChild().nextSibling();
    this->nodes = root.childNodes();
    file.close();
}

void LoadInfo::setPath(QString path)
{
    this->path = path;
}

QString LoadInfo::getPath()
{
    return this->path;
}

QString LoadInfo::getType()
{
    for(int i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes.at(i).nodeName() == "type")
        {
            return this->nodes.at(i).toElement().text();
        }
    }
    return "";
}

QString LoadInfo::getDataBaseName()
{
    for(int i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes.at(i).nodeName() == "DataBaseName")
        {
            return this->nodes.at(i).toElement().text();
        }
    }
    return "";
}

QString LoadInfo::getAddress()
{
    for(int i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes.at(i).nodeName() == "address")
        {
            return this->nodes.at(i).toElement().text();
        }
    }
    return "";
}

quint16 LoadInfo::getPort()
{
    for(int i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes.at(i).nodeName() == "port")
        {
            return static_cast<quint16>(this->nodes.at(i).toElement().text().toInt());
        }
    }
    return 0;
}

QString LoadInfo::getUserName()
{
    for(int i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes.at(i).nodeName() == "username")
        {
            return this->nodes.at(i).toElement().text();
        }
    }
    return "";
}

QString LoadInfo::getPassword()
{
    for(int i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes.at(i).nodeName() == "password")
        {
            return this->nodes.at(i).toElement().text();
        }
    }
    return "";
}
