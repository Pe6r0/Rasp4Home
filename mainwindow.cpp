#include <QWidget>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Qt::WindowFlags flags{Qt::Window | Qt::FramelessWindowHint};
    setWindowFlags(flags);

    mMainWindowUi.setupUi(this);
    setupWidgets();

    //TODO: add global start
}

void MainWindow::setupWidgets()
{
    mWeather.setParent(mMainWindowUi.centralwidget);


    mWeather.start();
}
