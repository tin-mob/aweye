#include "TKStateOff.h"
#include "Config.h"
#include "TimeKeeper.h"

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
    parent->m_HereStamp = 0;
    parent->m_AwayStamp = 0;
}

int TKStateOff::getTimerInterval(const TimeKeeper*) const
{
    return 0;
}

bool TKStateOff::isLate(const TimeKeeper*) const
{
    return false;
}

int TKStateOff::getInterval(const TimeKeeper*) const
{
    return 0;
}

int TKStateOff::getTimeLeft(const TimeKeeper* parent) const
{
    const Config* config = parent->m_Config;
    return config->getWorkLength();
}
