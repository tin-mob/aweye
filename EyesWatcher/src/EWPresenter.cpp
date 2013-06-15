/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "EWPresenter.h"
#include "AbstractMsgHandler.h"
#include "AbstractTimeHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractTimer.h"
#include "BaseException.h"
#include "EWViewObserver.h"

#include "boost/date_time/posix_time/posix_time.hpp"

#include <sstream>
#include <iomanip>
#include <stdlib.h>

/// @todo EWPresenter to EWTimeKeeperController,
EWPresenter::EWPresenter(AbstractMsgHandler& msgHandler, AbstractTimeKeeper& keeper,
                         AbstractTimer& checkTimer, AbstractTimer& clockTimer,
                         AbstractTimeHandler& timeHandler,
                         bool popupAlarm, bool soundAlarm, std::string soundPath,
                         boost::posix_time::time_duration runningLateThreshold)
    : m_Warn(true), m_Shown(true), m_TimeKeeper(keeper), m_MsgHandler(msgHandler),
    m_CheckTimer(checkTimer), m_ClockTimer(clockTimer), m_TimeHandler(timeHandler),
    m_PopupAlarm(popupAlarm), m_SoundAlarm(soundAlarm), m_SoundPath(soundPath),
    m_RunningLateThreshold(runningLateThreshold),
    m_LastTimeUpdate(boost::posix_time::not_a_date_time)
{
    m_CheckTimer.attach(this);
    m_ClockTimer.attach(this);
}

EWPresenter::~EWPresenter()
{
}

void EWPresenter::start()
{
    try
    {
        m_TimeKeeper.start();
        m_CheckTimer.startTimer(m_TimeKeeper.getTimerInterval().total_milliseconds(), true);
        notify(&EWViewObserver::OnStatusUpdate, this);

        m_ClockTimer.startTimer(1000, false);
        m_LastTimeUpdate = m_TimeHandler.getTime();
    }
    catch (BaseException e)
    {
        m_MsgHandler.displayError(e.what());
    }
}

void EWPresenter::stop()
{
    m_TimeKeeper.stop();
    m_CheckTimer.stopTimer();
    m_ClockTimer.stopTimer();
    notify(&EWViewObserver::OnStatusUpdate, this);
}

void EWPresenter::quit()
{
    notify(&EWViewObserver::OnQuit, this);
}

void EWPresenter::show(bool show)
{
    m_Shown = show;
    notify(&EWViewObserver::OnStatusUpdate, this);
}

void EWPresenter::updateStatus()
{
    try
    {
        m_TimeKeeper.updateStatus();
        m_CheckTimer.startTimer(m_TimeKeeper.getTimerInterval().total_milliseconds(), true);
        notify(&EWViewObserver::OnStatusUpdate, this);

        if (m_TimeKeeper.isLate() && m_TimeKeeper.getStatus() == AbstractTimeKeeper::HERE)
        {
            alert();
        }
    }
    catch (BaseException e)
    {
        m_MsgHandler.displayError(e.what());
        m_TimeKeeper.stop();
    }
}

void EWPresenter::updateTimes()
{
    // if it has been a long time since last ring and is running, we have hibernated
    if (m_TimeHandler.getTime() - m_LastTimeUpdate >
        boost::posix_time::minutes(1))
    {
        m_TimeKeeper.notifyHibernated();

        m_CheckTimer.startTimer(m_TimeKeeper.getTimerInterval().total_milliseconds(), true);
        notify(&EWViewObserver::OnStatusUpdate, this);

        if (m_TimeKeeper.isLate() && m_TimeKeeper.getStatus() == AbstractTimeKeeper::HERE)
        {
            alert();
        }
    }

    notify(&EWViewObserver::OnTimeUpdate, this);
    m_LastTimeUpdate = m_TimeHandler.getTime();
}

void EWPresenter::onTimerRing(AbstractTimer* timer)
{
    if (timer == &m_ClockTimer)
    {
        updateTimes();
    }
    else if (timer == &m_CheckTimer)
    {
        updateStatus();
    }
    else
    {
        assert(0);
    }
}

