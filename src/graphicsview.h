#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include "pixmap_creator.hpp"
#include <QPointF>
#include <QPoint>
#include <QScrollBar>

class GraphicsView : public QGraphicsView {
    public:
        /*!
        \brief Constructor of class
        */
        GraphicsView(QWidget *parent = nullptr, QScrollBar *scrollBar = nullptr);

        /*!
        \brief group of mouse events to control occurance of
        special zoom rectangle
        */
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;

    private:
        double zoomFactor;
        bool leftButtonPressed;
        QGraphicsPixmapItem *zoomRect;
        void spawnZoomRect(int xCenter, int yCenter,
                           int width = 150, int height = 150);
        
        void moveZoomRect(int xCenter, int yCenter);
        void despawnZoomRect();
        QPointF mapPos(double x, double y);
        void test_pos(QMouseEvent *event);
        QScrollBar *scrollBar;
        PixmapCreator *pc;
};

#endif // GRAPHICSVIEW_H