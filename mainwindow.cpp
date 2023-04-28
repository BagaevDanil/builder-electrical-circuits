#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chainitem.h"

int SCREEN_WIDTH = 2000;
int SCREEN_HEIGHT = 2000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString str1 = "K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14";
    QString str2 = "K12-K3-(L1,L4,(K2-L11,L9),(K7-K8,L1,L4,(K2-L11,L9)))-(L11,L7)-L14";
    QString str = "K12-K3-(L1,L4,(K2-L11,L9),(K7-K8,(K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14),L4,(K2-L11,L9)))-(L11,L7)-L14";
    QString str4 = "K12-K3-(L1,L4,(K2-L11,L9),(K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-K89-(L11,L7)-L14-K8))-K89-(L11,L7)-L14";
    TChainItem* chain = new TChainItem();
    chain->MakeChainFromStr(str);
    qDebug() << chain->ToString();
    qDebug() << chain->GetW();

    //TChainItem* tail = chain->GetTail();
    //qDebug() << tail->ToStringReverse();
    //qDebug() << chain->_H;

    auto* _Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_Scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    _Scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    chain->AddToScene(_Scene, 50, SCREEN_WIDTH - 50, 50, SCREEN_HEIGHT - 50);
}

MainWindow::~MainWindow()
{
    delete ui;
}
