#include "mainwindow.h"
#include "ui_mainwindow.h"


int INDENT_LEFT = 30;
int INDENT_UP = 30;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto* _Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_Scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    QString str1 = "K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14";
    QString str2 = "K12-K3-(L1,L4,(K2-L11,L9),(K7-K8,L1,L4,(K2-L11,L9)))-(L11,L7)-L14";
    QString str = "K1-L2-K3-(K1-L1-K1,(K1-L1-K1,K1-L1-K1)-K1-L1-(K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14,K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14,K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14,K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14,K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14,K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14,K1-L1-(K1-L1-K1,K1-L1-K1),K1))-K4-L5-K6-K12-K2-(K33-L12345-K1,K1-L4-K1,(K123456-L123456,K4-L123456)-L123-L1-K12,(K3333-K8,(K12-K3-(L1,L4,(K2-L11,L9-K7),(K7-K8))-(L11,L7)-L14),K8-L4,(K2-L11,L9-K9)))-(L1111,L7)-L14";
    QString str4 = "K1-L2-K3-(K1-L1-K1,(K1-L1-K1,K1-L1-K1)-K1-L1-(K1,K1-L1-(K1-L1-K1,K1-L1-K1),K1))-K4-L5-K6";

    chain = new TChainItem(str, _Scene, INDENT_LEFT, INDENT_UP);
    _Scene->setSceneRect(0, 0, INDENT_LEFT + chain->GetSizeW(), INDENT_UP + chain->GetSizeH());
    qDebug() << chain->ToString();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    chain->ChangeReverese();
}

