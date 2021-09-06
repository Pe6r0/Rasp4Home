#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>

#include "timedisplay.h"

namespace rasp4home
{
namespace ui
{
class MainScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MainScreen(QWidget *parent = nullptr);

    void setTime(int h, int m, int s);

private:
    void paletteSetup();

    TimeDisplay mTime;
    QWidget mWeather;
    QWidget mQuote;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MainScreen* getUI();
private:
    MainScreen mDisplay;
};

}
}
#endif // MAINWINDOW_H
