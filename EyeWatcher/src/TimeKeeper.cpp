#include "TimeKeeper.h"
#include "WebcamHandler.h"
#include "TKStateAway.h"
#include "TKStateHere.h"
#include "TKStateOff.h"
#include "TimeHandler.h"
#include "Config.h"

TimeKeeper::TimeKeeper(Config* config) : m_HereStamp(0), m_AwayStamp(0), m_Config(config)
{
    //ctor
    this->m_TimeHandler = new TimeHandler();
    this->m_WebcamHandler = new WebcamHandler();
    this->initStates();
}

TimeKeeper::TimeKeeper(Config* config, AbstractTimeHandler* timeHandler, AbstractWebcamHandler* handler) : m_TimeHandler(timeHandler), m_WebcamHandler(handler), m_HereStamp(0), m_AwayStamp(0), m_Config(config)
{
    this->initStates();
}

TimeKeeper::~TimeKeeper()
{
    //dtor
    delete this->m_TimeHandler;
    this->m_TimeHandler = NULL;
    delete this->m_WebcamHandler;
    this->m_WebcamHandler = NULL;

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
        this->m_CurrentState = TimeKeeper::HERE;
        this->m_HereStamp = this->m_TimeHandler->getTime();
    }
}

void TimeKeeper::stop()
{
    if (this->m_CurrentState != TimeKeeper::OFF)
    {
        this->m_CurrentState = TimeKeeper::OFF;
        this->m_HereStamp = 0;
        this->m_AwayStamp = 0;
    }
}

/// @todo:coming back to check restarts the pause - determine how to be permissive (config???)
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
