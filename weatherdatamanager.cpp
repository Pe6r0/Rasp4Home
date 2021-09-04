#include <string>
#include <exception>
#include <QNetworkAccessManager>
#include "weatherdatamanager.h"

namespace
{
    const std::string resourceURLCurrentConditionsBase{"http://dataservice.accuweather.com/currentconditions/v1/"};
    const std::string resourceURL1DayForecastBase{"http://dataservice.accuweather.com/forecasts/v1/daily/1day/"};

}

QUrl rasp4home::WeatherDataManager::buildCurrentConditionsRequest()
{
    QUrl request{resourceURLCurrentConditionsBase.c_str()};
}

rasp4home::WeatherDataManager::WeatherDataManager(std::string apikey, std::string location) : mAPIKey{apikey}, mLocationCode{location}
{
}

bool rasp4home::WeatherDataManager::refreshAllData()
{
    return true;
}
