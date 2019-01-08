#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <QMap>
#include <QMultiMap>
#include <QString>
#include <QSet>
#include <QList>
#include <QPair>
#include <QStack>
#include "location.h"

QMap<QString, Location> Kruskal(QMap<QString, Location> & map);
bool toLink(QSet<QPair<QString, QString>> & path, QPair<QString, QString> & point);

#endif // KRUSKAL_H
