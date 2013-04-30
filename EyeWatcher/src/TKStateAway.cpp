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
            unsigned int num = parent->m_NumTolerated;
            unsigned int tol = parent->m_PauseTol;
            if (parent->m_NumTolerated < parent->m_PauseTol)
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
    const boost::posix_time::ptime now = parent->m_TimeHandler->getTime();
    boost::posix_time::time_duration timerInterval = parent->m_CheckFreq;

    boost::posix_time::time_duration pauseInterval = now - parent->m_AwayStamp;
    // work period ended
    if (pauseInterval >= parent->m_PauseLength)
    {
        timerInterval = parent->m_CheckFreq;
    }
    // pause period ending soon
    else if (pauseInterval + parent->m_CheckFreq > parent->m_PauseLength)
    {
        timerInterval = parent->m_PauseLength - pauseInterval;
    }

    return timerInterval;
}

bool TKStateAway::isLate(const TimeKeeper* parent) const
{
    return (parent->m_AwayStamp - parent->m_HereStamp) >= parent->m_WorkLength;
}

boost::posix_time::time_duration TKStateAway::getInterval(const TimeKeeper* parent) const
{
    return parent->m_TimeHandler->getTime() - parent->m_AwayStamp;
}

boost::posix_time::time_duration TKStateAway::getTimeLeft(const TimeKeeper* parent) const
{
    return parent->m_AwayStamp + parent->m_PauseLength - parent->m_TimeHandler->getTime();
}
