#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QImage>

#define FILE_PATH "/Users/ilya/mandelbrot_test.bmp"
#define X_CENTER 1024 / 2.0f
#define Y_CENTER 1024 / 2.0f

MainWindow::MainWindow(MultithreadApi *api, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    mApi = api;
    ui->graphicsView->setApi(mApi);
    const std::vector<MandelbrotColor> colors = mApi->getColors();
    mApi->genBmp(colors, colors.size(), X_CENTER, Y_CENTER);
    mApi->saveBmpToFile(FILE_PATH);

}


MainWindow::~MainWindow() {
    delete ui;
    delete mApi;
}
