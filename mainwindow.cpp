#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QByteArray>
#include "dijkstra.h"
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mapwidget->installEventFilter(this);
    ui->helpword->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200), stop:1 rgba(20,196,188, 210));");
    ui->resulttext->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200), stop:1 rgba(20,196,188, 210));");
    ui->search->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                               "border: 2px groove gray;border-radius:15px;padding:2px 4px;border-style: outset;}"
                               "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                               "QPushButton:pressed{background-color: rgb(17,171,164);}"//pressed
                                 "border:2px solid rgb(20,196,188);");
    ui->recover->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                               "border: 2px groove gray;border-radius:15px;padding:2px 4px;border-style: outset;}"
                               "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                               "QPushButton:pressed{background-color: rgb(17,171,164);}"//pressed
                                 "border:2px solid rgb(20,196,188);");
    ui->exit->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                               "border: 2px groove gray;border-radius:15px;padding:2px 4px;border-style: outset;}"
                               "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                               "QPushButton:pressed{background-color: rgb(17,171,164);}"//pressed
                                 "border:2px solid rgb(20,196,188);");
    this->checkboxs.push_back(new QCheckBox);//用一个空对象占用0号位
    this->checkboxs.push_back(ui->wulumuqi);
    this->checkboxs.push_back(ui->yinchuan);
    this->checkboxs.push_back(ui->beijing);
    this->checkboxs.push_back(ui->haerbin);
    this->checkboxs.push_back(ui->zhengzhou);
    this->checkboxs.push_back(ui->shanghai);
    this->checkboxs.push_back(ui->lasa);
    this->checkboxs.push_back(ui->chengdu);
    this->checkboxs.push_back(ui->wuhan);
    this->checkboxs.push_back(ui->nanning);
    this->checkboxs.push_back(ui->haikou);
    this->checkboxs.push_back(ui->xianggang);
    this->checkboxs.push_back(ui->guangzhou);
    for(int i=0;i<checkboxs.size();i++){
        connect(checkboxs[i],SIGNAL(clicked()),this,SLOT(statechanged()));
    }

    cur_selected = 0;
    ui->helpword->setText("\t使用说明\n\n1、选中任意两个城市地点,点击查询即可查询两城市间最短路径,结果包含最短路线图示,路线文字说明,以及最短路程长度.\n\n2、点击复原即可取消所有勾选城市及结果显示.\n\n3、Ps:所有城市以及源数据来源于网络\n\n4、标注里程单位：Km");
    G = new AMGraph();
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getcity(int &index1, int &index2)
{
    int i=0;
    index1 = 0;
    index2 = 0;
    for(i=0;i<checkboxs.size();i++){
        if(checkboxs[i]->isChecked()){
            index1 = i;
            break;
        }
    }
    i++;
    for(;i<checkboxs.size();i++){
        if(checkboxs[i]->isChecked()){
            index2 = i;
            break;
        }
    }
}


void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_search_clicked()
{
    if(this->cur_selected!=2){
        QMessageBox msg;
        msg.setWindowTitle("警告");
        msg.setIcon(QMessageBox::Warning);
        msg.setText("查询失败,请检查!");
        msg.exec();
        on_recover_clicked();
        return;
    }else{
        int city1,city2;
        getcity(city1,city2);//得到对应城市下标,默认city1是起点,city2是终点
        double path_len[G->n+1];
        dijkstra(G,G->n,city1,path_len);//迪杰斯特拉算法求出两城市的最短路径
        qDebug()<<path_len[city2]<<endl;
    }
}

void MainWindow::on_recover_clicked()
{
    printf("recover done\n");
}

void MainWindow::statechanged()
{
    QObject *obj = QObject::sender();
    QCheckBox *chb = qobject_cast<QCheckBox *>(obj);
    if (chb->isChecked()){
            cur_selected++;
        } else {
            cur_selected--;
        }
    if(cur_selected>2){
        chb->setCheckState(Qt::Unchecked);
        cur_selected--;
    }

    QString s = "";
    for(int i=1;i<checkboxs.size();i++){
        if(checkboxs[i]->isChecked()){
            s+= (G->vexs[i]+ " ");
        }
    }
    ui->statusbar->showMessage(QString("已选中")+QString::number(cur_selected)+QString("个地点城市: ")+s);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->mapwidget && event->type() == QEvent::Paint){
        paintpath(G);
    }
    return QWidget::eventFilter(watched,event);
}

void MainWindow::paintpath(AMGraph *G)
{
    QPainter painter(ui->mapwidget);
    int x1,y1,x2,y2;
    for(int i=1;i<=13;i++){
        painter.setPen(QPen(Qt::black,5));
        painter.drawPoint(checkboxs[i]->x()+30,checkboxs[i]->y()+15);
        for(int j=i;j<=13;j++){
            painter.setPen(QPen(Qt::darkGray,2));
            if(G->arcs[i][j] != ENDLESS){
                x1 = checkboxs[i]->x()+30;
                y1 = checkboxs[i]->y()+15;
                x2 = checkboxs[j]->x()+30;
                y2 = checkboxs[j]->y()+15;
                painter.drawLine(x1,y1,x2,y2);//绘制城市线路
                painter.drawText(QPoint((x1+x2)/2,(y1+y2)/2),QString::number(G->arcs[i][j]));//绘制单线路径里程
            }
        }
    }// of for i

}


void MainWindow::paintEvent(QPaintEvent*){


}





