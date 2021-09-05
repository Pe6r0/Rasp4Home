#include <iostream>
#include <string>
#include <exception>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <nlohmann/json.hpp>

#include "weatherdatamanager.h"
#include "weatherdata.h"

namespace
{
const auto resourceURLCurrentConditionsBase{"http://dataservice.accuweather.com/currentconditions/v1/"};
const auto resourceURL1DayForecastBase{"http://dataservice.accuweather.com/forecasts/v1/hourly/12hour/"};

//queries
const auto apikey = "apikey";
const auto details = "details";
const auto detailedRequestCurrent = "true";
const auto detailedRequestForecast = "false";
const auto metric = "metric";
const auto metricRequest = "true";
}

QUrl rasp4home::data::WeatherDataManager::buildCurrentConditionsRequest()
{
    QUrl request{(resourceURLCurrentConditionsBase + mLocationCode).c_str()};
    QUrlQuery query;
    query.addQueryItem(apikey, mAPIKey.c_str());
    query.addQueryItem(details, detailedRequestCurrent);
    query.addQueryItem(apikey, metricRequest);
    request.setQuery(query);
    return request;
}

QUrl rasp4home::data::WeatherDataManager::build12HourForecastRequest()
{
    QUrl request{(resourceURL1DayForecastBase + mLocationCode).c_str()};
    QUrlQuery query;
    query.addQueryItem(apikey, mAPIKey.c_str());
    query.addQueryItem(details, detailedRequestForecast);
    query.addQueryItem(apikey, metricRequest);
    request.setQuery(query);
    return request;
}

rasp4home::data::WeatherDataManager::WeatherDataManager(WeatherDataManagerInput input, QObject *parent) : QObject(parent), mAPIKey{input.APIKey}, mLocationCode{input.location}, mNetworkManager(this)
{}

void rasp4home::data::WeatherDataManager::refreshAllData()
{
    refreshCurrentWeather();
    refreshWeatherDailyForecast();
}

void rasp4home::data::WeatherDataManager::refreshCurrentWeather()
{
    QNetworkRequest currentConditionsRequest{buildCurrentConditionsRequest()};
    QNetworkReply *currentConditionsReply = mNetworkManager.get(currentConditionsRequest);
    connect(currentConditionsReply, &QNetworkReply::finished, this, [=]() {
        if(currentConditionsReply->error() == QNetworkReply::NoError)
        {
            readCurrentConditions(currentConditionsReply->readAll());
        }
        else
        {
            std::cout << "[refreshAllData] Problem reading current weather conditions. (" << currentConditionsReply->error()  << ")"<< std::endl;
        };
    });
}

void rasp4home::data::WeatherDataManager::refreshWeatherDailyForecast()
{
    QNetworkRequest forecastRequest{build12HourForecastRequest()};
    QNetworkReply *forecastReply = mNetworkManager.get(forecastRequest);
    connect(forecastReply, &QNetworkReply::finished, this, [=]() {
        if(forecastReply->error() == QNetworkReply::NoError)
        {
            readForecast(forecastReply->readAll());
        }
        else
        {
            std::cout << "[refreshAllData] Problem reading weather forecast. (" << forecastReply->error()  << ")" << std::endl;
        };
    });
}

void rasp4home::data::WeatherDataManager::readCurrentConditions(QByteArray response)
{
    std::cout << "[readCurrentConditions] received: " << response.toStdString() << std::endl;
    nlohmann::json requestJsonParsed = nlohmann::json::parse(response.toStdString());

    rasp4home::data::WeatherData::CurrentWeatherData newData;
    try
    {
        int time = requestJsonParsed[0].at("EpochTime");
        newData.timestamp.setTime_t(time);
        newData.location = "london";
        newData.summary = requestJsonParsed[0].at("WeatherText");
        newData.raining = requestJsonParsed[0].at("HasPrecipitation");
        newData.daytime = requestJsonParsed[0].at("IsDayTime");
        newData.temperature = requestJsonParsed[0].at("Temperature").at("Metric").at("Value");
        newData.humidity = requestJsonParsed[0].at("RelativeHumidity");
        newData.windDirection = requestJsonParsed[0].at("Wind").at("Direction").at("Degrees");
        newData.windSpeed = requestJsonParsed[0].at("Wind").at("Speed").at("Metric").at("Value");
        newData.windGustsSpeed = requestJsonParsed[0].at("WindGust").at("Speed").at("Metric").at("Value");
        newData.UVIndex = requestJsonParsed[0].at("UVIndex");
        newData.visibility = requestJsonParsed[0].at("Visibility").at("Metric").at("Value");
        newData.cloudCover = requestJsonParsed[0].at("CloudCover");
        newData.precipitation = requestJsonParsed[0].at("Precip1hr").at("Metric").at("Value");

        mWeatherData.setCurrentWeatherData(newData);
    }  catch (std::exception &e) {
        std::cout << "[readCurrentConditions]: Problem parsing data. " << e.what() << std::endl;
    }

}

void rasp4home::data::WeatherDataManager::readForecast(QByteArray response)
{
    std::cout << "[readForecast] received: " << response.toStdString() << std::endl;
    nlohmann::json requestJsonParsed = nlohmann::json::parse(response.toStdString());
    try
    {
        std::vector<rasp4home::data::WeatherData::WeatherForecast> forecast;

        QDateTime currentDate = QDateTime::currentDateTime();
        for(int i=0; i <= 11; ++i)
        {
            rasp4home::data::WeatherData::WeatherForecast forecastUnit;
            forecastUnit.timestamp = currentDate;
            int time = requestJsonParsed[i].at("EpochDateTime");
            forecastUnit.predictedTime.setTime_t(time);
            forecastUnit.location = "london";
            forecastUnit.summary = requestJsonParsed[i].at("IconPhrase");
            forecastUnit.raining = requestJsonParsed[i].at("HasPrecipitation");
            forecastUnit.daytime = requestJsonParsed[i].at("IsDaylight");
            forecastUnit.temperature = requestJsonParsed[i].at("Temperature").at("Value");
            forecastUnit.precipitationProbability = requestJsonParsed[i].at("PrecipitationProbability");
            forecast.emplace_back(forecastUnit);
        }
        mWeatherData.setWeatherForecast(forecast);

    }  catch (std::exception &e) {
        std::cout << "[readForecast]: Problem parsing data. " << e.what() << std::endl;
    }

}
