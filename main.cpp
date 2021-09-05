#include <iostream>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#include "inputparser.h"
#include "datamanager.h"
#include "mainwindow.h"


#include "weatherdatamanager.h"

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

        rasp4home::data::DataManager mainDataManager;



        ////tmp
        /// add the args in a struct maybe?
        rasp4home::data::WeatherDataManager weatherDataManager(inputParser.get<std::string>("Accu_API"), inputParser.get<std::string>("Accu_Location"));

        weatherDataManager.refreshAllData();
        ///



        rasp4home::ui::MainWindow mainUI;
        mainUI.resize(inputParser.get<int>("ScreenSize_x"), inputParser.get<int>("ScreenSize_y"));
        if(QGuiApplication::primaryScreen()->availableSize() != mainUI.size()){
            mainUI.show();
        }else{
            mainUI.showFullScreen();
        }

        return a.exec();

    }  catch (std::exception &e) {
        std::cout << "[main]: " << e.what() << std::endl << "Aborting." << std::endl;
        return EINVAL;
    }
}
