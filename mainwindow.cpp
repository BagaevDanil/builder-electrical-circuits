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
    , _Chain(nullptr)
{
    ui->setupUi(this);
    _Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_Scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    SetChain(QString::fromStdString("K1-L2-K3-(K4-L5-K6,K7-L8-K9,(K10-L11,K12-L13-K14),(K15-L16-K17))-(K18-L19,L20-K21)-L22-K23-L24-K25"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    _Chain->ChangeReverese();
}

void MainWindow::SetChain(QString str)
{
    if (_Chain) {
        delete _Chain;
        _Chain = nullptr;
    }

    _Scene->clear();
    try {
     _Chain = new TChainItem(str, _Scene, INDENT_LEFT, INDENT_UP);
    } catch (std::exception) {
        QMessageBox::warning(this, "Ошибка", "Некорректные данные");
        return;
    }
    _Scene->setSceneRect(0, 0, INDENT_LEFT + _Chain->GetSizeW(), INDENT_UP + _Chain->GetSizeH());
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
    std::string str;
    input >> str;
    SetChain(QString::fromStdString(str));
}

