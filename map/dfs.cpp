#include "dfs.h"

QVector<QList<QString>> DFS(QMap<QString, Location> & map, QString begin, QString end)
{
    QVector<QList<QString>> ret;
    QList<QString> list;
    list.push_back(begin);
    assist(map, begin, end, list, ret);
    return ret;
}

void assist(QMap<QString, Location> & map, QString begin, QString end, QList<QString> & list, QVector<QList<QString>> & ret)
{
    if(begin == end)
    {
        ret.push_back(list);
        return;
    }
    for(QString & str : map[begin].getPath().keys())
    {
        if(!list.contains(str))
        {
            list.push_back(str);
            assist(map, str, end, list, ret);
            list.pop_back();
        }
    }
}
