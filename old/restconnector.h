#ifndef RESTCONNECTOR_H
#define RESTCONNECTOR_H

#include <string>

#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QNetworkAccessManager>

//reponsible for refreshing content
class RestConnector : public QObject
{
    Q_OBJECT
public:
    explicit RestConnector(QUrl API, int refreshSeconds = -1);
    const QByteArray &getReply() const;

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
    QByteArray mReply;
};

#endif // RESTCONNECTOR_H
