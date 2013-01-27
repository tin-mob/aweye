#include "TKStateOff.h"
#include "Config.h"
#include "TimeKeeper.h"

TKStateOff* TKStateOff::m_Instance = NULL;

TKStateOff* TKStateOff::Instance()
{
    if (TKStateOff::m_Instance == NULL)
    {
        TKStateOff::m_Instance = new TKStateOff();
    }
    return TKStateOff::m_Instance;
}

TKStateOff::TKStateOff()
{
    //ctor
}

TKStateOff::~TKStateOff()
{
    //dtor
}


void TKStateOff::updateStatus(TimeKeeper* parent, int lastInterval)
{
    parent->m_HereStamp = 0;
    parent->m_AwayStamp = 0;
}

int TKStateOff::getTimerInterval(TimeKeeper* parent)
{
    Config* config = parent->m_Config;
    return config->getCheckFreq();
}

int TKStateOff::getInterval(TimeKeeper* parent)
{
    return 0;
}

int TKStateOff::getTimeLeft(TimeKeeper* parent)
{
    return 0;
}

std::string TKStateOff::getName()
{
    return "Off";
}
