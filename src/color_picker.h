#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QColorDialog>
#include <QWidget>


class ColorPicker : public QColorDialog {
	Q_OBJECT
public:
	explicit ColorPicker(QWidget *parent = nullptr);
};

#endif //COLORPICKER_H