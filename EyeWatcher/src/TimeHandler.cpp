#include "TimeHandler.h"
#include "boost/date_time/posix_time/posix_time.hpp"

TimeHandler::TimeHandler()
{
    //ctor
}

TimeHandler::~TimeHandler()
{
    //dtor
}

boost::posix_time::ptime TimeHandler::getTime() const
{
    return boost::posix_time::second_clock::local_time();
}
