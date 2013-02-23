#include "EWLogic.h"
#include "AbstractConfig.h"
#include "HandlerFactory.h"
#include "AbstractMsgHandler.h"
#include "AbstractTimeKeeper.h"
#include "BaseException.h"

#include <sstream>
#include <iomanip>

EWLogic::EWLogic(AbstractMsgHandler* msgHandler, AbstractConfig* config, AbstractTimeKeeper* keeper)
    : m_Warn(true), m_Config(config), m_TimeKeeper(keeper), m_MsgHandler(msgHandler)
{
}

EWLogic::~EWLogic()
{
}

const ConfigData& EWLogic::getConfigData() const
{
    return this->m_Config->getData();
}

void EWLogic::saveConfig(const ConfigData& data)
{
    this->m_Config->save(data);
}

void EWLogic::start()
{
    try
    {
        this->m_TimeKeeper->start();
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
    }
}

void EWLogic::stop()
{
    this->m_TimeKeeper->stop();
}

void EWLogic::pause()
{
    m_Warn = !m_Warn;
}

void EWLogic::updateStatus()
{
    try
    {
        this->m_TimeKeeper->updateStatus();
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
        this->m_TimeKeeper->stop();
    }
}

boost::posix_time::time_duration EWLogic::getNextStatusTimer() const
{
    return this->m_TimeKeeper->getTimerInterval();
}

std::string EWLogic::getStatus() const
{
    return this->m_TimeKeeper->getStatusStr();
}

std::string EWLogic::durationToString(boost::posix_time::time_duration duration)
{
    if (duration.is_special())
    {
        return "00:00:00";
    }
    std::stringstream out;
    out << std::setw(2) << std::setfill('0') << duration.hours() << ":" << std::setw(2)
    << std::setfill('0') << duration.minutes() << ":" << std::setw(2)
    << std::setfill('0') << duration.seconds();
    return out.str();
}

std::string EWLogic::getTimeOn() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getHereStamp().time_of_day();
    return EWLogic::durationToString(stamp);
}

std::string EWLogic::getTimeOff() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getAwayStamp().time_of_day();
    return EWLogic::durationToString(stamp);
}

std::string EWLogic::getTimeRunning() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getInterval();
    return EWLogic::durationToString(stamp);
}

std::string EWLogic::getTimeLeft() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getTimeLeft();
    return EWLogic::durationToString(stamp);
}
