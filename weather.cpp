#include <iostream>

#include <QNetworkRequest>
#include <QNetworkReply>

#include "mainwindow.h"
#include "weather.h"


Weather::Weather(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(update()));
    connect(&mNetworkManager, &QNetworkAccessManager::finished, this, &Weather::updateValues);
    mTimer.setInterval(REFRESH_COOLDOWN * 1000);
}

void Weather::start()
{
    update();
}

void Weather::update()
{
    sendRequests();

    mTimer.start();
}

void Weather::sendRequests()
{
    QNetworkRequest req(API_ACCESS);
    mNetworkManager.get(req);
}

void Weather::updateValues(QNetworkReply *reply)
{
    if(reply == nullptr)
    {
        throw(std::out_of_range{"Weather::updateValues: reply is nullptr."});
        return;
    }
    mCurrentTemperature++;
    auto text = reply->readAll();
    ui.currentTemperature->setText(QString::fromUtf8(text));

    updateUI();
}

void Weather::updateUI()
{
    //ui.currentTemperature->setText(QString::number(mCurrentTemperature));
    //ui.minMaxTemperature->setText(QString("%1-%2").arg(QString::number(mMinTemperature)).arg(QString::number(mMaxTemperature)));
}
