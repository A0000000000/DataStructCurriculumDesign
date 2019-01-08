#include "kruskal.h"

QMap<QString, Location> Kruskal(QMap<QString, Location> & map)
{
    QMap<QString, Location> ret;
    QSet<QPair<QString, QString>> allPath;
    QMultiMap<int, QPair<QString, QString>> path;
    for(QString key1 : map.keys())
    {
        for(QString key2 : map[key1].getPath().keys())
        {
            QPair<QString, QString> tmp1(key1, key2), tmp2(key2, key1);
            if(allPath.find(tmp1) == allPath.end() && allPath.find(tmp2) == allPath.end())
            {
                allPath.insert(tmp1);
                path.insert(map[key1].getPath()[key2], tmp1);
            }
        }
    }
    QSet<QString> visit;
    allPath.clear();
    for(int key : path.keys())
    {
        QList<QPair<QString, QString>> res = path.values(key);
        for(QPair<QString, QString> & p : res)
        {
            bool flag = false;
            if(visit.find(p.first) == visit.end())
            {
                flag = true;
                visit.insert(p.first);
            }
            if(visit.find(p.second) == visit.end())
            {
                flag = true;
                visit.insert(p.second);
            }
            if(!flag && (allPath.find(QPair<QString, QString>(p.first, p.second)) == allPath.end() && allPath.find(QPair<QString, QString>(p.second, p.first)) == allPath.end()))
            {
                if(!toLink(allPath, p))
                {
                    flag = true;
                }
            }
            if(flag)
            {
                allPath.insert(QPair<QString, QString>(p.first, p.second));
            }
        }
    }
    for(const QPair<QString, QString> & p : allPath)
    {
        if(ret.find(p.first) == ret.end())
        {
            Location tmp(p.first);
            tmp.addPath(p.second, map[p.first].getPath()[p.second]);
            ret[p.first] = tmp;
        }
        else
        {
            ret[p.first].addPath(p.second, map[p.first].getPath()[p.second]);
        }
        if(ret.find(p.second) == ret.end())
        {
            Location tmp(p.second);
            tmp.addPath(p.first, map[p.second].getPath()[p.first]);
            ret[p.second] = tmp;
        }
        else
        {
            ret[p.second].addPath(p.first, map[p.second].getPath()[p.first]);
        }
    }
    return ret;
}

bool toLink(QSet<QPair<QString, QString>> & path, QPair<QString, QString> & point)
{
    QSet<QPair<QString, QString>> Ass;
    for(const QPair<QString, QString> & p : path)
    {
        Ass.insert(QPair<QString, QString>(p.first, p.second));
        Ass.insert(QPair<QString, QString>(p.second, p.first));
    }
    QSet<QString> visit;
    QStack<QPair<QString, bool>> s;
    visit.insert(point.first);
    s.push_back(QPair<QString, bool>(point.first, false));
    while(!s.empty())
    {
        QPair<QString, bool> p = s.top();
        s.pop_back();
        if(p.second)
        {
            if(p.first == point.second)
                return true;
        }
        else
        {
            p.second = true;
            s.push(p);
            for(const QPair<QString, QString> & tmp : Ass)
            {
                if(visit.find(tmp.second) == visit.end() && p.first == tmp.first)
                {
                    s.push(QPair<QString, bool>(tmp.second, false));
                    visit.insert(tmp.second);
                }
            }
        }
    }
    return false;
}
