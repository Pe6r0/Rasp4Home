#ifndef MOTIVATIONALQUOTEMANAGER_H
#define MOTIVATIONALQUOTEMANAGER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QByteArray>

#include "motivationalquote.h"

namespace rasp4home
{
namespace data
{
class MotivationalQuoteManager : public QObject
{
    Q_OBJECT
public:
    explicit MotivationalQuoteManager(QObject *parent = nullptr);
    void getQuote();
private:

    void readQuote(QByteArray response);

    QNetworkAccessManager mNetworkManager;
    MotivationalQuote mMotivationalQuote;

};
}
}

#endif // MOTIVATIONALQUOTEMANAGER_H
