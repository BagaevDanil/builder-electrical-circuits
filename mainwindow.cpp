#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chainitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString str = "K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14";
    TChainItem* chain = new TChainItem(str, 0);
    qDebug() << chain->ToString();

    /*qDebug() << chain->_IsChain;
    qDebug() << chain->_Num;

    chain = chain->_Next;
    qDebug() << chain->_IsChain;
    qDebug() << chain->_Num;

    chain = chain->_Next;
    qDebug() << chain->_IsChain;
    TChainItem* child1 = chain->_Child[0];
    TChainItem* child2 = chain->_Child[1];
    TChainItem* child3 = chain->_Child[2];
    TChainItem* child4 = chain->_Child[3];

    qDebug() << child1->_IsChain;
    qDebug() << child1->_Num;

    qDebug() << child2->_IsChain;
    qDebug() << child2->_Num;

    qDebug() << child3->_IsChain;
    TChainItem* child31 = child3->_Child[0];
    TChainItem* child32 = child3->_Child[1];
    qDebug() << child31->_IsChain;
    qDebug() << child31->_Num;
    qDebug() << child32->_IsChain;
    qDebug() << child32->_Num;*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

