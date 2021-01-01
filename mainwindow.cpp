#include <QWidget>

#include "utils.h"

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
    //mWeather.reset(new Weather{ui->frame});
    mWiki.reset(new Wiki{ui->frame});

    //mWeather->start();
    mWiki->start();
}
