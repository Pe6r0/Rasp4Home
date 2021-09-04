#include <iostream>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#include "inputparser.h"

#include "mainwindow.h"

namespace
{
std::string CONFIG = "config.json";
}

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        rasp4home::InputParser inputParser(CONFIG);
        MainWindow w;
        w.resize(inputParser.get<int>("ScreenSize_x"), inputParser.get<int>("ScreenSize_y"));
        if(QGuiApplication::primaryScreen()->availableSize() != w.size()){
            w.show();
        }else{
            w.showFullScreen();
        }

        return a.exec();

    }  catch (std::exception &e) {
        std::cout << "[main]: " << e.what() << std::endl << "Aborting." << std::endl;
        return EINVAL;
    }
}
