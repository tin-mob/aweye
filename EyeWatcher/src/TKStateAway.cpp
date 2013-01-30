#include "TKStateAway.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "WebcamHandler.h"
#include "TKStateHere.h"
#include "AbstractTimeHandler.h"

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
    const bool isHere = parent->m_WebcamHandler->isHere();
    std::string msg = "";

    if (isHere)
    {
        int timeLeft = this->getTimeLeft(parent);
        if (timeLeft > 0)
        {
            if (parent->m_NumTolerated < parent->m_Config->getPauseTol())
            {
                parent->m_NumTolerated++;
            }
            else
            {
                parent->m_AwayStamp = parent->m_LastAwayStamp;
                parent->m_CurrentState = TimeKeeper::HERE;
            }
        }
        else if (timeLeft <= 0)
        {
            parent->setStatus(TimeKeeper::HERE);
        }
    }
}

void TKStateAway::updateTimeStamps(TimeKeeper* parent)
{
    parent->m_NumTolerated = 0;
    parent->m_LastAwayStamp = parent->m_AwayStamp;
    parent->m_AwayStamp = parent->m_TimeHandler->getTime();
}

int TKStateAway::getTimerInterval(const TimeKeeper* parent) const
{
    const Config* config = parent->m_Config;
    const time_t now = parent->m_TimeHandler->getTime();
    int timerInterval = config->getCheckFreq();

    unsigned int pauseInterval = now - parent->m_AwayStamp;
    // work period ended
    if (pauseInterval >= config->getPauseLength())
    {
        timerInterval = config->getCheckFreq();
    }
    // pause period ending soon
    else if (pauseInterval + config->getCheckFreq() > config->getPauseLength())
    {
        timerInterval = config->getPauseLength() - pauseInterval;
    }

    return timerInterval;
}

bool TKStateAway::isLate(const TimeKeeper* parent) const
{
    return (parent->m_AwayStamp - parent->m_HereStamp) >= parent->m_Config->getWorkLength();
}

int TKStateAway::getInterval(const TimeKeeper* parent) const
{
    return parent->m_TimeHandler->getTime() - parent->m_AwayStamp;
}

int TKStateAway::getTimeLeft(const TimeKeeper* parent) const
{
    const Config* config = parent->m_Config;
    return parent->m_AwayStamp + config->getPauseLength() - parent->m_TimeHandler->getTime();
}
