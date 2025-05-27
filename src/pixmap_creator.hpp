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
        QPixmap* createPixmap(size_t xCenterFrame = 512,
                              size_t yCenterFrame = 400,
                              int width = 1024,
                              int height = 1024,
                              double scale = 1.0);
};

#endif // PIXMAP_CREATOR_H