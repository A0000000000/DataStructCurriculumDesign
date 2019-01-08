#ifndef SHORTESTROUTE_H
#define SHORTESTROUTE_H

#include <QMultiMap>
#include <QMap>
#include <QStack>
#include <QSet>
#include <QPair>
#include <QString>
#include "location.h"

QMultiMap<int, QString> ShortestRoute(QMap<QString, Location> & map);
int getLengthByDFS(QMap<QString, Location> & map, QString point);

#endif // SHORTESTROUTE_H
