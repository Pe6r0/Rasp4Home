#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <vector>
#include <QDateTime>

namespace rasp4home
{
namespace data
{
class WeatherData
{
public:
    enum PrecipitationType
    {
        Rain,
        Snow,
        Ice,
        Mixed,
        Null
    };

    struct CurrentWeatherData
    {
        QDateTime timestamp;
        std::string location;
        std::string summary;
        bool raining;
        bool daytime;
        float temperature;      //celsius
        float humidity;         //%
        float windDirection;    //degrees
        float windSpeed;        //km/h
        float windGustsSpeed;   //km/h
        int UVIndex;
        float visibility;       //km
        float cloudCover;       //%
        float precipitation;    //mm, past hour

        std::string toString();
    };

    struct WeatherForecast
    {
        QDateTime timestamp;
        QDateTime predictedTime;
        std::string location;
        std::string summary;
        bool raining;
        bool daytime;
        float temperature;              //celsius
        float precipitationProbability; //%

        std::string toString();
    };

    WeatherData(){};
    void setCurrentWeatherData(CurrentWeatherData data);
    void setWeatherForecast(std::vector<WeatherForecast> forecast);
    CurrentWeatherData getCurrentWeatherData();

private:
    CurrentWeatherData mCurrentWeatherData; //TODO add storage
    std::vector<WeatherForecast> mForecast;
};
}
}
#endif // WEATHERDATA_H
