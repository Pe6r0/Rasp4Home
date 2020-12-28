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
    ~MainWindow(){};
    QNetworkAccessManager &getNetworkManager(){ return mNetworkManager; };

private:
    void setupWidgets();

    Ui_MainWindow mMainWindowUi;
    QNetworkAccessManager mNetworkManager;
    Weather mWeather;
};
#endif // MAINWINDOW_H
