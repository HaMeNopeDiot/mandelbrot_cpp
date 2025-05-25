#include "pixmap_creator.hpp"
#include <QBrush>

#define PIXEL_WIDTH 1
#define PIXEL_HEIGHT 1

QPixmap* PixmapCreator::createPixmap(size_t xCenterFrame, size_t yCenterFrame, double scale)
{
    QColor color(0xFFFFFF);

    GetMandelbrotPixelData mndlbrt(1024, 1024, color);

    QList<QColor> colors;

    for (size_t i = 0; i < 300; i++) {
        colors.push_back(QColor(0x11 + i, 0x11 + i, 0x40 + i));
    }

    const QColor *pixelData = mndlbrt.getMandelbrotPixelData(colors, colors.length(),
                                                            xCenterFrame,
                                                            yCenterFrame,
                                                            scale);
    QPixmap *pixmap = new QPixmap(1024, 1024);
    QPainter *painter = new QPainter(pixmap);

    for (size_t i = 0; i < mndlbrt.getHeight(); i++) {
        for (size_t j = 0; j < mndlbrt.getWidth(); j++) {
            painter->setPen(pixelData[i * mndlbrt.getWidth() + j]);
            painter->drawRect(j, i, 1, 1);
        }
    }
    return pixmap;
}
