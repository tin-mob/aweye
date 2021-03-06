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
///@todo possible improvement : separate all the std::string get*
/// from the actions. would allow for views with different behaviour


#ifndef TKCONTROLLER_H
#define TKCONTROLLER_H

#include "aweye/core/AbstractTimer.h"
#include "aweye/core/AbstractTKController.h"
#include "aweye/core/AbstractUtils.h"
#include "aweye/core/TaskExceptionObserver.h"

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <memory>
#include <string>

namespace Aweye {

class AbstractMsgHandler;
class AbstractTimeHandler;
class AbstractTimeKeeper;
class BaseException;
class TKController : public AbstractTKController, public TimerInterface, public TaskExceptionObserver
{
    public:
        TKController(AbstractMsgHandler& msgHandler, AbstractTimeKeeper& keeper,
                    AbstractTimer& clockTimer, AbstractTimeHandler& timeHandler,
                    AbstractUtils& utils,
                    bool popupAlarm = true, bool soundAlarm = false, std::string soundPath = "",
                    boost::posix_time::time_duration runningLateThreshold = boost::posix_time::minutes(4));
        virtual ~TKController();

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

        virtual void onException(std::shared_ptr<const BaseException> exception);

    protected:
    private:
        void manageException(const BaseException& exception);
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
        AbstractUtils& m_Utils;

        bool m_PopupAlarm;
        bool m_SoundAlarm;
        std::string m_SoundPath;
        boost::posix_time::time_duration m_RunningLateThreshold;
        boost::posix_time::ptime m_LastAlert;
};
}

#endif // TKCONTROLLER_H
