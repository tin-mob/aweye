#include "TKStateAway.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "WebcamHandler.h"
#include "TKStateHere.h"
#include "AbstractTimeHandler.h"
#include "boost/date_time/posix_time/posix_time.hpp"

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
    const bool isHere = parent->m_PresenceHandler->isHere();
    std::string msg = "";

    if (isHere)
    {
        boost::posix_time::time_duration timeLeft = this->getTimeLeft(parent);
        if (timeLeft > boost::posix_time::time_duration(0,0,0,0))
        {
            if (parent->m_NumTolerated < parent->m_Config->getData().pauseTol)
            {
                parent->m_NumTolerated++;
            }
            else
            {
                parent->m_AwayStamp = parent->m_LastAwayStamp;
                parent->m_CurrentState = AbstractTimeKeeper::HERE;
            }
        }
        else if (timeLeft <= boost::posix_time::time_duration(0,0,0,0))
        {
            parent->setStatus(AbstractTimeKeeper::HERE);
        }
    }
}

void TKStateAway::updateTimeStamps(TimeKeeper* parent)
{
    parent->m_NumTolerated = 0;
    parent->m_LastAwayStamp = parent->m_AwayStamp;
    parent->m_AwayStamp = parent->m_TimeHandler->getTime();
}

boost::posix_time::time_duration TKStateAway::getTimerInterval(const TimeKeeper* parent) const
{
    const ConfigData& config = parent->m_Config->getData();
    const boost::posix_time::ptime now = parent->m_TimeHandler->getTime();
    boost::posix_time::time_duration timerInterval = config.checkFreq;

    boost::posix_time::time_duration pauseInterval = now - parent->m_AwayStamp;
    // work period ended
    if (pauseInterval >= config.pauseLength)
    {
        timerInterval = config.checkFreq;
    }
    // pause period ending soon
    else if (pauseInterval + config.checkFreq > config.pauseLength)
    {
        timerInterval = config.pauseLength - pauseInterval;
    }

    return timerInterval;
}

bool TKStateAway::isLate(const TimeKeeper* parent) const
{
    const ConfigData& config = parent->m_Config->getData();
    return (parent->m_AwayStamp - parent->m_HereStamp) >= config.workLength;
}

boost::posix_time::time_duration TKStateAway::getInterval(const TimeKeeper* parent) const
{
    return parent->m_TimeHandler->getTime() - parent->m_AwayStamp;
}

boost::posix_time::time_duration TKStateAway::getTimeLeft(const TimeKeeper* parent) const
{
    const ConfigData& config = parent->m_Config->getData();
    return parent->m_AwayStamp + config.pauseLength - parent->m_TimeHandler->getTime();
}
