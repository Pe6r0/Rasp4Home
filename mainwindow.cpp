#include <QApplication>
#include <QColor>
#include <QPalette>
#include <QFont>
#include <QBoxLayout>
#include "mainwindow.h"

namespace
{
const float Orange = 0xE95420;
const float WarmGrey = 0xAEA79F;
const float CoolGrey = 0x333333;
const float Aubergine = 0x772953;

const QFont sansFont("Helvetica [Cronyx]", 12);
}

rasp4home::ui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mDisplay(this)
{
    setCentralWidget(&mDisplay);
}

rasp4home::ui::MainWindow::~MainWindow()
{
}

rasp4home::ui::MainScreen* rasp4home::ui::MainWindow::getUI()
{
    return &mDisplay;
}

/////

rasp4home::ui::MainScreen::MainScreen(QWidget *parent) : QWidget(parent)
{
    paletteSetup();
    setLayout(new QBoxLayout(QBoxLayout::TopToBottom));


    auto tmpfont = sansFont;
    tmpfont.setPointSize(30);
    mTime.mHours.setFont(tmpfont);
    mTime.mSeparator.setFont(tmpfont);
    mTime.mMinutes.setFont(tmpfont);
    tmpfont.setPointSize(10);
    mTime.mSeconds.setFont(tmpfont);
    mTime.layout()->setAlignment(Qt::AlignBottom);
    layout()->addWidget(&mTime);


    layout()->addWidget(&mWeather);


    layout()->addWidget(&mQuote);

}

void rasp4home::ui::MainScreen::paletteSetup()
{
    setAutoFillBackground(true);
    auto palette = QApplication::palette();
    palette.setColor(QPalette::All, QPalette::Background, QColor(Aubergine));
    palette.setColor(QPalette::All, QPalette::WindowText, QColor(Orange));
    setPalette(palette);
}

void  rasp4home::ui::MainScreen::setTime(int h, int m, int s)
{
    mTime.mHours.setText(QStringLiteral("%1").arg(h, 2, 10, QLatin1Char('0')));
    mTime.mMinutes.setText(QStringLiteral("%1").arg(m, 2, 10, QLatin1Char('0')));
    mTime.mSeconds.setText(QStringLiteral("%1").arg(s, 2, 10, QLatin1Char('0')));
    if(s%2 == 0){
        mTime.mSeparator.setText(" ");
    } else{
        mTime.mSeparator.setText(":");
    }
}


