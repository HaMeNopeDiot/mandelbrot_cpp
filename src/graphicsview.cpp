#include "graphicsview.h"
#include "pixmap_creator.hpp"
#include <QPixmap>
#include <QGraphicsScene>
#include <QPointF>

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
    prevX = 512;
    prevY = 512;
}

void GraphicsView::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() && Qt::ControlModifier) {
        double zoomInFactor = DEFAULT_ZOOM_FACTOR;
        double zoomOutFactor = 1 / DEFAULT_ZOOM_FACTOR;

        // QPointF oldPos = mapToScene(event->position().toPoint());

        if (event->angleDelta().y() > 0) {
            if (zoomFactor < MAX_ZOOM_IN) {
                zoomFactor += zoomInFactor;
            }
            else {
                zoomFactor = MAX_ZOOM_IN;
            }
        }
        else {
            if (zoomFactor > MAX_ZOOM_OUT) {
                zoomFactor -= DEFAULT_ZOOM_FACTOR;
            }
            else {
                zoomFactor = MAX_ZOOM_OUT;
            }
        }

        PixmapCreator pc;

        QPointF newPos = event->position();

        // qInfo() << "Новая позиция: " << newPos;

        QPixmap *pixmap = pc.createPixmap(380, 350, 1024, 1024, zoomFactor);
        QGraphicsScene *scene = new QGraphicsScene();
        scene->addPixmap(*pixmap);


        setScene(scene);
    }
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        leftButtonPressed = true;
        spawnZoomRect(event->position().x(), event->position().y());
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (leftButtonPressed) {
        double xCenter = event->position().x();
        double yCenter = event->position().y();
        moveZoomRect(xCenter, yCenter);
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        leftButtonPressed = false;
        despawnZoomRect();
    }
}

void GraphicsView::spawnZoomRect(int xCenter, int yCenter, int width, int height) {
    scene().addRect(xCenter, yCenter, width, height);

}

void GraphicsView::moveZoomRect(int xCenter, int yCenter) {}
void GraphicsView::despawnZoomRect() {}