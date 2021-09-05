#include "motivationalquote.h"

void rasp4home::data::MotivationalQuote::setQuote(Quote quote)
{
    mQuote = quote;
}

rasp4home::data::MotivationalQuote::Quote rasp4home::data::MotivationalQuote::getQuote()
{
    return mQuote;
}
