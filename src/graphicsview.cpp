#include "graphicsview.h"
#include "pixmap_creator.hpp"
#include <QPixmap>
#include <QGraphicsScene>

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
}

void GraphicsView::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() && Qt::ControlModifier) {
        double zoomInFactor = DEFAULT_ZOOM_FACTOR;
        double zoomOutFactor = 1 / DEFAULT_ZOOM_FACTOR;

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

        qInfo() << zoomFactor;

        PixmapCreator pc;
        QPixmap *pixmap = pc.createPixmap(event->position().x(), event->position().y(), zoomFactor);
        QGraphicsScene *scene = new QGraphicsScene();
        scene->addPixmap(*pixmap);

        setScene(scene);
    }
}