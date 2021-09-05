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
const auto resourceURL1DayForecastBase{"http://dataservice.accuweather.com/forecasts/v1/daily/1day/"};

//queries
const auto apikey = "apikey";
const auto details = "details";
const auto detailedRequest = "true";
const auto metric = "metric";
const auto metricRequest = "true";
}

QUrl rasp4home::data::WeatherDataManager::buildCurrentConditionsRequest()
{
    QUrl request{(resourceURLCurrentConditionsBase + mLocationCode).c_str()};
    QUrlQuery query;
    query.addQueryItem(apikey, mAPIKey.c_str());
    query.addQueryItem(details, detailedRequest);
    query.addQueryItem(apikey, metricRequest);
    request.setQuery(query);
    return request;
}

rasp4home::data::WeatherDataManager::WeatherDataManager(std::string apikey, std::string location, QObject *parent) : QObject(parent), mAPIKey{apikey}, mLocationCode{location}, mNetworkManager(this)
{

}

bool rasp4home::data::WeatherDataManager::refreshAllData()
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
            std::cout << "[refreshAllData] Problem reading current weather conditions." << std::endl; //TODO: error code add. make this into a function
        };
    });
    return true;
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
        std::cout << newData.timestamp.toString().toStdString() << std::endl;
        newData.location = "london";
        newData.summary = requestJsonParsed[0].at("WeatherText");
        newData.raining = requestJsonParsed[0].at("HasPrecipitation");
        newData.daytime = requestJsonParsed[0].at("IsDayTime");
        newData.temperature = requestJsonParsed[0].at("Temperature").at("Metric").at("Value");

        std::cout << newData.temperature << std::endl;

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
