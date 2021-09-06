#include <QTime>

#include "datamanager.h"

namespace
{
int weatherDailyProbe = 50;
int weatherTimerInterval = (1000 * 60 * 60 * 24)/(weatherDailyProbe/2.0);

int quoteTimerInterval = 1000 * 60 * 30;

int clockRefresh = 500;
}

rasp4home::data::DataManager::DataManager(rasp4home::data::WeatherDataManager::WeatherDataManagerInput input, rasp4home::ui::MainScreen *uiPtr, QObject *parent) : QObject(parent), mUi{uiPtr}, mWeatherDataManager{input}
{
    connect(&mWeatherDataRefreshTimer, &QTimer::timeout, this, &rasp4home::data::DataManager::updateWeatherData);
    //mWeatherDataRefreshTimer.start(1);

    connect(&mQuoteRefreshTimer, &QTimer::timeout, this, &rasp4home::data::DataManager::updateQuote);
    //mQuoteRefreshTimer.start(1);

    connect(&mClock, &QTimer::timeout, this, &rasp4home::data::DataManager::updateClock);
    mClock.start(1);

}

void rasp4home::data::DataManager::updateWeatherData()
{
    mWeatherDataManager.refreshAllData();
    mWeatherDataRefreshTimer.start(weatherTimerInterval);
}

void rasp4home::data::DataManager::updateQuote()
{
    mMotivationalQuoteManager.getQuote();
    mQuoteRefreshTimer.start(quoteTimerInterval);

}

void rasp4home::data::DataManager::updateClock()
{
    QTime time = QTime::currentTime();
    mUi->setTime(time.hour(),time.minute(),time.second());
    mClock.start(500);
}
