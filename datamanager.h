#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QTimer>

#include "weatherdatamanager.h"

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
signals:

private:
    rasp4home::data::WeatherDataManager mWeatherDataManager;
    QTimer mWeatherDataRefreshTimer;
};
}
}
#endif // DATAMANAGER_H
