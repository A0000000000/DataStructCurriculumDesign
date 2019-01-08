#ifndef LOCATION_H
#define LOCATION_H

#include <QString>
#include <QMap>

class Location
{
public:
    Location(QString name = "");
    QString getName();
    bool addPath(QString name, quint16 length);
    QMap<QString, quint16> getPath();
private:
    QString name;
    QMap<QString, quint16> path;
};

#endif // LOCATION_H
