/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/

#include "TimeKeeper.h"
#include "TKStateAway.h"
#include "TKStateHere.h"
#include "TKStateOff.h"
#include "AbstractTimeHandler.h"
#include "AbstractPresenceHandler.h"

#include "boost/date_time/posix_time/posix_time.hpp"

TimeKeeper::TimeKeeper(AbstractTimeHandler* timeHandler,
                   AbstractPresenceHandler* presenceHandler,
                   boost::posix_time::time_duration workLength,
                   boost::posix_time::time_duration pauseLength,
                   boost::posix_time::time_duration remFreq,
                   boost::posix_time::time_duration checkFreq,
                   unsigned int pauseTol,
                   unsigned int workTol,
                   bool cummulPause):
    m_TimeHandler(timeHandler), m_PresenceHandler(presenceHandler),
    m_HereDur(boost::posix_time::seconds(0)),
    m_AwayDur(boost::posix_time::seconds(0)),
    m_LastUpdate(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_StartTimeUpdate(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_TolerationTime(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_NumTolerated(0),
    m_HereStamp(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_AwayStamp(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_LastAwayStamp(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_WorkLength(workLength), m_PauseLength(pauseLength), m_RemFreq(remFreq),
    m_CheckFreq(checkFreq), m_PauseTol(pauseTol), m_WorkTol(workTol),
    m_CummulPause(cummulPause)
{
    assert(timeHandler);
    assert(presenceHandler);
    try
    {
        m_States[AbstractTimeKeeper::OFF] = new TKStateOff();
        m_States[AbstractTimeKeeper::AWAY] = new TKStateAway();
        m_States[AbstractTimeKeeper::HERE] = new TKStateHere();
    }
    catch (...)
    {
       deleteStates();
       throw; //rethrow. no memory leak
    }
    m_CurrentState = TimeKeeper::OFF;
}

TimeKeeper::~TimeKeeper()
{
    deleteStates();
}

void TimeKeeper::deleteStates()
{
    for (std::map<Status,TKState*>::iterator it = m_States.begin() ; it != m_States.end(); ++it)
        delete it->second;
}

void TimeKeeper::start()
{
    if (m_CurrentState == TimeKeeper::OFF)
    {
        m_StartTimeUpdate = m_TimeHandler->getTime();
        m_LastUpdate = m_TimeHandler->getTime();

        if (m_PresenceHandler->isHere())
        {
            setStatus(AbstractTimeKeeper::HERE);
        }
        else
        {
            setStatus(AbstractTimeKeeper::AWAY);
        }
    }
}

void TimeKeeper::stop()
{
    if (m_CurrentState != TimeKeeper::OFF)
    {
        setStatus(AbstractTimeKeeper::OFF);
    }
}

void TimeKeeper::notifyHibernated()
{
    m_StartTimeUpdate = m_TimeHandler->getTime();
    m_NumTolerated = 0;
    m_LastAwayStamp = m_AwayStamp;

    if (!m_TolerationTime.is_special())
    {
        const boost::posix_time::time_duration interval =
            m_LastUpdate - m_TolerationTime;
        m_AwayDur += interval;
        m_HereDur -= interval;
        m_AwayStamp = m_TolerationTime;
    }
    else
    {
        m_AwayStamp = m_LastUpdate;
    }


    m_AwayDur += m_StartTimeUpdate - m_LastUpdate;
    m_CurrentState = AbstractTimeKeeper::AWAY;
    m_LastUpdate = m_StartTimeUpdate;
}

void TimeKeeper::updateStatus()
{
    m_StartTimeUpdate = m_TimeHandler->getTime();
    TKState* state = m_States.find(m_CurrentState)->second;
    state->updateStatus(this);

    state = m_States.find(m_CurrentState)->second;
    state->addDuration(this);
    m_LastUpdate = m_StartTimeUpdate;
}

boost::posix_time::time_duration TimeKeeper::getTimerInterval() const
{
    const TKState* state = m_States.find(m_CurrentState)->second;
    return state->getTimerInterval(this);
}

bool TimeKeeper::isLate() const
{
    const TKState* state = m_States.find(m_CurrentState)->second;
    return state->isLate(this);
}

TimeKeeper::Status TimeKeeper::getStatus() const
{
    return m_CurrentState;
}

boost::posix_time::time_duration TimeKeeper::getInterval() const
{
    const TKState* state = m_States.find(m_CurrentState)->second;
    return state->getInterval(this);
}

boost::posix_time::time_duration TimeKeeper::getTimeLeft() const
{
    const TKState* state = m_States.find(m_CurrentState)->second;
    return state->getTimeLeft(this);
}

boost::posix_time::ptime TimeKeeper::getHereStamp() const
{
    return m_HereStamp;
}

boost::posix_time::ptime TimeKeeper::getAwayStamp() const
{
    return m_AwayStamp;
}

boost::posix_time::time_duration TimeKeeper::getWorkTimeLeft() const
{
    const TKState* state = m_States.find(m_CurrentState)->second;
    return state->getWorkTimeLeft(this);
}

void TimeKeeper::setStatus(Status status, bool cancelled)
{
    m_CurrentState = status;

    TKState* state = m_States.find(m_CurrentState)->second;
    return state->initState(this, cancelled);

    m_TolerationTime = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
}

boost::posix_time::time_duration TimeKeeper::getUpdateOffset() const
{
    return m_TimeHandler->getTime() -
        (m_HereStamp + m_HereDur + m_AwayDur);
}

void TimeKeeper::setWorkLength(boost::posix_time::time_duration workLength)
{
    m_WorkLength = workLength;
}

void TimeKeeper::setPauseLength(boost::posix_time::time_duration pauseLength)
{
    m_PauseLength = pauseLength;
}

void TimeKeeper::setRemFreq(boost::posix_time::time_duration remFreq)
{
    m_RemFreq = remFreq;
}

void TimeKeeper::setCheckFreq(boost::posix_time::time_duration checkFreq)
{
    m_CheckFreq = checkFreq;
}

void TimeKeeper::setPauseTol(unsigned int pauseTol)
{
    m_PauseTol = pauseTol;
}

void TimeKeeper::setWorkTol(unsigned int workTol)
{
    m_WorkTol = workTol;
}

void TimeKeeper::setCummulPause(bool cummulPause)
{
    m_CummulPause = cummulPause;
}

