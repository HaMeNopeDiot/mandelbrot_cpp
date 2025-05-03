#include <QApplication>

#include "QTookMainDamn.hpp"

int main(int argc, char *argv[]) {
    // использовать QApplication для просто QThread это безумно, но так как это будет обернуто потом в GUI, то ладно
    QApplication app(argc, argv);

    QTookMainDamn oldMain;
    oldMain.main();

    return app.exec();
}
