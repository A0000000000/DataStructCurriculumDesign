#include "widget.h"
#include "ui_widget.h"

#include<QDebug>
#define cout qDebug()

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("校园导游系统");
    this->setWindowIcon(QIcon(":/new/prefix1/windows.ico"));
    this->init();
    this->initPageOne();
    this->initPageTwo();
    this->initPageThree();
    this->initPageFour();
    this->pageCrr = -1;
}

Widget::~Widget()
{
    delete this->li;
    delete this->cd;
    delete ui;
}

void Widget::init()
{
    this->li = new LoadInfo(":/new/prefix2/info.xml");
    this->li->init();
    this->cd = new ControlDatabase(this->li->getType(), this->li->getAddress(), \
                                   this->li->getPort(), this->li->getDataBaseName(), \
                                   this->li->getUserName(), this->li->getPassword());
    this->cd->init();
    this->data = this->cd->getData();
}

void Widget::on_pushButtonSwitch_clicked()
{
    this->data = this->cd->getData();
    this->pageCrr++;
    this->pageCrr = this->pageCrr % 4;
    this->ui->stackedWidget->setCurrentIndex(static_cast<int>(this->pageCrr));
}

void Widget::initPageOne()
{
    this->ui->comboBoxOrigin->clear();
    this->ui->comboBoxdestination->clear();
    for(Location & i : this->data)
    {
        this->ui->comboBoxOrigin->addItem(i.getName());
        this->ui->comboBoxdestination->addItem(i.getName());
    }
    this->ui->textEditResult->setText("");
}

void Widget::initPageTwo()
{
    this->ui->comboBoxCO->clear();
    this->ui->comboBoxDO->clear();
    for(Location & i : this->data)
    {
        this->ui->comboBoxCO->addItem(i.getName());
        this->ui->comboBoxDO->addItem(i.getName());
    }
}

void Widget::initPageThree()
{
    this->ui->comboBoxISearch->clear();
    this->ui->comboBoxIChange->clear();
    for(auto & i : this->data.keys())
    {
        this->ui->comboBoxISearch->addItem(i);
        this->ui->comboBoxIChange->addItem(i);
    }
    this->ui->textEditIChange->setText("");
    this->ui->textEditISinformation->setText("");
}

void Widget::initPageFour()
{
    this->ui->comboBoxAdvD->clear();
    this->ui->comboBoxAdvO->clear();
    for(QString & str : this->data.keys())
    {
        this->ui->comboBoxAdvO->addItem(str);
        this->ui->comboBoxAdvD->addItem(str);
    }
    this->ui->textEditAdvRet->setText("");
    this->ui->textEditMulRet->setText("");
    this->ui->lineEditMultiPoint->setText("");
}

void Widget::on_stackedWidget_currentChanged(int arg1)
{
    if(arg1 == 0)
    {
        this->initPageTwo();
    }
    else if(arg1 == 1)
    {
        this->initPageThree();
    }
    else if(arg1 == 2)
    {
        this->initPageFour();
    }
    else
    {
        this->initPageOne();
    }
}

void Widget::on_comboBoxCO_currentIndexChanged(const QString &arg1)
{
    this->ui->comboBoxCD->clear();
    for(auto & i : this->data[arg1].getPath().keys())
    {
        this->ui->comboBoxCD->addItem(i);
    }
    this->ui->lineEditCL->setText(QString::number(this->CacLength(arg1, this->ui->comboBoxCD->currentText())));
}

void Widget::on_comboBoxDO_currentIndexChanged(const QString &arg1)
{
    this->ui->comboBoxDD->clear();
    for(auto & i : this->data[arg1].getPath().keys())
    {
        this->ui->comboBoxDD->addItem(i);
    }
    this->ui->lineEditDL->setText(QString::number(this->CacLength(arg1, this->ui->comboBoxDD->currentText())));
}

void Widget::on_comboBoxCD_currentIndexChanged(const QString &arg1)
{
    this->ui->lineEditCL->setText(QString::number(this->CacLength(this->ui->comboBoxCO->currentText(), arg1)));
}

void Widget::on_comboBoxDD_currentIndexChanged(const QString &arg1)
{
    this->ui->lineEditDL->setText(QString::number(this->CacLength(this->ui->comboBoxDO->currentText(), arg1)));
}

int Widget::CacLength(QString str1, QString str2)
{
    return static_cast<int>(this->data[str1].getPath()[str2]);
}

void Widget::on_pushButtonAdd_clicked()
{
    QString str1 = this->ui->lineEditAO->text();
    QString str2 = this->ui->lineEditAD->text();
    quint16 len = static_cast<quint16>(this->ui->lineEditAL->text().toInt());
    if(str1 == "" || str2 == "" || len <= 0 || str1 == str2)
    {
        QMessageBox::about(this, "提示", "输入数据不合法");
        return;
    }
    bool ret = this->cd->addData(str1, str2, len);
    if(ret)
    {
        QMessageBox::about(this, "提示", "添加成功!");
        this->ui->lineEditAO->setText("");
        this->ui->lineEditAD->setText("");
        this->ui->lineEditAL->setText("");
        this->data = this->cd->getData();
        this->initPageTwo();
    }
    else
    {
        QMessageBox::about(this, "提示", "添加失败!");
    }
}

void Widget::on_pushButtonDel_clicked()
{
    QString str1 = this->ui->comboBoxDO->currentText();
    QString str2 = this->ui->comboBoxDD->currentText();
    quint16 len = static_cast<quint16>(this->ui->lineEditDL->text().toInt());
    bool ret = this->cd->delData(str1, str2, len);
    if(ret)
    {
        QMessageBox::about(this, "提示", "删除成功!");
        this->data = this->cd->getData();
        this->initPageTwo();
    }
    else
    {
        QMessageBox::about(this, "提示", "删除失败!");
    }
}

