#include "datamanager.h"

namespace
{
    int weatherDailyProbe = 50;
    int weatherTimerInterval = (1000 * 60 * 60 * 24)/(weatherDailyProbe/2.0);
}

rasp4home::data::DataManager::DataManager(rasp4home::data::WeatherDataManager::WeatherDataManagerInput input, QObject *parent) : QObject(parent), mWeatherDataManager{input}
{
    connect(&mWeatherDataRefreshTimer, &QTimer::timeout, this, &rasp4home::data::DataManager::updateWeatherData);
    mWeatherDataRefreshTimer.start(1);

}

void rasp4home::data::DataManager::updateWeatherData()
{
    mWeatherDataManager.refreshAllData();
    mWeatherDataRefreshTimer.start(weatherTimerInterval);
}
