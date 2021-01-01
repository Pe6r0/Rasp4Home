#ifndef WIKI_H
#define WIKI_H

#include <QWidget>
#include <memory>

#include "qrcodeservice.h"

#include "ui_wiki.h"

class Wiki : public QWidget
{
    Q_OBJECT
public:
    explicit Wiki(QWidget *parent = nullptr);
    void start();

signals:
private:

    std::shared_ptr<Ui_Wiki> ui;
    std::unique_ptr<QRCodeService> mImgFetch;
};

#endif // WIKI_H
