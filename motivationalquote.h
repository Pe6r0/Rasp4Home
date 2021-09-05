#ifndef MOTIVATIONALQUOTE_H
#define MOTIVATIONALQUOTE_H
#include <string>

namespace rasp4home
{
namespace data
{
class MotivationalQuote
{
public:
    struct Quote{
        std::string quote;
        std::string author;
    };
    MotivationalQuote(){};
    void setQuote(Quote quote);
    Quote getQuote();

private:
    Quote mQuote;
};
}
}

#endif // MOTIVATIONALQUOTE_H
