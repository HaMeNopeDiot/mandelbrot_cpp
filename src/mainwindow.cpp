#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include "pixmap_creator.hpp"
#include "graphicsview.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    zoomFactorLabel = new QLabel(QString("Zoom Factor"));
    ui->verticalLayout->addWidget(zoomFactorLabel);

    scrollBar = new QScrollBar(Qt::Horizontal, this);
    ui->verticalLayout->addWidget(scrollBar);

    view = new GraphicsView(this, scrollBar);
    ui->verticalLayout->addWidget(view);

    scrollBar->setMinimum(1);
    scrollBar->setMaximum(100);

}

MainWindow::~MainWindow() { delete ui; }
