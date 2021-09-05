#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QTimer>

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
    explicit DataManager(WeatherDataManager::WeatherDataManagerInput input, QObject *parent = nullptr);

public slots:
        void updateWeatherData();
        void updateQuote();
signals:

private:
    WeatherDataManager mWeatherDataManager;
    QTimer mWeatherDataRefreshTimer;

    MotivationalQuoteManager mMotivationalQuoteManager;
    QTimer mQuoteRefreshTimer;

};
}
}
#endif // DATAMANAGER_H
