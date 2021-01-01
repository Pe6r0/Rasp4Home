#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QByteArray>

#include <iostream>
#include <vector>

#include "restconnector.h"

RestConnector::RestConnector(QUrl API, int refreshSeconds)
    : mUrl { API }
{
    connect(&mNetworkMngr, &QNetworkAccessManager::finished, this,
        &RestConnector::updateValues);
    if (refreshSeconds != -1) {
        mRefreshTimer.setInterval(refreshSeconds * 1000);
        connect(&mRefreshTimer, &QTimer::timeout, this, &RestConnector::query);
    } else {
        mRefreshTimer.setInterval(10);
        mRefreshTimer.setSingleShot(true);
    }
}

const QByteArray &RestConnector::getReply() const
{
    return mReply;
}

void RestConnector::start()
{
    if(!mRefreshTimer.isSingleShot()){
        mRefreshTimer.start();
    }
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
        std::cout << "[RestConnector::updateValues]: Network Reply Error: " << reply->error() << std::endl;
        return;
    }
    mReply = reply->readAll();
    std::cout << "[RestConnector::updateValues]: Network Reply: " << QString::fromUtf8(mReply).toStdString() << std::endl;
    emit updated();
}

void RestConnector::query()
{
    std::cout << "[RestConnector::query()]: Attempting to contact: " << mUrl.toString().toStdString() << std::endl;
    QNetworkRequest req(mUrl);
    mNetworkMngr.get(req);
}
