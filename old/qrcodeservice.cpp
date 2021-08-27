#include <QUrl>
#include <QUrlQuery>
#include <stdexcept>

#include <iostream>

#include "utils.h"

#include "qrcodeservice.h"


namespace {

const QUrl QR_API { "http://api.qrserver.com/v1/create-qr-code/" };

}

QRCodeService::QRCodeService(QLabel* out, QString data, QColor color, QColor background, QObject* parent)
    : QObject { parent }
{
    if (out == nullptr) {
        throw std::out_of_range("QRCodeService, null QLabel.");
    }
    mLabel.reset(out);
    auto img = *(out->pixmap());
    if (img.isNull()) {
        throw std::out_of_range("QRCodeService, null image. Fill with empty content.");
    }
    if (data.isEmpty()) {
        throw std::out_of_range("QRCodeService, empty data string");
    }
    if (img.width() != img.height()) {
        throw std::out_of_range("QRCodeService, image is not a square");
    }
    if (img.width() < 10) {
        throw std::out_of_range("QRCodeService, image is too small");
    }
    if (img.width() > 1000) {
        throw std::out_of_range("QRCodeService, image is too big");
    }
    QUrl url = QR_API;
    QUrlQuery query;
    query.addQueryItem("size", QString("%1x%1").arg(img.width()));
    query.addQueryItem("data", data);
    query.addQueryItem("color", color.name().replace("#", ""));
    query.addQueryItem("bgcolor", background.name(QColor::NameFormat::HexRgb).replace("#", ""));
    url.setQuery(query);

    mConnector.reset(new RestConnector(url));
    connect(&*mConnector, &RestConnector::updated, this, &QRCodeService::update);
    mConnector->start();
}

void QRCodeService::update()
{
    QPixmap pix { *mLabel->pixmap() };
    pix.loadFromData(mConnector->getReply(), "PNG");
    mLabel->setPixmap(pix);
}
