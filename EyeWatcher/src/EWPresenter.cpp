#include "EWPresenter.h"

#include "AbstractConfig.h"
#include "AbstractMsgHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractTimer.h"
#include "AbstractPresenceHandler.h"
#include "AbstractOptionsDialog.h"
#include "BaseException.h"
#include "ConfigData.h"
#include "Command.h"

#include "boost/date_time/posix_time/posix_time.hpp"

#include <sstream>
#include <iomanip>
#include <stdlib.h>

EWPresenter::EWPresenter(AbstractMsgHandler* msgHandler, AbstractConfig* config,
                         AbstractTimeKeeper* keeper, AbstractPresenceHandler* presenceHandler,
                         AbstractTimer* checkTimer, AbstractTimer* clockTimer, Command* exitCmd)
    :  m_LateMsg("Time for a pause!"), m_PauseBtnLabel("Pause"), m_ResumeBtnLabel("Resume"),
    m_StartBtnLabel("Start"), m_StopBtnLabel("Stop"), m_Warn(true), m_Config(config),
    m_TimeKeeper(keeper), m_MsgHandler(msgHandler), m_PresenceHandler(presenceHandler),
    m_CheckTimer(checkTimer), m_ClockTimer(clockTimer), m_ExitCmd(exitCmd)
{
    this->m_CheckTimer->attach(this);
    this->m_ClockTimer->attach(this);
}

EWPresenter::~EWPresenter()
{
}

bool EWPresenter::saveConfig(const AbstractOptionsDialog* dialog)
{
    try
    {
        ConfigData data = dialog->getData();
        this->m_Config->save(data);

        this->m_PresenceHandler->setCascade(data.cascadePath);
        this->m_PresenceHandler->setFaceSize(data.faceSizeX, data.faceSizeY);
        this->m_PresenceHandler->setIndex(data.webcamIndex);

        this->m_TimeKeeper->setCheckFreq(data.checkFreq);
        this->m_TimeKeeper->setPauseLength(data.pauseLength);
        this->m_TimeKeeper->setPauseTol(data.pauseTol);
        this->m_TimeKeeper->setRemFreq(data.remFreq);
        this->m_TimeKeeper->setWorkLength(data.workLength);
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
        return false;
    }
    return true;
}

void EWPresenter::loadConfig(AbstractOptionsDialog* dialog)
{
    dialog->setData(this->m_Config->getData());
}

void EWPresenter::start()
{
    try
    {
        this->m_TimeKeeper->start();
        this->updateStatus();
        this->m_ClockTimer->startTimer(1000, false);
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
    }
}

void EWPresenter::stop()
{
    this->m_TimeKeeper->stop();
    this->m_CheckTimer->stopTimer();
    this->m_ClockTimer->stopTimer();
    this->notify();
}

void EWPresenter::quit()
{
    this->m_ExitCmd->execute();
}

void EWPresenter::updateStatus()
{
    try
    {
        this->m_TimeKeeper->updateStatus();
        this->m_CheckTimer->startTimer(this->m_TimeKeeper->getTimerInterval().total_milliseconds(), true);
        this->notify();

        if (this->m_TimeKeeper->isLate() && this->m_TimeKeeper->getStatus() == AbstractTimeKeeper::HERE)
        {
            this->alert();
        }
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
        this->m_TimeKeeper->stop();
    }
}

void EWPresenter::updateTimes()
{
    this->notify();
}

void EWPresenter::update(Observable* source)
{
    if (source == this->m_ClockTimer)
    {
        this->updateTimes();
    }
    else if (source == this->m_CheckTimer)
    {
        this->updateStatus();
    }
    else
    {
        assert(0);
    }
}

void EWPresenter::togglePause()
{
    m_Warn = !m_Warn;
    this->notify();
}

void EWPresenter::toggleStart()
{
    if(this->m_TimeKeeper->getStatus() != AbstractTimeKeeper::OFF)
    {
        this->stop();
    }
    else
    {
        this->start();
    }
}

std::string EWPresenter::getPauseButtonLabel() const
{
    if (this->m_Warn)
    {
        return this->m_PauseBtnLabel;
    }
    else
    {
        return this->m_ResumeBtnLabel;
    }
}

std::string EWPresenter::getStartButtonLabel() const
{
    if (this->m_TimeKeeper->getStatus() != AbstractTimeKeeper::OFF)
    {
        return this->m_StopBtnLabel;
    }
    else
    {
        return this->m_StartBtnLabel;
    }
}


std::string EWPresenter::getStatus() const
{
    return this->m_TimeKeeper->getStatusStr();
}

std::string EWPresenter::durationToString(boost::posix_time::time_duration duration)
{
    if (duration.is_special())
    {
        return "00:00:00";
    }
    std::stringstream out;
    if (duration.seconds() < 0)
    {
        out << "-";
    }

    out << std::setw(2) << std::setfill('0') << duration.hours() << ":" << std::setw(2)
    << std::setfill('0') << duration.minutes() << ":" << std::setw(2)
    << std::setfill('0') << abs(duration.seconds());
    return out.str();
}

std::string EWPresenter::getTimeOn() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getHereStamp().time_of_day();
    return EWPresenter::durationToString(stamp);
}

std::string EWPresenter::getTimeOff() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getAwayStamp().time_of_day();
    return EWPresenter::durationToString(stamp);
}

std::string EWPresenter::getTimeRunning() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getInterval();
    return EWPresenter::durationToString(stamp);
}

std::string EWPresenter::getTimeLeft() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getTimeLeft();
    return EWPresenter::durationToString(stamp);
}

void EWPresenter::alert()
{
    if (!this->m_Warn)
    {
        return;
    }

    const ConfigData& config = this->m_Config->getData();
    if (config.popupAlarm)
    {
        //sadly, only available in wxwidgets 2.9
        //frame->notifyMessage(m_LateMsg);

        // remove when notify is working...
        this->m_MsgHandler->displayAlert(m_LateMsg);
    }

    if (config.soundAlarm)
    {
        this->m_MsgHandler->playSound(config.soundPath);
    }

    if (config.emailAlarm)
    {
        ///@todo
    }
}
