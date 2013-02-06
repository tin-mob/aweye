#include "TKStateHere.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "WebcamHandler.h"
#include "TKStateAway.h"
#include "AbstractTimeHandler.h"
#include "boost/date_time/posix_time/posix_time.hpp"

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
        parent->setStatus(AbstractTimeKeeper::AWAY);
    }
}

void TKStateHere::updateTimeStamps(TimeKeeper* parent)
{
    parent->m_HereStamp = parent->m_TimeHandler->getTime();
}

boost::posix_time::time_duration TKStateHere::getTimerInterval(const TimeKeeper* parent) const
{
    const ConfigData& config = parent->m_Config->getData();
    const boost::posix_time::ptime now = parent->m_TimeHandler->getTime();
    boost::posix_time::time_duration timerInterval = config.checkFreq;

    boost::posix_time::time_duration hereInterval = now - parent->m_HereStamp;
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

boost::posix_time::time_duration TKStateHere::getInterval(const TimeKeeper* parent) const
{
    return parent->m_TimeHandler->getTime() - parent->m_HereStamp;
}

boost::posix_time::time_duration TKStateHere::getTimeLeft(const TimeKeeper* parent) const
{
    const ConfigData& config = parent->m_Config->getData();
    return parent->m_HereStamp + config.workLength - parent->m_TimeHandler->getTime();
}
