#include "location.h"

Location::Location(QString name)
{
    this->name = name;
}

QString Location::getName()
{
    return this->name;
}

bool Location::addPath(QString name, quint16 length)
{
    if(this->path.find(name) == this->path.end())
    {
        this->path[name] = length;
        return true;
    }
    return false;
}

QMap<QString, quint16> Location::getPath()
{
    return this->path;
}
