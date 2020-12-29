#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QUrl>

#include "restconnector.h"

#include "ui_weather.h"

class Weather : public QWidget
{
    Q_OBJECT
public:
    explicit Weather(QWidget *parent = nullptr);

public slots:
    void start();
    //TODO: void stop();

private slots:
    void update();

private:
    void updateUI();
    void updateValues();

    std::shared_ptr<Ui_Weather> ui;
    RestConnector mCurrentWeather;
    RestConnector mForecast;

    //celsius
    float mCurrentTemperature{0.0f};
    float mMinTemperature{0.0f};
    float mMaxTemperature{0.0f};
};

#endif // WEATHER_H
