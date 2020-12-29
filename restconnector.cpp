#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>

#include <QJsonArray>
#include <QJsonDocument>

#include <iostream>
#include <vector>

#include "restconnector.h"

RestConnector::RestConnector(QUrl API, int refreshSeconds)
    : mUrl { API }
{
    connect(&mNetworkMngr, &QNetworkAccessManager::finished, this,
        &RestConnector::updateValues);
    connect(&mRefreshTimer, &QTimer::timeout, this, &RestConnector::query);
    if (refreshSeconds != -1) {
        mRefreshTimer.setInterval(refreshSeconds * 1000);
    } else {
        mRefreshTimer.setSingleShot(true);
        mRefreshTimer.setInterval(0);
    }
}

QJsonObject RestConnector::getJsonObj() const
{
    return mJObject;
}

void RestConnector::start()
{
    mRefreshTimer.start();
    query();
}

void RestConnector::pause()
{
    mRefreshTimer.stop();
}

void RestConnector::updateValues(QNetworkReply* reply)
{
    if (reply == nullptr) {
        std::cout << "[RestConnector::updateValues]: nullptr reply." << std::endl;
        return;
    }
    if (reply->error() != QNetworkReply::NoError) {
        std::cout << "[RestConnector::updateValues]: Network Reply Error: " << reply->error();
        return;
    }
    auto text = reply->readAll();
    std::cout << "[RestConnector::updateValues]: Network Reply: " << QString::fromUtf8(text).toStdString() << std::endl;

    auto doc = QJsonDocument::fromJson(text);

    if (doc.isEmpty()) {
        std::cout << "[RestConnector::updateValues]: Json Document is empty." << std::endl;
        return;
    }
    if (doc.isNull()) {
        std::cout << "[RestConnector::updateValues]: Json Document is null." << std::endl;
        return;
    }

    if (doc.isArray()) {
        //TODO
    }

    if (doc.isObject()) {
        mJObject = doc.object();
        //TODO reset array
    }
    emit updated();
}

void RestConnector::query()
{
    std::cout << "[RestConnector::query()]: Attempting to contact: " << mUrl.toString().toStdString() << std::endl;
    QNetworkRequest req(mUrl);
    mNetworkMngr.get(req);
}
