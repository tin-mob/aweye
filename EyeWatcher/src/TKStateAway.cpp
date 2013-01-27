#include "TKStateAway.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "WebcamHandler.h"
#include "TKStateHere.h"

TKStateAway* TKStateAway::m_Instance = NULL;

TKStateAway* TKStateAway::Instance()
{
    if (TKStateAway::m_Instance == NULL)
    {
        TKStateAway::m_Instance = new TKStateAway();
    }
    return TKStateAway::m_Instance;
}

TKStateAway::TKStateAway()
{
    //ctor
}

TKStateAway::~TKStateAway()
{
    //dtor
}

void TKStateAway::updateStatus(TimeKeeper* parent, int lastInterval)
{
    bool isHere = parent->m_WebcamHandler->isHere();
    std::string msg = "";

    if (parent->m_AwayStamp + lastInterval > parent->m_Config->getPauseLength())
    {
        if (!isHere)
        {
            msg = "You can come back..";
        }
        else
        {
            parent->m_HereStamp = time(NULL);
            //parent->m_CurrentState = parent->WatcherStateEnum.HERE;
        }
    }

    parent->m_Msg = msg;
}

int TKStateAway::getTimerInterval(TimeKeeper* parent)
{
    Config* config = parent->m_Config;
    time_t now = time(NULL);
    int timerInterval = config->getCheckFreq();

    // special case: pause period ending soon
    int pauseInterval = now - parent->m_AwayStamp;
    if (pauseInterval + config->getCheckFreq() > config->getPauseLength())
    {
        timerInterval = config->getPauseLength() - pauseInterval;
    }

    return timerInterval;
}

int TKStateAway::getInterval(TimeKeeper* parent)
{
    return time(NULL) - parent->m_AwayStamp;
}

int TKStateAway::getTimeLeft(TimeKeeper* parent)
{
    Config* config = parent->m_Config;
    return parent->m_AwayStamp + config->getPauseLength() - time(NULL);
}

std::string TKStateAway::getName()
{
    return "Away";
}
