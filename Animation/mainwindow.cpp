#include "mainwindow.h"
#include "qgraphicsview.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    QPixmap pixmap("picture.jpg");
    pixmapItem = scene->addPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));

    xSpeed = 3;
    ySpeed = 2;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::movePixmap);
    timer->start(20);
}

void MainWindow::movePixmap()
{
    if(!pixmapItem) return;

    double x = pixmapItem->x();
    double y = pixmapItem->y();
    double pixWidth = pixmapItem->pixmap().width();
    double pixHeight = pixmapItem->pixmap().height();

    x += xSpeed;
    y += ySpeed;

    if(x <= 0 ){
        xSpeed = abs(xSpeed);
    }
    if( x  >= scene->width() - pixWidth) {
        xSpeed = -abs(xSpeed);
    }
    if(y <= 0 ){
        ySpeed = abs(ySpeed);
    }
    if( y  >= scene->height() - pixHeight) {
        ySpeed = -abs(ySpeed);
    }

    pixmapItem->setPos(x, y);

    updateSceneRect();
}

void MainWindow::updateSceneRect()
{
    if(view && scene) {
        QRect viewportRect = view->viewport()->rect();
        scene->setSceneRect(0, 0, viewportRect.width(), viewportRect.height());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
