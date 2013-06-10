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


#ifndef EWPRESENTERSTUB_H
#define EWPRESENTERSTUB_H

#include "AbstractEWPresenter.h"
#include "AbstractMsgHandler.h"
#include "AbstractTimeHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractTimer.h"
#include <string>

// That's a big stub...
class EWPresenterStub : public AbstractEWPresenter
{
    public:
        EWPresenterStub(AbstractMsgHandler* mH = nullptr, AbstractTimeKeeper* k = nullptr,
            AbstractTimer* chT = nullptr, AbstractTimer* clT = nullptr,
            AbstractTimeHandler* tH = nullptr, bool pA = false,
            bool sA = false, std::string sP = "",
            boost::posix_time::time_duration rLT = boost::posix_time::seconds(0)) :
            popupAlarm(pA), soundAlarm(sA), soundPath(sP), runningLateThreshold(rLT),
            paused(false), started(false), quitted(false),
            statusUpdated(false), timesUpdated(false), displayValues(),
            msgHandler(mH), keeper(k), checkTimer(chT), clockTimer(clT), timeHandler(tH) {}
        virtual ~EWPresenterStub() {}

        virtual void togglePause() {paused = !paused;}
        virtual void toggleStart() {started = !started;}
        virtual void quit() {quitted = true;}
        virtual void show(bool show) {displayValues.shown = show;}

        virtual void updateStatus() {statusUpdated = true;}
        virtual void updateTimes() {timesUpdated = true;}

        virtual std::string getHideButtonLabel() const {return displayValues.hideButtonLabel;}
        virtual std::string getPauseButtonLabel() const {return displayValues.pauseButtonLabel;}
        virtual std::string getStartButtonLabel() const {return displayValues.startButtonLabel;}
        virtual std::string getStatus() const {return displayValues.status;}
        virtual std::string getTimeOn() const {return displayValues.timeOn;}
        virtual std::string getTimeOff() const {return displayValues.timeOff;}
        virtual std::string getTimeRunning() const {return displayValues.timeRunning;}
        virtual std::string getTimeLeft() const {return displayValues.timeLeft;}
        virtual bool isShown() const {return displayValues.shown;}
        virtual std::string getIconName()const {return displayValues.icon;}

        virtual void setRunningLateThreshold(
            boost::posix_time::time_duration val) {runningLateThreshold = val;}
        virtual void setPopupAlarm(bool val) {popupAlarm = val;}
        virtual void setSoundAlarm(bool val) {soundAlarm = val;}
        virtual void setSoundPath(std::string val) {soundPath = val;}

        void notifyStatus() {notify(&EWViewObserver::OnStatusUpdate, this);}
        void notifyTime() {notify(&EWViewObserver::OnTimeUpdate, this);}
        void notifyQuit() {notify(&EWViewObserver::OnQuit, this);}


        struct DisplayValues
        {
            DisplayValues(bool s = false, std::string hbl = "", std::string pbl = "",
                std::string sbl = "", std::string st = "", std::string ton = "",
                std::string tof = "", std::string tr = "", std::string tl = "",
                std::string i = "") :
                shown(s), hideButtonLabel(hbl), pauseButtonLabel(pbl),
                startButtonLabel(sbl), status(st), timeOn(ton), timeOff(tof),
                timeRunning(tr), timeLeft(tl), icon(i) {}

            static DisplayValues getTestValues(bool shown = true, bool hasIcon = true)
            {
                return {shown, "hbl", "pbl", "sbl", "s", "ton", "toff", "tr",
                        "tl", hasIcon ? "in" : ""};
            }
            bool shown;
            std::string hideButtonLabel;
            std::string pauseButtonLabel;
            std::string startButtonLabel;
            std::string status;
            std::string timeOn;
            std::string timeOff;
            std::string timeRunning;
            std::string timeLeft;
            std::string icon;
        };
        void setDisplayValues(const DisplayValues& v){displayValues = v;}

        bool popupAlarm;
        bool soundAlarm;
        std::string soundPath;
        boost::posix_time::time_duration runningLateThreshold;

        bool paused;
        bool started;
        bool quitted;
        bool statusUpdated;
        bool timesUpdated;

        DisplayValues displayValues;

        AbstractMsgHandler* msgHandler;
        AbstractTimeKeeper* keeper;
        AbstractTimer* checkTimer;
        AbstractTimer* clockTimer;
        AbstractTimeHandler* timeHandler;

    protected:
    private:
};

#endif // EWPRESENTERSTUB_H
