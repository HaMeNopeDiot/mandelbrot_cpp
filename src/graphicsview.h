#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class GraphicsView : public QGraphicsView {
    public:
        GraphicsView(QWidget *parent = nullptr);
        void wheelEvent(QWheelEvent *event) override;

    private:
        double zoomFactor;
};

#endif // GRAPHICSVIEW_H