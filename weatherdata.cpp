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
    std::cout << mCurrentWeatherData.toString() << std::endl;
    std::cout << std::endl;
}

void rasp4home::data::WeatherData::setWeatherForecast(std::vector<rasp4home::data::WeatherData::WeatherForecast> forecast)
{
    mForecast = forecast;
    std::cout << std::endl;
    std::cout << "New entry for forecast." << std::endl;
    for(auto& forecast: mForecast)
    {
        std::cout << forecast.toString() << std::endl;
    }
    std::cout << std::endl;
}

std::string rasp4home::data::WeatherData::CurrentWeatherData::toString()
{
    std::stringstream returned;
    returned << summary << std::endl;
    returned << timestamp.date().toString().toStdString() << std::endl;
    returned << "Location: " << location << std::endl;
    returned << "Is it raining: " << (raining ? "yes":"no") << std::endl;
    returned << "Precipitation for the last hour: " << precipitation << std::endl;
    returned << "Temperature: " << temperature << std::endl;
    returned << "Daytime: " << (daytime ? "yes":"no") << std::endl;
    returned << "UV Index: " << UVIndex << std::endl;
    returned << "Cloud Cover: " << cloudCover << std::endl;
    returned << "Humidity: " << humidity << std::endl;
    returned << "Visibility: " << visibility << std::endl;
    returned << "Wind Direction: " << windDirection << std::endl;
    returned << "Wind Gusts: " << windGustsSpeed << std::endl;
    returned << "Wind Speed: " << windSpeed << std::endl;
    return returned.str();
}

std::string rasp4home::data::WeatherData::WeatherForecast::toString()
{
    std::stringstream returned;
    returned << summary << std::endl;
    returned << timestamp.date().toString().toStdString() << std::endl;
    returned << "Predition Time: " << predictedTime.date().toString().toStdString() << std::endl;
    returned << "Will it be raining: " << (raining ? "yes":"no") << std::endl;
    returned << "Rain probability: " << precipitationProbability << std::endl;
    returned << "Temperature: " << temperature << std::endl;
    returned << "Will it be Daytime: " << (daytime ? "yes":"no") << std::endl;
    return returned.str();
}
