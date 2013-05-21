#include "TKStateHere.h"
#include "TimeKeeper.h"
#include "AbstractPresenceHandler.h"
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

/// @todo: manage false negatives...
void TKStateHere::updateStatus(TimeKeeper* parent)
{
    if (!parent->m_PresenceHandler->isHere())
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
    boost::posix_time::time_duration timerInterval = parent->m_CheckFreq;
    boost::posix_time::time_duration hereInterval =
        parent->m_TimeHandler->getTime() - parent->m_HereStamp;
    // work period ended
    if (hereInterval >= parent->m_WorkLength)
    {
        if (parent->m_CheckFreq > parent->m_RemFreq)
        {
            timerInterval = parent->m_RemFreq;
        }
        else
        {
            timerInterval = parent->m_CheckFreq;
        }
    }
    // work period ending soon
    else if (hereInterval + parent->m_CheckFreq > parent->m_WorkLength)
    {
        timerInterval = parent->m_WorkLength - hereInterval;
    }

    return timerInterval;
}

bool TKStateHere::isLate(const TimeKeeper* parent) const
{
    return (parent->m_TimeHandler->getTime() - parent->m_HereStamp) >= parent->m_WorkLength;
}

boost::posix_time::time_duration TKStateHere::getInterval(const TimeKeeper* parent) const
{
    return parent->m_TimeHandler->getTime() - parent->m_HereStamp;
}

boost::posix_time::time_duration TKStateHere::getTimeLeft(const TimeKeeper* parent) const
{
    return parent->m_HereStamp + parent->m_WorkLength - parent->m_TimeHandler->getTime();
}

boost::posix_time::time_duration TKStateHere::getWorkTimeLeft(const TimeKeeper* parent) const
{
    return this->getTimeLeft(parent);
}
