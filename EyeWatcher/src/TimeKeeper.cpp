#include "TimeKeeper.h"
#include "WebcamHandler.h"

TimeKeeper::TimeKeeper(Config* config) : m_HereStamp(0), m_AwayStamp(0), m_Msg(""), m_Config(config)
{
    //ctor
    this->m_WebcamHandler = new WebcamHandler();
   // this->m_CurrentState = ;
}

TimeKeeper::~TimeKeeper()
{
    //dtor
    delete this->m_WebcamHandler;
    this->m_WebcamHandler = NULL;
}

void TimeKeeper::start()
{

}

void TimeKeeper::stop()
{

}

/// @todo:coming back to check restarts the pause - determine how to be permissive (config???)
void TimeKeeper::updateStatus(int lastInterval)
{

}

int TimeKeeper::getTimerInterval()
{
    return 0;
}

std::string TimeKeeper::getAlarmMsg()
{
    return this->m_Msg;
}

std::string TimeKeeper::getStatus()
{
    return "";
}

int TimeKeeper::getInterval()
{
    return 0;
}

int TimeKeeper::getTimeLeft()
{
    return 0;
}

int TimeKeeper::getHereStamp()
{
    return 0;
}

int TimeKeeper::getAwayStamp()
{
    return 0;
}
