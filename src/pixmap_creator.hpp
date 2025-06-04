#ifndef PIXMAP_CREATOR_H
#define PIXMAP_CREATOR_H

#include <QObject>
#include <QtGlobal>
#include <QPixmap>
#include <QPainter>
#include "gt_mndlbrt.hpp"
#include <QColor>
#include "color_picker.h"
#include <QGraphicsView>

#define DEFAULT_COLOR "green"

class PixmapCreator : public QObject{
        Q_OBJECT
    public:
        PixmapCreator(ColorPicker *color_picker, QGraphicsView* view);
        /*!
         * \brief Create pixmap to insert this into scene
         */
        QPixmap* createPixmap(size_t xCenterFrame = 250,
                              size_t yCenterFrame = 250,
                              int width = 500,
                              int height = 500,
                              double scale = 1.0);

    public slots:
            void changeColor(QColor color);
    private:
            QColor color;
            QGraphicsView *m_view;
};

#endif // PIXMAP_CREATOR_H