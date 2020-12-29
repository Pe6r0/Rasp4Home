#include <QWidget>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Qt::WindowFlags flags{Qt::Window | Qt::FramelessWindowHint};
    setWindowFlags(flags);

    ui.reset(new Ui_MainWindow);
    ui->setupUi(this);
    setupWidgets();

}

void MainWindow::setupWidgets()
{
    mWeather.reset(new Weather{ui->mainwidget});

    mWeather->start();
}
