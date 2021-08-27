#ifndef QRCODESERVICE_H
#define QRCODESERVICE_H

#include <QObject>
#include <QPixmap>
#include <QColor>
#include <QString>
#include <QLabel>

#include <memory>

#include "restconnector.h"

class QRCodeService : public QObject
{
    Q_OBJECT
public:
    explicit QRCodeService(QLabel *out, QString data, QColor color, QColor background, QObject *parent = nullptr);

signals:

private:
    void update();
    std::shared_ptr<QLabel> mLabel;
    std::unique_ptr<RestConnector> mConnector;

};

#endif // QRCODESERVICE_H
