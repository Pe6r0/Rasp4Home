#include "weather.h"

Weather::Weather(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(update()));

    mTimer.setInterval(REFRESH_COOLDOWN);
    mTimer.start();
}

void Weather::update()
{
    ui.currentTemperature->setText("here");

    mTimer.start();
}
