#include <QApplication>
#include <QColor>
#include <QPalette>
#include <QLabel>
#include <QWidget>
#include <QBoxLayout>
#include "mainwindow.h"

namespace
{
const QColor textColor{180,180,180};
const QColor backgroundColor{33,33,33};
}

rasp4home::ui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    paletteSetup();

    QLabel label;
    label.setText("first line");
    label.setAlignment(Qt::AlignCenter);


    /*QLabel *label2 = new QLabel();
    label2->setText("second line");
    label2->setAlignment(Qt::AlignCenter);*/

    layout()->addWidget(&label);

    /*mLayout.addWidget(label, Qt::AlignCenter);
    mLayout.addSpacing(320);
    mLayout.addWidget(label2, Qt::AlignCenter);

    mLayout.setContentsMargins(20, 20, 20, 20);

    setLayout(&mLayout);*/
}

void rasp4home::ui::MainWindow::paletteSetup()
{
    setAutoFillBackground(true);
    auto palette = QApplication::palette();
    palette.setColor(QPalette::All, QPalette::Background, backgroundColor);
    palette.setColor(QPalette::All, QPalette::WindowText, textColor);

    setPalette(palette);
}

rasp4home::ui::MainWindow::~MainWindow()
{
}

