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

#ifndef EWPRESENTER_H
#define EWPRESENTER_H

#include <string>
#include "boost/date_time/posix_time/posix_time_types.hpp"

#include "AbstractEWPresenter.h"
#include "AbstractTimer.h"

class AbstractConfig;
class AbstractMsgHandler;
class AbstractTimeHandler;
class AbstractTimeKeeper;
class AbstractPresenceHandler;
class AbstractTimer;
class ConfigData;

///@todo possible improvement : separate all the std::string get*
/// from the actions. would allow for views with different behaviour

class EWPresenter : public AbstractEWPresenter, public TimerInterface
{
    public:
        EWPresenter(AbstractMsgHandler& msgHandler, AbstractTimeKeeper& keeper,
                    AbstractTimer& clockTimer, AbstractTimeHandler& timeHandler,
                    bool popupAlarm = true, bool soundAlarm = false, std::string soundPath = "",
                    boost::posix_time::time_duration runningLateThreshold = boost::posix_time::minutes(4));
        virtual ~EWPresenter();

        virtual void togglePause();
        virtual void toggleStart();
        virtual void quit();
        virtual void show(bool show);

        virtual void onTimerRing(AbstractTimer* timer);

        virtual std::string getHideButtonLabel() const;
        virtual std::string getPauseButtonLabel() const;
        virtual std::string getStartButtonLabel() const;
        virtual std::string getStatus() const;
        virtual std::string getTimeOn() const;
        virtual std::string getTimeOff() const;
        virtual std::string getTimeRunning() const;
        virtual std::string getTimeLeft() const;
        virtual bool isShown() const;
        virtual std::string getIconName()const;

        virtual void setRunningLateThreshold(
            boost::posix_time::time_duration runningLateThreshold);
        virtual void setPopupAlarm(bool popupAlarm);
        virtual void setSoundAlarm(bool soundAlarm);
        virtual void setSoundPath(std::string soundPath);

    protected:
    private:
        static std::string durationToString(boost::posix_time::time_duration duration);

        void alert();
        void start();
        void stop();

        bool m_Warn;
        bool m_Shown;

        AbstractTimeKeeper& m_TimeKeeper;
        AbstractMsgHandler& m_MsgHandler;
        AbstractTimer& m_ClockTimer;
        AbstractTimeHandler& m_TimeHandler;

        bool m_PopupAlarm;
        bool m_SoundAlarm;
        std::string m_SoundPath;
        boost::posix_time::time_duration m_RunningLateThreshold;
        boost::posix_time::ptime m_LastAlert;
};

#endif // EWPRESENTER_H
