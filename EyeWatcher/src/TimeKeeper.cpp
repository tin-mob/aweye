#include "TimeKeeper.h"
#include "TKStateAway.h"
#include "TKStateHere.h"
#include "TKStateOff.h"
#include "AbstractConfig.h"
#include "AbstractTimeHandler.h"
#include "AbstractPresenceHandler.h"

#include "boost/date_time/posix_time/posix_time.hpp"

TimeKeeper::TimeKeeper(AbstractConfig* config, AbstractTimeHandler* timeHandler, AbstractPresenceHandler* presenceHandler) :
    m_Config(config), m_TimeHandler(timeHandler), m_PresenceHandler(presenceHandler),
    m_HereStamp(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_AwayStamp(boost::posix_time::ptime(boost::posix_time::not_a_date_time)),
    m_LastAwayStamp(boost::posix_time::ptime(boost::posix_time::not_a_date_time)), m_NumTolerated(0)
{
    //ctor
    this->initStates();
}

TimeKeeper::~TimeKeeper()
{
    //dtor
    delete this->m_States[AbstractTimeKeeper::OFF];
    delete this->m_States[AbstractTimeKeeper::AWAY];
    delete this->m_States[AbstractTimeKeeper::HERE];
}

void TimeKeeper::initStates()
{
    this->m_States[AbstractTimeKeeper::OFF] = new TKStateOff();
    this->m_States[AbstractTimeKeeper::AWAY] = new TKStateAway();
    this->m_States[AbstractTimeKeeper::HERE] = new TKStateHere();

    this->m_CurrentState = TimeKeeper::OFF;
}

void TimeKeeper::start()
{
    if (this->m_CurrentState == TimeKeeper::OFF)
    {
        this->m_PresenceHandler->open();
        this->setStatus(AbstractTimeKeeper::HERE);
    }
}

void TimeKeeper::stop()
{
    if (this->m_CurrentState != TimeKeeper::OFF)
    {
        this->m_PresenceHandler->release();
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

void TimeKeeper::setStatus(Status status)
{
    this->m_CurrentState = status;

    TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->updateTimeStamps(this);
}
