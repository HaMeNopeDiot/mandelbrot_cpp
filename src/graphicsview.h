#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QPixmap>
#include <QImage>
#include "multithread_api.hpp"

class GraphicsView : public QGraphicsView {
    public:
        GraphicsView(QWidget *parent = nullptr);
        void wheelEvent(QWheelEvent *event) override;
        void setApi(MultithreadApi *api);

    private:
        QGraphicsScene *mScene;
        QPixmap mPixmap;
        MultithreadApi *mApi;
        QImage *mImage;
        QGraphicsPixmapItem *pixmapItem;
};

#endif // GRAPHICSVIEW_H
