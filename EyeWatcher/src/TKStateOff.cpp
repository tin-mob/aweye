#include "TKStateOff.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "boost/date_time/posix_time/posix_time.hpp"

TKStateOff::TKStateOff()
{
    //ctor
}

TKStateOff::~TKStateOff()
{
    //dtor
}


void TKStateOff::updateStatus(TimeKeeper* parent)
{
}

void TKStateOff::updateTimeStamps(TimeKeeper* parent)
{
    parent->m_HereStamp = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
    parent->m_AwayStamp = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
}

boost::posix_time::time_duration TKStateOff::getTimerInterval(const TimeKeeper*) const
{
    return boost::posix_time::time_duration(0,0,0,0);
}

bool TKStateOff::isLate(const TimeKeeper*) const
{
    return false;
}

boost::posix_time::time_duration TKStateOff::getInterval(const TimeKeeper*) const
{
    return boost::posix_time::time_duration(0,0,0,0);
}

boost::posix_time::time_duration TKStateOff::getTimeLeft(const TimeKeeper* parent) const
{
    const ConfigData& config = parent->m_Config->getData();
    return config.workLength;
}
