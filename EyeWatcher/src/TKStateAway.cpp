#include "TKStateAway.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "WebcamHandler.h"
#include "TKStateHere.h"
#include "AbstractTimeHandler.h"

TKStateAway::TKStateAway()
{
    //ctor
}

TKStateAway::~TKStateAway()
{
    //dtor
}

void TKStateAway::updateStatus(TimeKeeper* parent)
{
    const bool isHere = parent->m_WebcamHandler->isHere();
    std::string msg = "";

    if (parent->m_TimeHandler->getTime() - parent->m_AwayStamp > parent->m_Config->getPauseLength())
    {
        if (isHere)
        {
            parent->m_HereStamp = parent->m_TimeHandler->getTime();
            parent->m_CurrentState = TimeKeeper::HERE;
        }
    }
}

int TKStateAway::getTimerInterval(const TimeKeeper* parent) const
{
    const Config* config = parent->m_Config;
    const time_t now = parent->m_TimeHandler->getTime();
    int timerInterval = config->getCheckFreq();

    unsigned int pauseInterval = now - parent->m_AwayStamp;
    // work period ended
    if (pauseInterval >= config->getPauseLength())
    {
        timerInterval = config->getCheckFreq();
    }
    // pause period ending soon
    else if (pauseInterval + config->getCheckFreq() > config->getPauseLength())
    {
        timerInterval = config->getPauseLength() - pauseInterval;
    }

    return timerInterval;
}

bool TKStateAway::isLate(const TimeKeeper* parent) const
{
    return (parent->m_AwayStamp - parent->m_HereStamp) >= parent->m_Config->getWorkLength();
}

int TKStateAway::getInterval(const TimeKeeper* parent) const
{
    return parent->m_TimeHandler->getTime() - parent->m_AwayStamp;
}

int TKStateAway::getTimeLeft(const TimeKeeper* parent) const
{
    const Config* config = parent->m_Config;
    return parent->m_AwayStamp + config->getPauseLength() - parent->m_TimeHandler->getTime();
}
