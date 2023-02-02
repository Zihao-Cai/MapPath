#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QCheckBox>
#include <QTimer>
#include "amgraph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    AMGraph* G;
    int cur_selected;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString calc();
    QVector<QCheckBox*> checkboxs;
    QTimer status_timer;
    void getcity(int &index1,int &index2);

private slots:
    void on_exit_clicked();

    void on_search_clicked();

    void on_recover_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
