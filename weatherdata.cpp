#include <iostream>
#include <sstream>

#include "weatherdata.h"

rasp4home::data::WeatherData::WeatherData()
{

}

void rasp4home::data::WeatherData::setCurrentWeatherData(rasp4home::data::WeatherData::CurrentWeatherData data)
{
    mCurrentWeatherData = data;
    std::cout << std::endl;
    std::cout << "New entry for weather data: " << std::endl;
    std::cout << toString() << std::endl;
    std::cout << std::endl;
}


std::string rasp4home::data::WeatherData::toString()
{
    std::stringstream returned;
    returned << mCurrentWeatherData.summary << std::endl;
    returned << mCurrentWeatherData.timestamp.date().toString().toStdString() << std::endl;
    returned << "Location: " << mCurrentWeatherData.location << std::endl;
    returned << "Is it raining: " << (mCurrentWeatherData.raining ? "yes":"no") << std::endl;
    returned << "Precipitation for the last hour: " << mCurrentWeatherData.precipitation << std::endl;
    returned << "Temperature: " << mCurrentWeatherData.temperature << std::endl;
    returned << "Daytime: " << (mCurrentWeatherData.daytime ? "yes":"no") << std::endl;
    returned << "UV Index: " << mCurrentWeatherData.UVIndex << std::endl;
    returned << "Cloud Cover: " << mCurrentWeatherData.cloudCover << std::endl;
    returned << "Humidity: " << mCurrentWeatherData.humidity << std::endl;
    returned << "Visibility: " << mCurrentWeatherData.visibility << std::endl;
    returned << "Wind Direction: " << mCurrentWeatherData.windDirection << std::endl;
    returned << "Wind Gusts: " << mCurrentWeatherData.windGustsSpeed << std::endl;
    returned << "Wind Speed: " << mCurrentWeatherData.windSpeed << std::endl;
    return returned.str();
}
