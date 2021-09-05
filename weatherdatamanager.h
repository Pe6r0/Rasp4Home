#ifndef WEATHERDATAMANAGER_H
#define WEATHERDATAMANAGER_H
#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QByteArray>

#include "weatherdata.h"

namespace rasp4home
{
namespace data
{
class WeatherDataManager : public QObject
{
    Q_OBJECT
public:

    struct WeatherDataManagerInput
    {
        std::string APIKey;
        std::string location;
    };

    WeatherDataManager(WeatherDataManagerInput input, QObject *parent = nullptr);
    void refreshAllData();
    void refreshCurrentWeather();
    void refreshWeatherDailyForecast();

private:
    void readCurrentConditions(QByteArray data);
    void readForecast(QByteArray data);
    QUrl buildCurrentConditionsRequest();
    QUrl build12HourForecastRequest();

    QNetworkAccessManager mNetworkManager;
    WeatherData mWeatherData;
    std::string mAPIKey;
    std::string mLocationCode;
};
}
}

#endif // WEATHERDATAMANAGER_H
