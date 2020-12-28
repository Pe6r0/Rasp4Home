#include <QWidget>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Qt::WindowFlags flags{Qt::Window | Qt::FramelessWindowHint};
    setWindowFlags(flags);

    mMainWindowUi.setupUi(this);
    setupWidgets();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupWidgets()
{
    mWeather.setParent(mMainWindowUi.centralwidget);
}
