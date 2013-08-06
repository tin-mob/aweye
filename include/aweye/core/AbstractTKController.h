/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef ABSTRACTTKCONTROLLER_H
#define ABSTRACTTKCONTROLLER_H

#include "aweye/core/tr.h"
#include "aweye/core/Subject.h"

#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace Aweye {

struct ConfigData;
class TKControllerObserver;
class AbstractTKController : public Subject<TKControllerObserver>
{
    public:
        AbstractTKController() : m_LateMsg(tr("Time for a pause!")),
            m_HideBtnLabel(tr("Hide")), m_RestoreBtnLabel(tr("Restore")),
            m_PauseBtnLabel(tr("Mute")), m_ResumeBtnLabel(tr("Resume")),
            m_StartBtnLabel(tr("Start")), m_StopBtnLabel(tr("Stop")),
            m_StopWebcamIcon("icons/webcam-stop.png"),
            m_GreenWebcamIcon("icons/webcam-green.png"),
            m_YellowWebcamIcon("icons/webcam-yellow.png"),
            m_RedWebcamIcon("icons/webcam-red.png")
        {
        }
        virtual ~AbstractTKController() {}

        virtual void togglePause() = 0;
        virtual void toggleStart() = 0;
        virtual void quit() = 0;
        virtual void show(bool show) = 0;

        virtual std::string getHideButtonLabel() const = 0;
        virtual std::string getPauseButtonLabel() const = 0;
        virtual std::string getStartButtonLabel() const = 0;
        virtual std::string getStatus() const = 0;
        virtual std::string getTimeOn() const = 0;
        virtual std::string getTimeOff() const = 0;
        virtual std::string getTimeRunning() const = 0;
        virtual std::string getTimeLeft() const = 0;
        virtual bool isShown() const = 0;
        virtual std::string getIconName()const = 0;

        virtual void setRunningLateThreshold(
            boost::posix_time::time_duration runningLateThreshold) = 0;
        virtual void setPopupAlarm(bool popupAlarm) = 0;
        virtual void setSoundAlarm(bool soundAlarm) = 0;
        virtual void setSoundPath(std::string soundPath) = 0;

        const std::string m_LateMsg;
        const std::string m_HideBtnLabel;
        const std::string m_RestoreBtnLabel;
        const std::string m_PauseBtnLabel;
        const std::string m_ResumeBtnLabel;
        const std::string m_StartBtnLabel;
        const std::string m_StopBtnLabel;

        const std::string m_StopWebcamIcon;
        const std::string m_GreenWebcamIcon;
        const std::string m_YellowWebcamIcon;
        const std::string m_RedWebcamIcon;
    protected:
    private:
};
}

#endif // ABSTRACTTKCONTROLLER_H
