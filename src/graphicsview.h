#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QWheelEvent>

class GraphicsView : public QGraphicsView {
    public:
        GraphicsView(QWidget *parent = nullptr);
        void wheelEvent(QWheelEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;

    private:
        double zoomFactor;
        double prevX;
        double prevY;
        bool leftButtonPressed;
        QGraphicsRectItem *zoomRect;
        void spawnZoomRect(int xCenter, int yCenter,
                           int width = 100, int height = 100);
        void moveZoomRect(int xCenter, int yCenter);
        void despawnZoomRect();
};

#endif // GRAPHICSVIEW_H