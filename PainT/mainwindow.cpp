#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDataStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene();
    ui->graphicsView->setScene(scene);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimer()
{
   timer->stop();
   scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
   timer->start(100);
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_pushButton_clicked()
{
    scene->setTypeFigure(PaintScene::RombType);
}

void MainWindow::on_pushButton_2_clicked()
{
    scene->setTypeFigure(PaintScene::SquareType);
}

void MainWindow::on_pushButton_3_clicked()
{
    scene->setTypeFigure(PaintScene::TriangleType);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save Figures","","");
    if (!fileName.isEmpty()) {
        scene->saveToBinaryFile(fileName);
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Load Figures","", "");
    if (!fileName.isEmpty()) {
        scene->loadFromBinaryFile(fileName);
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    scene->back();
}


void MainWindow::on_pushButton_7_clicked()
{
    scene->clear();
    scene->update();
}


void MainWindow::on_pushButton_8_clicked()
{
     scene->setTypeFigure(PaintScene::LineType);
}

