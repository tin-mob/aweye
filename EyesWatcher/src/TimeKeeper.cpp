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
///@todo: manage pc hibernate, stamps, les complicated...

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
                   unsigned int workTol):
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
    m_CheckFreq(checkFreq), m_PauseTol(pauseTol), m_WorkTol(workTol)
{
    assert(timeHandler);
    assert(presenceHandler);
    try
    {
        this->m_States[AbstractTimeKeeper::OFF] = new TKStateOff();
        this->m_States[AbstractTimeKeeper::AWAY] = new TKStateAway();
        this->m_States[AbstractTimeKeeper::HERE] = new TKStateHere();
    }
    catch (...)
    {
       this->deleteStates();
       throw; //rethrow. no memory leak
    }
    this->m_CurrentState = TimeKeeper::OFF;
}

TimeKeeper::~TimeKeeper()
{
    this->deleteStates();
}

void TimeKeeper::deleteStates()
{
    for (std::map<Status,TKState*>::iterator it = this->m_States.begin() ; it != this->m_States.end(); ++it)
        delete it->second;
}

void TimeKeeper::start()
{
    this->m_StartTimeUpdate = this->m_TimeHandler->getTime();
    this->m_LastUpdate = this->m_TimeHandler->getTime();
    if (this->m_CurrentState == TimeKeeper::OFF)
    {
        this->setStatus(AbstractTimeKeeper::HERE);
    }
}

void TimeKeeper::stop()
{
    if (this->m_CurrentState != TimeKeeper::OFF)
    {
        this->setStatus(AbstractTimeKeeper::OFF);
    }
}

void TimeKeeper::notifyHibernated(boost::posix_time::time_duration length)
{
    ///@todo
}

void TimeKeeper::updateStatus()
{
    this->m_StartTimeUpdate = this->m_TimeHandler->getTime();
    TKState* state = this->m_States.find(this->m_CurrentState)->second;
    state->updateStatus(this);

    state = this->m_States.find(this->m_CurrentState)->second;
    state->addDuration(this);
    this->m_LastUpdate = this->m_TimeHandler->getTime();

    if (this->m_AwayDur >= this->m_PauseLength)
    {
        this->m_HereDur = boost::posix_time::seconds(0);
    }
}

boost::posix_time::time_duration TimeKeeper::getTimerInterval() const
{
    const TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->getTimerInterval(this);
}

bool TimeKeeper::isLate() const
{
    const TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->isLate(this);
}

TimeKeeper::Status TimeKeeper::getStatus() const
{
    return this->m_CurrentState;
}

boost::posix_time::time_duration TimeKeeper::getInterval() const
{
    const TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->getInterval(this);
}

boost::posix_time::time_duration TimeKeeper::getTimeLeft() const
{
    const TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->getTimeLeft(this);
}

boost::posix_time::ptime TimeKeeper::getHereStamp() const
{
    return this->m_HereStamp;
}

boost::posix_time::ptime TimeKeeper::getAwayStamp() const
{
    return this->m_AwayStamp;
}

boost::posix_time::time_duration TimeKeeper::getWorkTimeLeft() const
{
    const TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->getWorkTimeLeft(this);
}

void TimeKeeper::setStatus(Status status, bool cancelled)
{
    this->m_CurrentState = status;

    TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->initState(this, cancelled);
}

void TimeKeeper::setWorkLength(boost::posix_time::time_duration workLength)
{
    this->m_WorkLength = workLength;
}

void TimeKeeper::setPauseLength(boost::posix_time::time_duration pauseLength)
{
    this->m_PauseLength = pauseLength;
}

void TimeKeeper::setRemFreq(boost::posix_time::time_duration remFreq)
{
    this->m_RemFreq = remFreq;
}

void TimeKeeper::setCheckFreq(boost::posix_time::time_duration checkFreq)
{
    this->m_CheckFreq = checkFreq;
}

void TimeKeeper::setPauseTol(unsigned int pauseTol)
{
    this->m_PauseTol = pauseTol;
}

void TimeKeeper::setWorkTol(unsigned int workTol)
{
    this->m_WorkTol = workTol;
}