void EWPresenter::togglePause()
{
    m_Warn = !m_Warn;
    notify(&EWViewObserver::OnStatusUpdate, this);
}

void EWPresenter::toggleStart()
{
    if(m_TimeKeeper.getStatus() != AbstractTimeKeeper::OFF)
    {
        stop();
    }
    else
    {
        start();
    }
}

std::string EWPresenter::getHideButtonLabel() const
{
    if (m_Shown)
    {
        return m_HideBtnLabel;
    }
    else
    {
        return m_RestoreBtnLabel;
    }
}

std::string EWPresenter::getPauseButtonLabel() const
{
    if (m_Warn)
    {
        return m_PauseBtnLabel;
    }
    else
    {
        return m_ResumeBtnLabel;
    }
}

std::string EWPresenter::getStartButtonLabel() const
{
    if (m_TimeKeeper.getStatus() != AbstractTimeKeeper::OFF)
    {
        return m_StopBtnLabel;
    }
    else
    {
        return m_StartBtnLabel;
    }
}


std::string EWPresenter::getStatus() const
{
    return m_TimeKeeper.getStatusStr();
}

std::string EWPresenter::getIconName()const
{
    if (m_TimeKeeper.getStatus() == AbstractTimeKeeper::OFF)
    {
        return m_StopWebcamIcon;
    }
    else if (m_TimeKeeper.getStatus() == AbstractTimeKeeper::AWAY &&
             m_TimeKeeper.getTimeLeft() <= boost::posix_time::seconds(0))
    {
        return m_GreenWebcamIcon;
    }
    else
    {
        const boost::posix_time::time_duration timeLeft = m_TimeKeeper.getWorkTimeLeft();
        if (timeLeft > m_RunningLateThreshold)
        {
            return m_GreenWebcamIcon;
        }
        else if (timeLeft > boost::posix_time::seconds(0))
        {
            return m_YellowWebcamIcon;
        }
        else
        {
            return m_RedWebcamIcon;
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

    out << std::setw(2) << std::setfill('0') << abs(duration.hours()) << ":" << std::setw(2)
    << std::setfill('0') << abs(duration.minutes()) << ":" << std::setw(2)
    << std::setfill('0') << abs(duration.seconds());
    return out.str();
}

std::string EWPresenter::getTimeOn() const
{
    const boost::posix_time::time_duration stamp = m_TimeKeeper.getHereStamp().time_of_day();
    return EWPresenter::durationToString(stamp);
}

std::string EWPresenter::getTimeOff() const
{
    const boost::posix_time::time_duration stamp = m_TimeKeeper.getAwayStamp().time_of_day();
    return EWPresenter::durationToString(stamp);
}

std::string EWPresenter::getTimeRunning() const
{
    const boost::posix_time::time_duration stamp = m_TimeKeeper.getInterval();
    return EWPresenter::durationToString(stamp);
}

std::string EWPresenter::getTimeLeft() const
{
    const boost::posix_time::time_duration stamp = m_TimeKeeper.getTimeLeft();
    return EWPresenter::durationToString(stamp);
}

bool EWPresenter::isShown() const
{
    return m_Shown;
}

void EWPresenter::setRunningLateThreshold(
            boost::posix_time::time_duration runningLateThreshold)
{
    m_RunningLateThreshold = runningLateThreshold;
}

void EWPresenter::setPopupAlarm(bool popupAlarm)
{
    m_PopupAlarm = popupAlarm;
}

void EWPresenter::setSoundAlarm(bool soundAlarm)
{
    m_SoundAlarm = soundAlarm;
}

void EWPresenter::setSoundPath(std::string soundPath)
{
    m_SoundPath = soundPath;
}

void EWPresenter::alert()
{
    if (!m_Warn)
    {
        return;
    }
    if (m_PopupAlarm)
    {
        m_MsgHandler.displayAlert(m_LateMsg);
    }

    if (m_SoundAlarm)
    {
        m_MsgHandler.playSound(m_SoundPath);
    }
}
