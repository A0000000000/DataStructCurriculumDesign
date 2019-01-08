#include "shortestroute.h"

QMultiMap<int, QString> ShortestRoute(QMap<QString, Location> & map)
{
    QMultiMap<int, QString> ret;
    for(QString key : map.keys())
    {
        ret.insert(getLengthByDFS(map, key), key);
    }
    return ret;
}

int getLengthByDFS(QMap<QString, Location> & map, QString point)
{
    int ret = 0;
    QMap<QString, QString> parent;
    QStack<QPair<QString, bool>> s;
    QSet<QString> visit;
    s.push_back(QPair<QString, bool>(point, false));
    visit.insert(point);
    int tmp = 0;
    while(!s.empty())
    {
        QPair<QString, bool> p = s.top();
        s.pop_back();
        if(p.second)
        {
            if(p.first != point)
            {
                ret += map[parent[p.first]].getPath()[p.first];
                tmp += map[parent[p.first]].getPath()[p.first];
            }
        }
        else
        {
            p.second = true;
            s.push_back(p);
            for(QString str : map[p.first].getPath().keys())
            {
                if(visit.find(str) == visit.end())
                {
                    visit.insert(str);
                    parent[str] = p.first;
                    s.push_back(QPair<QString, bool>(str, false));
                    ret += tmp;
                    tmp = 0;
                }
            }
        }
    }
    return ret;
}
