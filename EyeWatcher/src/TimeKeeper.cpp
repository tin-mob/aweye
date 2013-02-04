#include "TimeKeeper.h"
#include "TKStateAway.h"
#include "TKStateHere.h"
#include "TKStateOff.h"
#include "AbstractConfig.h"
#include "AbstractTimeHandler.h"
#include "AbstractWebcamHandler.h"

TimeKeeper::TimeKeeper(AbstractConfig* config, AbstractTimeHandler* timeHandler, AbstractWebcamHandler* webcamHandler) :
    m_Config(config), m_TimeHandler(timeHandler), m_WebcamHandler(webcamHandler),
    m_HereStamp(0), m_AwayStamp(0), m_LastAwayStamp(0), m_NumTolerated(0)
{
    //ctor
    this->initStates();
}

TimeKeeper::~TimeKeeper()
{
    //dtor
    delete this->m_States[TimeKeeper::OFF];
    this->m_States.erase (TimeKeeper::OFF);
    delete this->m_States[TimeKeeper::AWAY];
    this->m_States.erase (TimeKeeper::AWAY);
    delete this->m_States[TimeKeeper::HERE];
    this->m_States.erase (TimeKeeper::HERE);
}

void TimeKeeper::initStates()
{
    this->m_States[TimeKeeper::OFF] = new TKStateOff();
    this->m_States[TimeKeeper::AWAY] = new TKStateAway();
    this->m_States[TimeKeeper::HERE] = new TKStateHere();

    this->m_CurrentState = TimeKeeper::OFF;
}

void TimeKeeper::start()
{
    if (this->m_CurrentState == TimeKeeper::OFF)
    {
        this->m_WebcamHandler->open();
        this->setStatus(TimeKeeper::HERE);
    }
}

void TimeKeeper::stop()
{
    if (this->m_CurrentState != TimeKeeper::OFF)
    {
        this->m_WebcamHandler->release();
        this->setStatus(TimeKeeper::OFF);
    }
}

void TimeKeeper::updateStatus()
{
    TKState* state = this->m_States.find(this->m_CurrentState)->second;
    state->updateStatus(this);
}

int TimeKeeper::getTimerInterval() const
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

int TimeKeeper::getInterval() const
{
    const TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->getInterval(this);
}

int TimeKeeper::getTimeLeft() const
{
    const TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->getTimeLeft(this);
}

int TimeKeeper::getHereStamp() const
{
    return this->m_HereStamp;
}

int TimeKeeper::getAwayStamp() const
{
    return this->m_AwayStamp;
}

void TimeKeeper::setStatus(Status status)
{
    this->m_CurrentState = status;

    TKState* state = this->m_States.find(this->m_CurrentState)->second;
    return state->updateTimeStamps(this);
}
