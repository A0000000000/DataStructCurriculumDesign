#include"dijkstra.h"

QMap<QString, QList<QString>> Dijkstra(QMap<QString, Location> & map, QString Key)
{
    QMap<QString, QList<QString>> ret, tmp;//最短路径 临时路径
    QList<QString> path;//每条路径
    path.push_back(Key);
    ret[Key] = path;//初始化最短路径
    for(QString & str : map[Key].getPath().keys())
    {
        path.push_back(str);
        tmp[str] = path;//初始化临时路径
        path.pop_back();
    }
    while(!tmp.empty())
    {
        QString minKey = getMinPath(tmp, map);
        ret[minKey] = tmp[minKey];//将临时路径的最短路径加入到最短路径中
        tmp.remove(minKey);//移除最短路径
        addPath(minKey, tmp, map, ret);//添加最短路径
    }
    return ret;
}

QString getMinPath(QMap<QString, QList<QString>> & res, QMap<QString, Location> & map)
{
    if(res.size() == 0 || map.size() == 0)
        return "";
    QString ret = res.keys()[0];//记录最短路径
    QList<QString> pathS = res[ret];
    int minPath = getPath(pathS, map);//记录最短路径的长度
    for(int i = 1; i < res.keys().size(); i++)
    {
        pathS = res[res.keys()[i]];
        int cnt = getPath(pathS, map);
        if(cnt < minPath)
        {
            minPath = cnt;//更新最短路径的长度
            ret = res.keys()[i];//更新最短路径
        }
    }
    return ret;
}

qint32 getPath(QList<QString> & path, QMap<QString, Location> & map)
{
    qint32 ret = 0;
    for(int i = 0; i < path.size() - 1; i++)//记录某一条路径的每一段长度
    {
        ret += map[path[i]].getPath()[path[i + 1]];
    }
    return ret;
}

void addPath(QString key, QMap<QString, QList<QString>> & res, QMap<QString, Location> & map, const QMap<QString, QList<QString>> & ass)
{
    QList<QString> allDst = map[key].getPath().keys();
    QList<QString> path = ass[key];
    for(QString & str : allDst)
    {
        if(ass.find(str) == ass.end())
        {
            if(res.find(str) == res.end())
            {
                path.push_back(str);//获得一条未访问的路径
                res[str] = path;//增加路径
                path.pop_back();
            }
            else
            {
                path.push_back(str);
                int len1 = getPath(path, map);
                int len2 = getPath(res[str], map);
                if(len1 < len2)
                {
                    res[str] = path;//已存在路径 更新为最短的路径
                }
                path.pop_back();
            }
        }
    }
}
