#include "EWPresenter.h"

#include "AbstractMsgHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractTimer.h"
#include "BaseException.h"
#include "EWViewObserver.h"

#include "boost/date_time/posix_time/posix_time.hpp"

#include <sstream>
#include <iomanip>
#include <stdlib.h>

/// @todo: EWPresenter to EWTimeKeeperPresenter
EWPresenter::EWPresenter(AbstractMsgHandler* msgHandler, AbstractTimeKeeper* keeper,
                         AbstractTimer* checkTimer, AbstractTimer* clockTimer,
                         bool popupAlarm, bool soundAlarm, std::string soundPath,
                         boost::posix_time::time_duration runningLateThreshold)
    : m_Warn(true), m_Shown(true), m_TimeKeeper(keeper), m_MsgHandler(msgHandler),
    m_CheckTimer(checkTimer), m_ClockTimer(clockTimer), m_PopupAlarm(popupAlarm),
    m_SoundAlarm(soundAlarm), m_SoundPath(soundPath), m_RunningLateThreshold(runningLateThreshold)
{
    this->m_CheckTimer->attach(this);
    this->m_ClockTimer->attach(this);
}

EWPresenter::~EWPresenter()
{
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
        boost::posix_time::time_duration timeLeft = this->m_TimeKeeper->getWorkTimeLeft();
        if (timeLeft > this->m_RunningLateThreshold)
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

void EWPresenter::setRunningLateThreshold(
            boost::posix_time::time_duration runningLateThreshold)
{
    this->m_RunningLateThreshold = runningLateThreshold;
}

void EWPresenter::setPopupAlarm(bool popupAlarm)
{
    this->m_PopupAlarm = popupAlarm;
}

void EWPresenter::setSoundAlarm(bool soundAlarm)
{
    this->m_SoundAlarm = soundAlarm;
}

void EWPresenter::setSoundPath(std::string soundPath)
{
    this->m_SoundPath = soundPath;
}

/// @todo: does this belong there?
void EWPresenter::alert()
{
    if (!this->m_Warn)
    {
        return;
    }
    if (this->m_PopupAlarm)
    {
        this->m_MsgHandler->displayAlert(m_LateMsg);
    }

    if (this->m_SoundAlarm)
    {
        this->m_MsgHandler->playSound(this->m_SoundPath);
    }
}
