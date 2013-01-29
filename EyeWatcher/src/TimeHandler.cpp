#include "TimeHandler.h"

TimeHandler::TimeHandler()
{
    //ctor
}

TimeHandler::~TimeHandler()
{
    //dtor
}

time_t TimeHandler::getTime() const
{
    return time(NULL);
}
