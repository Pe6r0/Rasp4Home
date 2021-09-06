#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QTimer>
#include <QPointer>

#include "mainwindow.h"
#include "weatherdatamanager.h"
#include "motivationalquotemanager.h"

namespace rasp4home
{
namespace data
{
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(WeatherDataManager::WeatherDataManagerInput input, ui::MainScreen *uiPtr, QObject *parent = nullptr);

public slots:
        void updateWeatherData();
        void updateQuote();
        void updateClock();
signals:

private:
    WeatherDataManager mWeatherDataManager;
    QTimer mWeatherDataRefreshTimer;

    MotivationalQuoteManager mMotivationalQuoteManager;
    QTimer mQuoteRefreshTimer;
    QTimer mClock;

    QPointer<ui::MainScreen> mUi;

};
}
}
#endif // DATAMANAGER_H
