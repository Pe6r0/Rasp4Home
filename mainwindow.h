#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

#include "weather.h"
#include "ui_main.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupWidgets();

    Ui_MainWindow mMainWindowUi;
    Weather mWeather;
    QNetworkAccessManager mNetworkManager;
};
#endif // MAINWINDOW_H
