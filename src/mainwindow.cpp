#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include "pixmap_creator.hpp"
#include "graphicsview.h"
#include <QDebug>

#define MIN_ZOOM 1
#define MAX_ZOOM 150


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    zoomFactorLabel = new QLabel(QString("Zoom Factor"));
    ui->verticalLayout->addWidget(zoomFactorLabel);

    scrollBar = new QScrollBar(Qt::Horizontal, this);
    ui->verticalLayout->addWidget(scrollBar);

    view = new GraphicsView(this, scrollBar);
    ui->verticalLayout->addWidget(view);

    scrollBar->setMinimum(MIN_ZOOM);
    scrollBar->setMaximum(MAX_ZOOM);
}

MainWindow::~MainWindow() { delete ui; }
