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
                   unsigned int pauseTol):
    m_TimeHandler(timeHandler), m_PresenceHandler(presenceHandler),
    m_HereStamp(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_AwayStamp(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_LastAwayStamp(boost::posix_time::ptime(boost::posix_time::not_a_date_time)), m_NumTolerated(0),
    m_WorkLength(workLength), m_PauseLength(pauseLength), m_RemFreq(remFreq), m_CheckFreq(checkFreq),
    m_PauseTol(pauseTol)
{
    //ctor
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
    //dtor
    this->deleteStates();
}

void TimeKeeper::deleteStates()
{
    for (std::map<Status,TKState*>::iterator it = this->m_States.begin() ; it != this->m_States.end(); ++it)
        delete it->second;
}

void TimeKeeper::start()
{
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

void TimeKeeper::updateStatus()
{
    TKState* state = this->m_States.find(this->m_CurrentState)->second;
    state->updateStatus(this);
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
    return this->m_States.find(AbstractTimeKeeper::HERE)->second->getTimeLeft(this);
}

void TimeKeeper::setStatus(Status status)
{
    this->m_CurrentState = status;

    TKState* state = this->m_States.find(this->m_CurrentState)->second;

    // Note: the timestamp is the first recorded time when the status is changed,
    // not the time of the last occurance of the last state.
    return state->updateTimeStamps(this);
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
