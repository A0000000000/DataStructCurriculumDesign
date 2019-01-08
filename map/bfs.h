#ifndef BFS_H
#define BFS_H

#include <QVector>
#include <QString>
#include <QMap>
#include <QSet>
#include <QQueue>
#include "location.h"

QVector<QVector<QString>> BFS(QMap<QString, Location> & map, QString key);

#endif // BFS_H
