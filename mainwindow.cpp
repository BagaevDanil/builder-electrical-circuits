#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

const int MainWindow::INDENT_LEFT = 30;
const int MainWindow::INDENT_UP = 30;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_Scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    QString str = "K1-L2-K3-(K4-L5-K6,K7-L8-K9,(K10-L11,K12-L13-K14),(K15-L16-K17))-(K18-L19,L20-K21)-L22-K23-L24-K25";
    chain = new TChainItem(str, _Scene, INDENT_LEFT, INDENT_UP);
    _Scene->setSceneRect(0, 0, INDENT_LEFT + chain->GetSizeW(), INDENT_UP + chain->GetSizeH());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    chain->ChangeReverese();
}


void MainWindow::on_pushButtonOpenFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                        this,
                        "Open matrix",
                        "C://",
                        "Text file (*.txt)"
                    );

    std::ifstream input;
    input.open(path.toStdString());
    if (!input.is_open()) {
        QMessageBox::warning(this, "Ошибка", "Неверный путь");
        return;
    }

    delete chain;
    std::string str;
    input >> str;

    _Scene->clear();
    chain = new TChainItem(QString::fromStdString(str), _Scene, INDENT_LEFT, INDENT_UP);
    _Scene->setSceneRect(0, 0, INDENT_LEFT + chain->GetSizeW(), INDENT_UP + chain->GetSizeH());
}

