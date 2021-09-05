#ifndef WEATHERDATA_H
#define WEATHERDATA_H
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
        int precipitation;      //mm, past hour
    };

    WeatherData();
    void setCurrentWeatherData(CurrentWeatherData data);
    CurrentWeatherData getCurrentWeatherData();
    std::string toString();

private:
    CurrentWeatherData mCurrentWeatherData; //TODO add storage
};
}
}
#endif // WEATHERDATA_H
