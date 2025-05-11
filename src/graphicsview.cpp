#include "graphicsview.h"
#include <QWheelEvent>
#include <QGraphicsPixmapItem>

#define DEFAULT_ZOOM_FACTOR 2
#define FILE_PATH "/Users/ilya/mandelbrot_test.bmp"

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {


    // Обновлять view port когда нужно
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Оставлять центр зума на мыши
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    mScene = new QGraphicsScene();
    setScene(mScene);

    mImage = new QImage(FILE_PATH);

    mPixmap = QPixmap::fromImage(*mImage);
    pixmapItem = mScene->addPixmap(mPixmap);

}

void GraphicsView::setApi(MultithreadApi *api) {
    mApi = api;
}

void GraphicsView::wheelEvent(QWheelEvent *event) {

    if (event->modifiers() & Qt::ControlModifier) {
        double factor = DEFAULT_ZOOM_FACTOR;
        const std::vector<MandelbrotColor> colors = mApi->getColors();
        mApi->genBmp(colors, colors.size(), event->position().x(), event->position().y(), factor);
        mApi->saveBmpToFile(FILE_PATH);

        mImage = new QImage(FILE_PATH);
        mPixmap = QPixmap::fromImage(*mImage);
        pixmapItem->setPixmap(mPixmap);
    }
    else { QGraphicsView::wheelEvent(event); }
    event->accept();
}
