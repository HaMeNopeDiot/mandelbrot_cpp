#include "graphicsview.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QPointF>
#include <QPoint>

#define DEFAULT_ZOOM_FACTOR 2
#define START_ZOOM_FACTOR 1
#define MAX_ZOOM_IN 100
#define MAX_ZOOM_OUT 1


GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {
     // Обновлять view port когда нужно
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Оставлять центр зума на мыши
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    zoomFactor = START_ZOOM_FACTOR;
    pc = new PixmapCreator();

    QPixmap *pixmap = pc->createPixmap(width() / 2, height() / 2, width(), height());

    QGraphicsScene *scene = new QGraphicsScene(0, 0, width(), height());
    scene->addPixmap(*pixmap);
    setScene(scene);
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        leftButtonPressed = true;
        QPointF mappedPos = mapToScene(event->position().x(), event->position().y());
        spawnZoomRect(mappedPos.x(), mappedPos.y());
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (leftButtonPressed) {
        double xCenter = event->position().x();
        double yCenter = event->position().y();
        moveZoomRect(xCenter, yCenter);
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        leftButtonPressed = false;
        despawnZoomRect();
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::spawnZoomRect(int xCenter, int yCenter, int width, int height) {

    qInfo() << "X: " << xCenter << ", Y: " << yCenter;

    yCenter = this->height() - yCenter;

    QPointF p(xCenter, yCenter);
    p = p / this->width() * width;

    qInfo() << "P: " << p;

    QPixmap *pixmap = pc->createPixmap(p.x(), p.y(), width, height, 25);
    zoomRect = scene()->addPixmap(*pixmap);
    zoomRect->setZValue(2);

    zoomRect->setX(xCenter);
    zoomRect->setY(this->height() - yCenter);
}

void GraphicsView::moveZoomRect(int xCenter, int yCenter) {
    double width = zoomRect->boundingRect().width();
    double height = zoomRect->boundingRect().height();

    despawnZoomRect();
    spawnZoomRect(xCenter, yCenter, width, height);
}

void GraphicsView::despawnZoomRect() {
    scene()->removeItem(zoomRect);
}