#include "pixmap_creator.hpp"
#include <QBrush>
#include <QRgb>
#include "graphicsview.h"

#define PIXEL_WIDTH 1
#define PIXEL_HEIGHT 1
#define COLOR_DEPTH 255

PixmapCreator::PixmapCreator(ColorPicker* color_picker, QGraphicsView* view) {
    m_view = view;
    color = QColor(DEFAULT_COLOR);
    connect(color_picker, &ColorPicker::currentColorChanged,
            this, &PixmapCreator::changeColor);
}

void PixmapCreator::changeColor(QColor color) {
    this->color = color;
    QPixmap* new_pixmap = this->createPixmap();
    QGraphicsScene *scene = new QGraphicsScene(m_view);
    scene->addPixmap(*new_pixmap);
    m_view->setScene(scene);
}

QPixmap* PixmapCreator::createPixmap(size_t xCenterFrame,
                                     size_t yCenterFrame,
                                     int width,
                                     int height,
                                     double scale)
{
    GetMandelbrotPixelData mndlbrt(width, height, color);

    QList<QColor> colors;

    QRgb rgb_color = color.rgb();

    for (size_t i = 0; i < 257; i++) {
        int red = qRed(rgb_color);
        if (red < COLOR_DEPTH - i) red += i;
        else red = COLOR_DEPTH;

        int green = qGreen(rgb_color);
        if (green < COLOR_DEPTH - i) green += i;
        else green = COLOR_DEPTH;

        int blue = qBlue(rgb_color);
        if (blue < COLOR_DEPTH - i) blue += i;
        else blue = COLOR_DEPTH;

        colors.push_back(QColor(red, green, blue));
    }

    const QColor *pixelData = mndlbrt.getMandelbrotPixelData(colors, colors.length(),
                                                             xCenterFrame,
                                                             yCenterFrame,
                                                             scale);


    QPixmap *pixmap = new QPixmap(width, height);
    QPainter *painter = new QPainter(pixmap);

    for (size_t i = 0; i < mndlbrt.getHeight(); i++) {
        for (size_t j = 0; j < mndlbrt.getWidth(); j++) {
            // qDebug() << pixelData[i * mndlbrt.getWidth() + j];
            painter->setPen(pixelData[i * mndlbrt.getWidth() + j]);
            painter->drawRect(j, i, PIXEL_WIDTH, PIXEL_HEIGHT);
        }
    }
    return pixmap;
}
