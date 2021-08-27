#include <QPixmap>
#include <QLabel>

#include <iostream>
#include <stdexcept>

#include "utils.h"
#include "wiki.h"

Wiki::Wiki(QWidget* parent)
    : QWidget(parent)
{
    ui.reset(new Ui_Wiki);
    ui->setupUi(this);
}

void Wiki::start()
{
    QPixmap imgs{130,130};
    ui->QRCode->setPixmap(imgs);

    try {
        mImgFetch.reset(new QRCodeService{ui->QRCode, "www.wikipedia.com", globals::HINT_COLOR, globals::BACKGROUND_COLOR});
    }
    catch (const std::out_of_range& e) {
        std::cout << "[Wiki::start()]: " << e.what() << std::endl;
    }

}

