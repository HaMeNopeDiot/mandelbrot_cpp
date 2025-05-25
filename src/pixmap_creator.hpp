#include <QtGlobal>
#include <QPixmap>
#include <QPainter>
#include "gt_mndlbrt.hpp"
#include <QColor>

class PixmapCreator {
    public:
        /*
         * \brief Create pixmap to insert this into scene
         */
        QPixmap* createPixmap(size_t xCenterFrame = 512, size_t yCenterFrame = 512, double scale = 1.0);
};
