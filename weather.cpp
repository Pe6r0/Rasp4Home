#include <iostream>

#include "mainwindow.h"
#include "weather.h"

namespace {
int REFRESH_CURRENT_COOLDOWN { 860 };
QUrl API_CURRENT_ACCESS { "http://dataservice.accuweather.com/currentconditions/v1/328328/?apikey=GUHqOXBTc7f4Kdz0AuoD1iGwPdkImWB3" };

int REFRESH_FORECAST_COOLDOWN { 860 };
QUrl API_FORECAST_ACCESS { "http://dataservice.accuweather.com/forecasts/v1/daily/1day/328328?apikey=GUHqOXBTc7f4Kdz0AuoD1iGwPdkImWB3&metric=true" };
}

Weather::Weather(QWidget* parent)
    : QWidget(parent), mCurrentWeather{API_CURRENT_ACCESS, REFRESH_CURRENT_COOLDOWN}, mForecast{API_FORECAST_ACCESS, REFRESH_FORECAST_COOLDOWN}
{
    ui.reset(new Ui_Weather);
    ui->setupUi(this);
    connect(&mCurrentWeather, &RestConnector::updated, this, &Weather::update);
    connect(&mForecast, &RestConnector::updated, this, &Weather::update);
}

void Weather::start()
{
    mCurrentWeather.start();
    mForecast.start();
}

void Weather::update()
{
    mForecast.getValue("test");
}

void Weather::updateValues()
{
    /*if (reply == nullptr) {
        throw(std::out_of_range { "Weather::updateValues: reply is nullptr." });
        return;
    }
    mCurrentTemperature++;
    auto text = reply->readAll();
    ui->currentTemperature->setText(QString::fromUtf8(text));

    updateUI(); */
}

void Weather::updateUI()
{
    //ui.currentTemperature->setText(QString::number(mCurrentTemperature));
    //ui.minMaxTemperature->setText(QString("%1-%2").arg(QString::number(mMinTemperature)).arg(QString::number(mMaxTemperature)));
}
