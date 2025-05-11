#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "multithread_api.hpp"
#include <QGraphicsScene>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(MultithreadApi *api = new MultithreadApi(), QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        MultithreadApi *mApi;
};

#endif // MAINWINDOW_HPP
