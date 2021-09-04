#ifndef WEATHERDATAMANAGER_H
#define WEATHERDATAMANAGER_H
#include <QUrl>

#include "weatherdata.h"

namespace rasp4home
{

class WeatherDataManager
{
public:
    WeatherDataManager(std::string APIKey, std::string location);
    bool refreshAllData();
    bool setLocation(std::string location);

private:
    QUrl buildCurrentConditionsRequest();

    WeatherData mWeatherData;
    std::string mAPIKey;
    std::string mLocationCode;
};
}

#endif // WEATHERDATAMANAGER_H
