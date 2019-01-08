#ifndef DFS_H
#define DFS_H

#include <QVector>
#include <QList>
#include <QString>
#include <QMap>
#include "location.h"

QVector<QList<QString>> DFS(QMap<QString, Location> & map, QString begin, QString end);
void assist(QMap<QString, Location> & map, QString begin, QString end, QList<QString> & list, QVector<QList<QString>> & ret);

#endif // DFS_H
