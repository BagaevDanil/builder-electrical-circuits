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
    const static int INDENT_LEFT;
    const static int INDENT_UP;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    TChainItem* chain;
    QGraphicsScene* _Scene;

private slots:
    void on_pushButton_clicked();

    void on_pushButtonOpenFile_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
