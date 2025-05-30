#include "graphicsview.h"
#include <QPixmap>
#include <QGraphicsScene>


GraphicsView::GraphicsView(QWidget *parent, QScrollBar *scrollBar) : QGraphicsView(parent) {
     // Обновлять view port когда нужно
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Оставлять центр зума на мыши
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    pc = new PixmapCreator();

    QPixmap *pixmap = pc->createPixmap();

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(*pixmap);
    setScene(scene);

    this->scrollBar = scrollBar;
}

QPointF GraphicsView::mapPos(double x, double y) {
    return mapToScene(x, y);
    // return mapFromScene(x, y);
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        leftButtonPressed = true;
        QPointF mappedPos = mapPos(event->position().x(), event->position().y());
        spawnZoomRect(mappedPos.x(), mappedPos.y());
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (leftButtonPressed) {
        QPointF mappedPos = mapPos(event->position().x(), event->position().y());
        moveZoomRect(mappedPos.x(), mappedPos.y());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::test_pos(QMouseEvent *event) {
    qInfo() << "To scene: " << mapToScene(event->position().x(), event->position().y());
    qInfo() << "From scene: " << mapFromScene(event->position().x(), event->position().y());
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        leftButtonPressed = false;
        despawnZoomRect();
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::spawnZoomRect(int xCenter, int yCenter, int width, int height) {
    int pixmapXCenter = xCenter / 5; // расследование показало, что делитель зависит от зума,
    int pixmapYCenter = yCenter / 3; // но вот как?..

    double zoom = scrollBar->value();

    QPixmap *pixmap = pc->createPixmap(pixmapXCenter, height - pixmapYCenter, width, height, zoom);
    zoomRect = scene()->addPixmap(*pixmap);

    zoomRect->setZValue(2);
    zoomRect->setX(xCenter);
    zoomRect->setY(yCenter);
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