#include "pixmap_creator.hpp"
#include <QBrush>
#include <QRgb>
#include "graphicsview.h"

#define PIXEL_WIDTH 1
#define PIXEL_HEIGHT 1

PixmapCreator::PixmapCreator(ColorPicker* color_picker, QGraphicsView* view) {
    m_view = view;
    color = QColor(DEFAULT_COLOR);
    connect(color_picker, &ColorPicker::currentColorChanged, this, &PixmapCreator::changeColor);
}

void PixmapCreator::changeColor(QColor color) {
    this->color = color;
    QPixmap* new_pixmap = this->createPixmap();
    ((GraphicsView)m_view).base_pixmap = new_pixmap;
}

QPixmap* PixmapCreator::createPixmap(size_t xCenterFrame,
                                     size_t yCenterFrame,
                                     int width,
                                     int height,
                                     double scale)
{
    QColor base_color(0x111111);


    GetMandelbrotPixelData mndlbrt(width, height, base_color);

    QList<QColor> colors;

    QRgb rgb_color = color.rgb();

    for (size_t i = 0; i < 300; i++) {
        colors.push_back(QColor(qRed(rgb_color) + i, qGreen(rgb_color) + i, qBlue(rgb_color) + i));
    }

    const QColor *pixelData = mndlbrt.getMandelbrotPixelData(colors, colors.length(),
                                                             xCenterFrame,
                                                             yCenterFrame,
                                                             scale);
    QPixmap *pixmap = new QPixmap(width, height);
    QPainter *painter = new QPainter(pixmap);

    for (size_t i = 0; i < mndlbrt.getHeight(); i++) {
        for (size_t j = 0; j < mndlbrt.getWidth(); j++) {
            painter->setPen(pixelData[i * mndlbrt.getWidth() + j]);
            painter->drawRect(j, i, PIXEL_WIDTH, PIXEL_HEIGHT);
        }
    }
    return pixmap;
}
