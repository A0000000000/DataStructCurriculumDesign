#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>
#include <QIcon>
#include <QString>
#include <QStringList>
#include <QSet>
#include <QMultiMap>
#include <QVector>
#include "location.h"
#include "loadinfo.h"
#include "controldatabase.h"
#include "dijkstra.h"
#include "kruskal.h"
#include "bfs.h"
#include "dfs.h"
#include "shortestroute.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void init();
    void initPageOne();
    void initPageTwo();
    void initPageThree();
    void initPageFour();
    int CacLength(QString str1, QString str2);

private slots:
    void on_pushButtonSwitch_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_comboBoxCO_currentIndexChanged(const QString &arg1);

    void on_comboBoxDO_currentIndexChanged(const QString &arg1);

    void on_comboBoxCD_currentIndexChanged(const QString &arg1);

    void on_comboBoxDD_currentIndexChanged(const QString &arg1);

    void on_pushButtonAdd_clicked();

    void on_pushButtonDel_clicked();

    void on_pushButtonChange_clicked();

    void on_pushButtonFind_clicked();

    void on_pushButtonISearch_clicked();

    void on_pushButtonIChange_clicked();

    void on_pushButtonAdvSearch_clicked();

    void on_pushButtonMSearch_clicked();

private:
    Ui::Widget *ui;
    LoadInfo * li;
    ControlDatabase * cd;
    QMap<QString, Location> data;
    qint16 pageCrr;
};

#endif // WIDGET_H
