#include <QCoreApplication>
#include <QDebug>

#include "gt_mndlbrt.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QColor color(0xFFFFFF);

    GetMandelbrotPixelData Mndlbrt(1024, 1024, color);

    QList<QColor> colors;

    for(size_t i = 0; i < 300; i++) {
        colors.push_back(QColor(0x11 + i, 0x11 + i, 0x40 + i));
    }

    // this is not a data leak, it doesn't provide ownership
    // it's technically a weak pointer, but converting the code to work with that is a whole can of worms on its own
    // that i dont wish to dive in on this lovely fing day, god speed it works, and i don't care
    const QColor *pixel_data = Mndlbrt.getMandelbrotPixelData(colors, colors.length(), 512, 512, 1.0);

    qInfo() << "N: " << *pixel_data;

    return a.exec();
}
