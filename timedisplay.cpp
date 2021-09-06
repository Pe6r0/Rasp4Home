#include <QBoxLayout>

#include "timedisplay.h"

rasp4home::ui::TimeDisplay::TimeDisplay(QWidget *parent) : QWidget(parent)
{
    //setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
    setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
    layout()->addWidget(&mHours);
    layout()->addWidget(&mSeparator);
    layout()->addWidget(&mMinutes);
    layout()->addWidget(&mSeconds);
}
