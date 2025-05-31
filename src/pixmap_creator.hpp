#ifndef PIXMAP_CREATOR_H
#define PIXMAP_CREATOR_H

#include <QtGlobal>
#include <QPixmap>
#include <QPainter>
#include "gt_mndlbrt.hpp"
#include <QColor>

class PixmapCreator {
    public:
        /*!
         * \brief Create pixmap to insert this into scene
         */
        QPixmap* createPixmap(size_t xCenterFrame = 250,
                              size_t yCenterFrame = 250,
                              int width = 500,
                              int height = 500,
                              double scale = 1.0);
};

#endif // PIXMAP_CREATOR_H