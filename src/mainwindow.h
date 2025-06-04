#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include "gt_mndlbrt.hpp"
#include "graphicsview.h"
#include <QScrollBar>
#include <QLabel>
#include <QString>
#include "color_picker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        Ui::MainWindow* getUi();
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        GraphicsView *view;
        QScrollBar *scrollBar;
        ColorPicker *colorPicker;
        QLabel *zoomFactorLabel;
};

#endif // MAINWINDOW_H
