#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QTimer>
#include <QUrl>

#include <QNetworkAccessManager>

#include "ui_weather.h"

class Weather : public QWidget
{
    Q_OBJECT
public:
    explicit Weather(QWidget *parent = nullptr);

public slots:
    void start();
    //void stop();

private slots:
    void update();

private:
    int REFRESH_COOLDOWN{10};
    QUrl API_ACCESS{"http://dataservice.accuweather.com/locations/v1/cities/search?apikey=GUHqOXBTc7f4Kdz0AuoD1iGwPdkImWB3&q=London"};

    void updateUI();
    void updateValues(QNetworkReply *reply);

    void sendRequests();

    QTimer mTimer;
    Ui_Weather ui;
    QNetworkAccessManager mNetworkManager;

    //celsius
    float mCurrentTemperature{0.0f};
    float mMinTemperature{0.0f};
    float mMaxTemperature{0.0f};
};

#endif // WEATHER_H
