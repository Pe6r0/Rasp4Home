#ifndef WEATHER_H
#define WEATHER_H

#include <QDateTime>
#include <optional>

#include <QUrl>
#include <QWidget>

#include "restconnector.h"

#include "ui_weather.h"

class Weather : public QWidget {
    Q_OBJECT
public:
    explicit Weather(QWidget* parent = nullptr);

public slots:
    void start();
    //TODO: void stop();

private:
    void updateUI();
    void updateCurrent();

    std::shared_ptr<Ui_Weather> ui;
    RestConnector mCurrentWeather;
    //RestConnector mForecast;

    struct CurrentState {
        CurrentState(double temp, QString status, QString place, QDateTime eTime, bool rain, QString link)
            : mCurrentTemperature { temp }
            , mCurrentStatus { std::move(status) }
            , mPlace { std::move(place) }
            , mTime { eTime }
            , mIsItRaining { rain }
            , mLink { link }
        {
        }
        //celsius
        double mCurrentTemperature;
        QString mCurrentStatus;
        QString mPlace;
        QDateTime mTime;
        bool mIsItRaining;
        QString mLink;
    };

    std::optional <CurrentState> mCurrentState;
};

#endif // WEATHER_H
