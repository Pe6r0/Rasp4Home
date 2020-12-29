#ifndef RESTCONNECTOR_H
#define RESTCONNECTOR_H

#include <string>

#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QNetworkAccessManager>

#include <QJsonObject>

//reponsible for refreshing content
class RestConnector : public QObject
{
    Q_OBJECT
public:
    RestConnector(QUrl API, int refreshSeconds = -1);
    QJsonObject getJsonObj() const;

signals:
    void updated();

public slots:
    void query();
    void start();
    void pause();

private:
    void updateValues(QNetworkReply* reply);

    QUrl mUrl;
    QTimer mRefreshTimer;
    QNetworkAccessManager mNetworkMngr;
    QJsonObject mJObject; //include array etc
};

#endif // RESTCONNECTOR_H
