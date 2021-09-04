#include <iostream>
#include <QApplication>

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
        rasp4Home::InputParser inputParser(CONFIG);
    }  catch (std::exception &e) {
        std::cout << "[main]: " << e.what() << std::endl << "Aborting." << std::endl;
        return EINVAL;
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
