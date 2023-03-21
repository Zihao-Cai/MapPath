#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QCheckBox>
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
    bool p;
    QVector<int> path;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QCheckBox*> checkboxs;
    void getcity(int &index1,int &index2);
    void paintEvent(QPaintEvent*);

private slots:
    void on_exit_clicked();
    void on_search_clicked();
    void on_recover_clicked();
    void statechanged();

private:
    Ui::MainWindow *ui;
    bool eventFilter(QObject*watched,QEvent*event);
    void paintpath(AMGraph* G,bool p,QVector<int> path);
};
#endif // MAINWINDOW_H
