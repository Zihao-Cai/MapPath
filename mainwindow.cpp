#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QByteArray>
#include "dijkstra.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    this->checkboxs.push_back(new QCheckBox);
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

    cur_selected = 0;
    status_timer.setInterval(10);
    connect(&status_timer,&QTimer::timeout,[=](){//定时器实时监测显示底部状态栏信息
        QString str = calc();
        ui->statusbar->showMessage(QString("已选中")+QString::number(cur_selected)+QString("个地点城市: ")+str);
        });
    status_timer.start();
    ui->helpword->setText("\t使用说明\n\n1、选中任意两个城市地点,点击查询即可查询两城市间最短路径,结果包含最短路线图示,路线文字说明,以及最短路程长度.\n\n2、点击复原即可取消所有勾选城市及结果显示.\n\n3、Ps:所有城市以及源数据来源于网络");
    G = new AMGraph();

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calc()
{
    int ct = 0;
    QString s = "";
    for(int i=0;i<checkboxs.size();i++){
        if(checkboxs[i]->isChecked()){
            ct++;
            s+= (G->vexs[i]+ " ");
        }
    }
    this->cur_selected = ct;
    return s;
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
        getcity(city1,city2);//得到对应城市下标
        dijkstra(G,city1,city2);//迪杰斯特拉算法求出两城市的最短路径
    }
}

void MainWindow::on_recover_clicked()
{
    printf("recover done\n");
}
