#include "EWPresenter.h"

#include "AbstractConfig.h"
#include "AbstractMsgHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractTimer.h"
#include "AbstractPresenceHandler.h"
#include "BaseException.h"
#include "ConfigData.h"
#include "EWViewObserver.h"

#include "boost/date_time/posix_time/posix_time.hpp"

#include <sstream>
#include <iomanip>
#include <stdlib.h>

EWPresenter::EWPresenter(AbstractMsgHandler* msgHandler, AbstractConfig* config,
                         AbstractTimeKeeper* keeper, AbstractPresenceHandler* presenceHandler,
                         AbstractTimer* checkTimer, AbstractTimer* clockTimer)
    : m_Warn(true), m_Shown(true), m_Config(config), m_TimeKeeper(keeper),
    m_MsgHandler(msgHandler), m_PresenceHandler(presenceHandler), m_CheckTimer(checkTimer),
    m_ClockTimer(clockTimer)
{
    this->m_CheckTimer->attach(this);
    this->m_ClockTimer->attach(this);
}

EWPresenter::~EWPresenter()
{
}

bool EWPresenter::saveConfig(const ConfigData& data)
{
    try
    {
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

const ConfigData& EWPresenter::getConfigData() const
{
    return this->m_Config->getData();
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
    this->notify(&EWViewObserver::OnStatusUpdate);
}

void EWPresenter::quit()
{
    this->notify(&EWViewObserver::OnQuit);
}

void EWPresenter::show(bool show)
{
    this->m_Shown = show;
    this->notify(&EWViewObserver::OnStatusUpdate);
}

void EWPresenter::updateStatus()
{
    try
    {
        this->m_TimeKeeper->updateStatus();
        this->m_CheckTimer->startTimer(this->m_TimeKeeper->getTimerInterval().total_milliseconds(), true);
        this->notify(&EWViewObserver::OnStatusUpdate);

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
    this->notify(&EWViewObserver::OnTimeUpdate);
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
    this->notify(&EWViewObserver::OnStatusUpdate);
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

std::string EWPresenter::getHideButtonLabel() const
{
    if (this->m_Shown)
    {
        return this->m_HideBtnLabel;
    }
    else
    {
        return this->m_RestoreBtnLabel;
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

std::string EWPresenter::getIconName()const
{
    if (this->m_TimeKeeper->getStatus() == AbstractTimeKeeper::OFF)
    {
        return this->m_StopWebcamIcon;
    }
    else if (this->m_TimeKeeper->getStatus() == AbstractTimeKeeper::AWAY &&
             this->m_TimeKeeper->getTimeLeft() <= boost::posix_time::seconds(0))
    {
        return this->m_GreenWebcamIcon;
    }
    else
    {
        const ConfigData& config = this->m_Config->getData();
        boost::posix_time::time_duration timeLeft = this->m_TimeKeeper->getWorkTimeLeft();
        if (timeLeft > config.runningLateThreshold)
        {
            return this->m_GreenWebcamIcon;
        }
        else if (timeLeft > boost::posix_time::seconds(0))
        {
            return this->m_YellowWebcamIcon;
        }
        else
        {
            return this->m_RedWebcamIcon;
        }
    }
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

bool EWPresenter::isShown() const
{
    return this->m_Shown;
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
        this->m_MsgHandler->displayAlert(m_LateMsg);
    }

    if (config.soundAlarm)
    {
        this->m_MsgHandler->playSound(config.soundPath);
    }
}
