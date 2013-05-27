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


#ifndef ABSTRACTEWPRESENTER_H
#define ABSTRACTEWPRESENTER_H

#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "Subject.h"
#include "EWViewObserver.h"

class ConfigData;
class AbstractEWPresenter : public Subject<EWViewObserver, AbstractEWPresenter*>
{
    public:
        AbstractEWPresenter() : m_LateMsg("Time for a pause!"),
            m_HideBtnLabel("Hide"), m_RestoreBtnLabel("Restore"),
            m_PauseBtnLabel("Pause"), m_ResumeBtnLabel("Resume"),
            m_StartBtnLabel("Start"), m_StopBtnLabel("Stop"),
            m_StopWebcamIcon("webcam-stop.png"), m_GreenWebcamIcon("webcam-green.png"),
            m_YellowWebcamIcon("webcam-yellow.png"), m_RedWebcamIcon("webcam-red.png")
        {
        }
        virtual ~AbstractEWPresenter() {}

        virtual void togglePause() = 0;
        virtual void toggleStart() = 0;
        virtual void quit() = 0;
        virtual void show(bool show) = 0;

        virtual void updateStatus() = 0;
        virtual void updateTimes() = 0;

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

#endif // ABSTRACTEWPRESENTER_H
