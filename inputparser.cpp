#include <exception>
#include <fstream>
#include <iostream>

#include "inputparser.h"

rasp4Home::InputParser::InputParser(std::string input)
{
    std::ifstream file(input);
    if(!file.is_open()){
        std::cout << "[InputParser] : File not found" << std::endl;
        throw std::invalid_argument("File not found");
    }

     database = nlohmann::json::parse(file);
}

template<typename T>
T rasp4Home::InputParser::get(std::string request)
{
    try
    {
        return database.at(request);
    }
    catch (std::exception &e) {
        std::cout << "[InputParser] Failure to get value for key: [" << request << "]" << "(" << e.what() << ")" << std::endl;
        throw std::invalid_argument(std::string{"Failure to get value for "} + request);
    }
}


template int rasp4Home::InputParser::get<int>(std::string request);
template std::string rasp4Home::InputParser::get<std::string>(std::string request);
template bool rasp4Home::InputParser::get<bool>(std::string request);
/*
template<typename T>
T rasp4Home::InputParser::get()
{
    //try
    {
        T t = 0;
        return t + 1;
    }
    //catch (std::exception &e) {
    //    std::cout << "[InputParser] Failure to get value for key: [" << request << "]" << "(" << e.what() << ")" << std::endl;
    //    throw std::invalid_argument(std::string{"Failure to get value for "} + request);
    //}
}*/
