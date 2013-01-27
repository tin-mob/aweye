#include "TKStateHere.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "WebcamHandler.h"
#include "TKStateAway.h"

TKStateHere* TKStateHere::m_Instance = NULL;

TKStateHere* TKStateHere::Instance()
{
    if (TKStateHere::m_Instance == NULL)
    {
        TKStateHere::m_Instance = new TKStateHere();
    }
    return TKStateHere::m_Instance;
}

TKStateHere::TKStateHere()
{
    //ctor
}

TKStateHere::~TKStateHere()
{
    //dtor
}

void TKStateHere::updateStatus(TimeKeeper* parent, int lastInterval)
{
    Config* config = parent->m_Config;
    bool isHere = parent->m_WebcamHandler->isHere();
    std::string msg = "";

    if (isHere)
    {
        if (parent->m_HereStamp + lastInterval > config->getWorkLength())
        {
             msg = "Time for a pause";
        }
    }
    else
    {
        parent->m_AwayStamp = time(NULL);
        //parent->m_CurrentState = AwayWatcherState::Instance();
    }

    parent->m_Msg = msg;
}

int TKStateHere::getTimerInterval(TimeKeeper* parent)
{
    Config* config = parent->m_Config;
    time_t now = time(NULL);
    int timerInterval = config->getCheckFreq();

    // special case: work period ending soon
    int hereInterval = now - parent->m_HereStamp;
    if (hereInterval + config->getCheckFreq() > config->getWorkLength())
    {
        timerInterval = config->getWorkLength() - hereInterval;
    }

    return timerInterval;
}

int TKStateHere::getInterval(TimeKeeper* parent)
{
    return time(NULL) - parent->m_HereStamp;
}

int TKStateHere::getTimeLeft(TimeKeeper* parent)
{
    Config* config = parent->m_Config;
    return parent->m_HereStamp + config->getWorkLength() - time(NULL);
}

std::string TKStateHere::getName()
{
    return "Here";
}
