#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QTimer>

#include "ui_weather.h"

class Weather : public QWidget
{
    Q_OBJECT
public:
    int REFRESH_COOLDOWN{10};
    explicit Weather(QWidget *parent = nullptr);

private slots:
    void update();

private:
    QTimer mTimer;
    Ui_Weather ui;
};

#endif // WEATHER_H
