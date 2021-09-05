#include <iostream>

#include <QNetworkRequest>
#include <QNetworkReply>

#include <nlohmann/json.hpp>

#include "motivationalquotemanager.h"


namespace
{
const auto quoteURLBase{"http://quotes.rest/qod/"};
}

rasp4home::data::MotivationalQuoteManager::MotivationalQuoteManager(QObject *parent) : QObject(parent), mNetworkManager(this)
{}


void rasp4home::data::MotivationalQuoteManager::getQuote()
{
    QNetworkRequest quoteRequest{QUrl{quoteURLBase}};
    QNetworkReply *quoteReply = mNetworkManager.get(quoteRequest);
    connect(quoteReply, &QNetworkReply::finished, this, [=]() {
        if(quoteReply->error() == QNetworkReply::NoError)
        {
            readQuote(quoteReply->readAll());
        }
        else
        {
            std::cout << "[getQuote] Problem reading current weather conditions. (" << quoteReply->error()  << ")"<< std::endl;
        };
    });
}

void rasp4home::data::MotivationalQuoteManager::readQuote(QByteArray response)
{
    std::cout << "[readQuote] received: " << response.toStdString() << std::endl;
    nlohmann::json requestJsonParsed = nlohmann::json::parse(response.toStdString());

    rasp4home::data::MotivationalQuote::Quote newQuote;
    try
    {
        newQuote.quote = requestJsonParsed.at("contents")["quotes"][0].at("quote");
        newQuote.quote = requestJsonParsed.at("contents")["quotes"][0].at("author");

    }  catch (std::exception &e) {
        std::cout << "[readQuote]: Problem parsing data. " << e.what() << std::endl;
    }
    mMotivationalQuote.setQuote(newQuote);

}
