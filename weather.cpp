#include <iostream>
#include <string>
#include <time.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "mainwindow.h"
#include "utils.h"
#include "weather.h"

namespace {
static const std::string APIWEATHER { "GUHqOXBTc7f4Kdz0AuoD1iGwPdkImWB3" };
static const std::string LOCATION { "328328" };
int REFRESH_CURRENT_COOLDOWN { 860 };
QUrl API_CURRENT_ACCESS { "http://dataservice.accuweather.com/currentconditions/v1/328328/?apikey=GUHqOXBTc7f4Kdz0AuoD1iGwPdkImWB3" };

int REFRESH_FORECAST_COOLDOWN { 860 };
QUrl API_FORECAST_ACCESS { "http://dataservice.accuweather.com/forecasts/v1/daily/1day/328328?apikey=GUHqOXBTc7f4Kdz0AuoD1iGwPdkImWB3&metric=true" };
}

Weather::Weather(QWidget* parent)
    : QWidget(parent)
    , mCurrentWeather { API_CURRENT_ACCESS, REFRESH_CURRENT_COOLDOWN }
    //, mForecast { API_FORECAST_ACCESS, REFRESH_FORECAST_COOLDOWN }
{
    ui.reset(new Ui_Weather);
    ui->setupUi(this);
    connect(&mCurrentWeather, &RestConnector::updated, this, &Weather::updateCurrent);
    //connect(&mForecast, &RestConnector::updated, this, &Weather::update);

    ui->label->setText(globals::addColorTags(ui->label->text(), globals::TEXT_COLOR));
}

void Weather::start()
{
    mCurrentWeather.start();
    //mForecast.start();
}

void Weather::updateCurrent()
{
    auto reply = mCurrentWeather.getReply();
    auto doc = QJsonDocument::fromJson(reply);

    if (doc.isEmpty()) {
        std::cout << "[RestConnector::updateValues]: Json Document is empty." << std::endl;
        return;
    }
    if (doc.isNull()) {
        std::cout << "[RestConnector::updateValues]: Json Document is null." << std::endl;
        return;
    }

    if (doc.isArray()) {
        auto obj = doc.array().at(0).toObject();
        ////
        /*[
          {
            "LocalObservationDateTime": "2021-01-01T19:51:00+00:00",
            "EpochTime": 1609530660,
            "WeatherText": "Mostly cloudy",
            "WeatherIcon": 38,
            "HasPrecipitation": false,
            "PrecipitationType": null,
            "IsDayTime": false,
            "Temperature": {
              "Metric": {
                "Value": 4.1,
                "Unit": "C",
                "UnitType": 17
              },
              "Imperial": {
                "Value": 39,
                "Unit": "F",
                "UnitType": 18
              }
            },
            "MobileLink": "http://m.accuweather.com/en/gb/london/ec4a-2/current-weather/328328?lang=en-us",
            "Link": "http://www.accuweather.com/en/gb/london/ec4a-2/current-weather/328328?lang=en-us"
          }
        ]*/
        auto time = obj.find("EpochTime").value().toInteger();
        auto raining = obj.find("HasPrecipication").value().toBool();
        auto link = obj.find("Link").value().toString();
        auto precipitationType = obj.find("PrecipitationType").value().toString();
        auto temperature = obj.find("Temperature").value().toObject().find("Metric").value().toObject().find("Value").value().toDouble();
        auto text = obj.find("WeatherText").value().toString();
        //TODO: add dynamic update

        QDateTime t;
        t.setSecsSinceEpoch(time);

        mCurrentState = CurrentState { temperature, text, "London, United Kingdom", t, raining, link };
        updateUI();
    }
}

//void Weather::updateForecast(const QByteArray & reply)
//{

//}

void Weather::updateUI()
{
    if (mCurrentState.has_value()) {
        ui->currentTemperature->setText(globals::addColorTags(QString::number(mCurrentState.value().mCurrentTemperature), globals::HINT_COLOR));
        ui->weatherText->setText(globals::addColorTags(mCurrentState.value().mCurrentStatus, globals::HINT_COLOR));
        ui->lastUpdatedLabel->setText(globals::addColorTags(QString { "Last updated on: %1" }.arg(mCurrentState.value().mTime.toString(Qt::DateFormat::ISODate)), globals::TEXT_COLOR));
        ui->placeLabel->setText(globals::addColorTags(mCurrentState.value().mPlace, globals::TEXT_COLOR));
    }
}
