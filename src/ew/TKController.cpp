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


#include "ew/AbstractMsgHandler.h"
#include "ew/AbstractTimeHandler.h"
#include "ew/AbstractTimeKeeper.h"
#include "ew/AbstractTimer.h"
#include "ew/BaseException.h"
#include "ew/TKController.h"
#include "ew/TKControllerObserver.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <iomanip>
#include <sstream>
#include <stdlib.h>

namespace EW {

TKController::TKController(AbstractMsgHandler& msgHandler, AbstractTimeKeeper& keeper,
                         AbstractTimer& clockTimer, AbstractTimeHandler& timeHandler,
                         AbstractUtils& utils,
                         bool popupAlarm, bool soundAlarm, std::string soundPath,
                         boost::posix_time::time_duration runningLateThreshold)
    : m_Warn(true), m_Shown(true), m_TimeKeeper(keeper), m_MsgHandler(msgHandler),
    m_ClockTimer(clockTimer), m_TimeHandler(timeHandler), m_Utils(utils),
    m_PopupAlarm(popupAlarm), m_SoundAlarm(soundAlarm), m_SoundPath(soundPath),
    m_RunningLateThreshold(runningLateThreshold),
    m_LastAlert(boost::posix_time::not_a_date_time)
{
    m_ClockTimer.attach(this);
}

TKController::~TKController()
{
    m_ClockTimer.detach(this);
}

void TKController::start()
{
    try
    {
        m_TimeKeeper.start();
        notify(&TKControllerObserver::OnStatusUpdate);
        m_ClockTimer.startTimer(1000, false);
    }
    catch (...)
    {
        onException(std::current_exception());
    }
}

void TKController::stop()
{
    m_TimeKeeper.stop();
    m_ClockTimer.stopTimer();
    notify(&TKControllerObserver::OnStatusUpdate);
}

void TKController::quit()
{
    notify(&TKControllerObserver::OnQuit);
}

void TKController::show(bool show)
{
    m_Shown = show;
    notify(&TKControllerObserver::OnStatusUpdate);
}

void TKController::onTimerRing(AbstractTimer*)
{
    try
    {
        if(m_TimeKeeper.checkUpdate())
        {
            notify(&TKControllerObserver::OnStatusUpdate);

            bool late = m_TimeKeeper.isLate();
            bool here = m_TimeKeeper.getStatus() == AbstractTimeKeeper::HERE;
            bool isAlertTime = m_LastAlert.is_special() ||
                m_TimeHandler.getTime() >= m_LastAlert + m_TimeKeeper.getRemFreq();
            bool intolerant = !m_TimeKeeper.isTolerating();

            if (late && here && isAlertTime && intolerant)
            {
                alert();
            }
        }
        else
        {
            notify(&TKControllerObserver::OnTimeUpdate);
        }
    }
    catch (...)
    {
        onException(std::current_exception());
    }
}

void TKController::togglePause()
{
    m_Warn = !m_Warn;
    notify(&TKControllerObserver::OnStatusUpdate);
}

void TKController::toggleStart()
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

///@note convert to real shared_ptr to remove silly try?
/// No, it allows to Exception not derived from BaseException
/// to stop the app.
void TKController::onException(const std::exception_ptr exception)
{
    try
    {
        std::rethrow_exception(exception);
    }
    catch (const BaseException& e)
    {
        stop();
        m_MsgHandler.displayError(e.what());
    }
}

std::string TKController::getHideButtonLabel() const
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

std::string TKController::getPauseButtonLabel() const
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

std::string TKController::getStartButtonLabel() const
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


std::string TKController::getStatus() const
{
    return m_TimeKeeper.getStatusStr();
}

std::string TKController::getIconName()const
{
    std::string iconName;
    if (m_TimeKeeper.getStatus() == AbstractTimeKeeper::OFF)
    {
        iconName += m_StopWebcamIcon;
    }
    else if (m_TimeKeeper.getStatus() == AbstractTimeKeeper::AWAY &&
             m_TimeKeeper.getTimeLeft() <= boost::posix_time::seconds(0))
    {
        iconName += m_GreenWebcamIcon;
    }
    else
    {
        const boost::posix_time::time_duration timeLeft = m_TimeKeeper.getWorkTimeLeft();
        if (timeLeft > m_RunningLateThreshold)
        {
            iconName += m_GreenWebcamIcon;
        }
        else if (timeLeft > boost::posix_time::seconds(0))
        {
            iconName += m_YellowWebcamIcon;
        }
        else
        {
            iconName += m_RedWebcamIcon;
        }
    }
    return m_Utils.getDataPath(iconName);
}

std::string TKController::durationToString(boost::posix_time::time_duration duration)
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

std::string TKController::getTimeOn() const
{
    const boost::posix_time::time_duration stamp = m_TimeKeeper.getHereStamp().time_of_day();
    return TKController::durationToString(stamp);
}

std::string TKController::getTimeOff() const
{
    const boost::posix_time::time_duration stamp = m_TimeKeeper.getAwayStamp().time_of_day();
    return TKController::durationToString(stamp);
}

std::string TKController::getTimeRunning() const
{
    const boost::posix_time::time_duration stamp = m_TimeKeeper.getInterval();
    return TKController::durationToString(stamp);
}

std::string TKController::getTimeLeft() const
{
    const boost::posix_time::time_duration stamp = m_TimeKeeper.getTimeLeft();
    return TKController::durationToString(stamp);
}

bool TKController::isShown() const
{
    return m_Shown;
}

void TKController::setRunningLateThreshold(
            boost::posix_time::time_duration runningLateThreshold)
{
    m_RunningLateThreshold = runningLateThreshold;
}

void TKController::setPopupAlarm(bool popupAlarm)
{
    m_PopupAlarm = popupAlarm;
}

void TKController::setSoundAlarm(bool soundAlarm)
{
    m_SoundAlarm = soundAlarm;
}

void TKController::setSoundPath(std::string soundPath)
{
    m_SoundPath = soundPath;
}

///@note should alert timing be here or in timekeeper?
void TKController::alert()
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
    m_LastAlert = m_TimeHandler.getTime();
}
}
