#include "mainwindow.h"
#include "ui_mainwindow.h"


int SCREEN_WIDTH = 3000;
int SCREEN_HEIGHT = 500;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto* _Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_Scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    _Scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    QString str1 = "K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14";
    QString str2 = "K12-K3-(L1,L4,(K2-L11,L9),(K7-K8,L1,L4,(K2-L11,L9)))-(L11,L7)-L14";
    QString str = "K12-K2-(K33-L12345-K1,K1-L4-K1,(K123456-L123456,K4-L123456)-L123-L1-K12,(K3333-K8,(K12-K3-(L1,L4,(K2-L11,L9-K7),(K7-K8))-(L11,L7)-L14),K8-L4,(K2-L11,L9-K9)))-(L1111,L7)-L14";
    QString str4 = "K12-K3-(K1-L1-K1,K1-L4-K1,(K123456-L11,L123456),(K12-K3-(L1,L4,(K2-L11,L9-K9),(K7-K8))-K89-(L11,L7)-L14-K8))-K89-(L11,L7)-L14";

    chain = new TChainItem(_Scene, str);
    qDebug() << chain->ToString();

    TChainItem* tail = chain->GetTail();
    qDebug() << tail->ToStringReverse();
    //qDebug() << chain->_H;

    chain->AddToScene(_Scene, 30, SCREEN_HEIGHT - 50);
    //chain->GetTail()->AddToSceneR(_Scene, 0, 600, 50, SCREEN_HEIGHT - 50);

    // chain = chain->_Next->_Next->_Child[3]->_Child[1];
    // qDebug() << chain->ToString();
    // qDebug() << chain->GetLen();
}

void MainWindow::test() {
    qDebug() << "TEST";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    chain->SetReverse(!chain->IsReverese);
}

