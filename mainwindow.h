#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chainitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    TChainItem* chain;

private slots:
    void on_pushButton_clicked();
    void test();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
