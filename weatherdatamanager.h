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
    WeatherDataManager(std::string APIKey, std::string location, QObject *parent = nullptr);
    bool refreshAllData();

public slots:
    void readCurrentConditions(QByteArray data);

private:
    QUrl buildCurrentConditionsRequest();

    QNetworkAccessManager mNetworkManager;
    WeatherData mWeatherData;
    std::string mAPIKey;
    std::string mLocationCode;
};
}
}

#endif // WEATHERDATAMANAGER_H