void Widget::on_pushButtonChange_clicked()
{
    QString str1 = this->ui->comboBoxCO->currentText();
    QString str2 = this->ui->comboBoxCD->currentText();
    quint16 len = static_cast<quint16>(this->ui->lineEditCL->text().toInt());
    if(len <= 0)
    {
        QMessageBox::about(this, "提示", "输入不合法!");
        return;
    }
    bool ret = this->cd->updateData(str1, str2, len);
    if(ret)
    {
        QMessageBox::about(this, "提示", "修改成功");
        this->data = this->cd->getData();
        this->initPageTwo();
    }
    else
    {
        QMessageBox::about(this, "提示", "修改失败");
    }
}

void Widget::on_pushButtonFind_clicked()
{
    this->ui->textEditResult->clear();
    QString str1 = this->ui->comboBoxOrigin->currentText();
    QString str2 = this->ui->comboBoxdestination->currentText();
    if(str1 == str2)
    {
        this->ui->textEditResult->append("<font style=\"color : green\">您选择的起始地和目的地相同.</font>");
        return;
    }
    QMap<QString, QList<QString>> ret = Dijkstra(this->data, str1);
    if(ret.find(str2) == ret.end())
    {
        this->ui->textEditResult->append("<font style=\"color : red\">您选择的起始地和目的地没有合适的路线.</font>");
        return;
    }
    QList<QString> path = ret[str2];
    this->ui->textEditResult->append("<font style=\"color : #66CCff\">最短路径为:</font>");
    for(int i = 0; i < path.size() - 1; i++)
    {
        QString line = QString("<font style=\"color : #66FFCC\">%1 ---  %2  ---></font>").arg(path[i]).arg(this->data[path[i]].getPath()[path[i + 1]]);
        this->ui->textEditResult->append(line);
    }
    if(!path.empty())
    {
        this->ui->textEditResult->append(QString("<font style=\"color : #66FFCC\">%1</font>").arg(path[path.size() - 1]));
    }
}

void Widget::on_pushButtonISearch_clicked()
{
    QString str = this->ui->comboBoxISearch->currentText();
    QString information = this->cd->getInformation(str);
    this->ui->textEditISinformation->setText(information);
}

void Widget::on_pushButtonIChange_clicked()
{
    QString str = this->ui->comboBoxIChange->currentText();
    QString information = this->ui->textEditIChange->toPlainText();
    bool ret = this->cd->changeInformation(str, information);
    if(ret)
    {
        QMessageBox::about(this, "提示", "信息修改成功!");
        this->ui->textEditIChange->setText("");
    }
    else
    {
        QMessageBox::about(this, "提示", "信息修改失败!");
    }
}

void Widget::on_pushButtonAdvSearch_clicked()
{
    this->ui->textEditAdvRet->setText("");
    QString str1 = this->ui->comboBoxAdvO->currentText();
    QString str2 = this->ui->comboBoxAdvD->currentText();
    if(str1 == str2)
    {
        this->ui->textEditAdvRet->append("<font style=\"color : green\">您选择的起始地和目的地相同.</font>");
        return;
    }
    QVector<QList<QString>> ret = DFS(this->data, str1, str2);
    if(ret.size() == 0)
    {
        this->ui->textEditAdvRet->append("<font style=\"color : red\">您选择的起始地和目的地没有合适的路线.</font>");
        return;
    }
    for(QList<QString> & list : ret)
    {
        QString line;
        if(list.size() > 0)
        {
            line = list[0];
        }
        for(int i = 1; i < list.size(); i++)
        {
            line += "->" + list[i];
        }
        this->ui->textEditAdvRet->append(QString("<font style=\"color : #66FFCC\">%1</font>").arg(line));
    }
}

void Widget::on_pushButtonMSearch_clicked()
{
    this->ui->textEditMulRet->setText("");
    QString points = this->ui->lineEditMultiPoint->text();
    points = points.trimmed();
    QStringList list = points.split("#");
    QSet<QString> sS = list.toSet();
    QMap<QString, Location> subMap;
    for(QSet<QString>::iterator it = sS.begin(); it != sS.end(); )
    {
        if(this->data.find(*it) == this->data.end())
        {
            sS.erase(it);
        }
        else
        {
            it++;
        }
        if(sS.empty())
            break;
    }
    if(sS.empty())
    {
        this->ui->textEditMulRet->setText("未查询到任何信息");
        return;
    }
    for(QString s1 : sS)
    {
        subMap[s1] = Location(s1);
        for(QString s2 : sS)
        {
            QMap<QString, quint16> path = this->data[s1].getPath();
            if(s1 != s2 && path.find(s2) != path.end())
            {
                subMap[s1].addPath(s2, this->data[s1].getPath()[s2]);
            }
        }
    }
    QMap<QString, Location> littleTree = Kruskal(subMap);
    QMultiMap<int, QString> res = ShortestRoute(littleTree);
    QVector<QVector<QString>> ret = BFS(littleTree, res.value(res.keys()[0]));
    for(QVector<QString> & line : ret)
    {
        QString str = "[";
        for(int i = 0; i < line.size() - 1; i++)
        {
            str += line[i];
            str += ", ";
        }
        if(line.size() != 0)
        {
            str += line[line.size() - 1];
        }
        str += "]";
        this->ui->textEditMulRet->append(str);
    }
}
