#include <QApplication>
#include <QDebug>

#include "gt_mndlbrt.hpp"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
