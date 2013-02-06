#include "EWLogic.h"
#include "AbstractConfig.h"
#include "HandlerFactory.h"
#include "AbstractMsgHandler.h"
#include "AbstractTimeKeeper.h"

#include "BaseException.h"

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

AbstractTimeKeeper::Status EWLogic::getStatus() const
{
    return this->m_TimeKeeper->getStatus();
}

std::string EWLogic::getTimeOn() const
{
    return "";
}

std::string EWLogic::getTimeOff() const
{
    return "";
}

std::string EWLogic::getLastPause() const
{
    return "";
}

std::string EWLogic::getTimeLeft() const
{
    return "";
}
