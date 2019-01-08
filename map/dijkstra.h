#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QMap>
#include <QList>
#include <QString>
#include "location.h"

QMap<QString, QList<QString>> Dijkstra(QMap<QString, Location> & map, QString Key);
QString getMinPath(QMap<QString, QList<QString>> & res, QMap<QString, Location> & map);
qint32 getPath(QList<QString> & path, QMap<QString, Location> & map);
void addPath(QString key, QMap<QString, QList<QString>> & res, QMap<QString, Location> & map, const QMap<QString, QList<QString>> & ass);

#endif // DIJKSTRA_H
