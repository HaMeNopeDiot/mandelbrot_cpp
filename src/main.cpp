#include <QApplication>

#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
    // использовать QApplication для просто QThread это безумно, но так как это будет обернуто потом в GUI, то ладно
    QApplication app(argc, argv);

    MainWindow *mw = new MainWindow();
    mw->show();

    return app.exec();
}
