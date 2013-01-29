#include "TKStateHere.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "WebcamHandler.h"
#include "TKStateAway.h"
#include "AbstractTimeHandler.h"

TKStateHere::TKStateHere()
{
    //ctor
}

TKStateHere::~TKStateHere()
{
    //dtor
}

void TKStateHere::updateStatus(TimeKeeper* parent)
{
    const bool isHere = parent->m_WebcamHandler->isHere();
    if (!isHere)
    {
        parent->m_AwayStamp = parent->m_TimeHandler->getTime();
        parent->m_CurrentState = TimeKeeper::AWAY;
    }
}

int TKStateHere::getTimerInterval(const TimeKeeper* parent) const
{
    const Config* config = parent->m_Config;
    const time_t now = parent->m_TimeHandler->getTime();
    int timerInterval = config->getCheckFreq();

    unsigned int hereInterval = now - parent->m_HereStamp;
    // work period ended
    if (hereInterval >= config->getWorkLength())
    {
        if (config->getCheckFreq() > config->getRemFreq())
        {
            timerInterval = config->getRemFreq();
        }
        else
        {
            timerInterval = config->getCheckFreq();
        }
    }
    // work period ending soon
    else if (hereInterval + config->getCheckFreq() > config->getWorkLength())
    {
        timerInterval = config->getWorkLength() - hereInterval;
    }

    return timerInterval;
}

bool TKStateHere::isLate(const TimeKeeper* parent) const
{
    return (parent->m_TimeHandler->getTime() - parent->m_HereStamp) >= parent->m_Config->getWorkLength();
}

int TKStateHere::getInterval(const TimeKeeper* parent) const
{
    return parent->m_TimeHandler->getTime() - parent->m_HereStamp;
}

int TKStateHere::getTimeLeft(const TimeKeeper* parent) const
{
    const Config* config = parent->m_Config;
    return parent->m_HereStamp + config->getWorkLength() - parent->m_TimeHandler->getTime();
}
