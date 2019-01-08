#include"bfs.h"

QVector<QVector<QString>> BFS(QMap<QString, Location> & map, QString key)
{
    QVector<QVector<QString>> ret;
    QSet<QString> visit;
    QQueue<QString> q;
    q.push_back(key);
    visit.insert(key);
    while(!q.empty())
    {
        QVector<QString> tmp;
        int size = q.size();
        for(int i = 0; i < size; i++)
        {
            QString str = q.front();
            tmp.push_back(str);
            q.pop_front();
            for(QString & dst : map[str].getPath().keys())
            {
                if(visit.find(dst) == visit.end())
                {
                    visit.insert(dst);
                    q.push_back(dst);
                }
            }
        }
        ret.push_back(tmp);
    }
    return ret;
}
