#ifndef INPUTPARSER_H
#define INPUTPARSER_H
#include <string>

#include <nlohmann/json.hpp>

namespace rasp4Home
{
//class parses expected input and makes information in it available
class InputParser
{
public:
    InputParser(std::string path);
    template<class T>
    T get(std::string request);
private:
    nlohmann::json database;
};
}
#endif // INPUTPARSER_H
