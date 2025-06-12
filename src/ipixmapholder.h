#include <QPixmap>


class IPixmapHolder {
    public:
        virtual void setPixmap(QPixmap *pixmap) = 0;
        virtual QPixmap* getPixmap() = 0;
};