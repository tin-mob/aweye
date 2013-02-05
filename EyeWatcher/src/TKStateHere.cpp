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
    const bool isHere = parent->m_PresenceHandler->isHere();
    if (!isHere)
    {
        parent->setStatus(TimeKeeper::AWAY);
    }
}

void TKStateHere::updateTimeStamps(TimeKeeper* parent)
{
    parent->m_HereStamp = parent->m_TimeHandler->getTime();
}

int TKStateHere::getTimerInterval(const TimeKeeper* parent) const
{
    const ConfigData& config = parent->m_Config->getData();
    const time_t now = parent->m_TimeHandler->getTime();
    int timerInterval = config.checkFreq;

    unsigned int hereInterval = now - parent->m_HereStamp;
    // work period ended
    if (hereInterval >= config.workLength)
    {
        if (config.checkFreq > config.remFreq)
        {
            timerInterval = config.remFreq;
        }
        else
        {
            timerInterval = config.checkFreq;
        }
    }
    // work period ending soon
    else if (hereInterval + config.checkFreq > config.workLength)
    {
        timerInterval = config.workLength - hereInterval;
    }

    return timerInterval;
}

bool TKStateHere::isLate(const TimeKeeper* parent) const
{
    return (parent->m_TimeHandler->getTime() - parent->m_HereStamp) >= parent->m_Config->getData().workLength;
}

int TKStateHere::getInterval(const TimeKeeper* parent) const
{
    return parent->m_TimeHandler->getTime() - parent->m_HereStamp;
}

int TKStateHere::getTimeLeft(const TimeKeeper* parent) const
{
    const ConfigData& config = parent->m_Config->getData();
    return parent->m_HereStamp + config.workLength - parent->m_TimeHandler->getTime();
}
