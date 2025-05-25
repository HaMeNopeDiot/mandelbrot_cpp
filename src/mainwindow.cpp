#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include "pixmap_creator.hpp"
#include "graphicsview.h"
#include <qDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    view = new GraphicsView();

    PixmapCreator *pc = new PixmapCreator();
    QPixmap *pixmap = pc->createPixmap();

    QGraphicsScene *scene = new QGraphicsScene();

    scene->addPixmap(*pixmap);
    view->setScene(scene);

    ui->verticalLayout->addWidget(view);

    qInfo() << view;

}

MainWindow::~MainWindow() { delete ui; }
