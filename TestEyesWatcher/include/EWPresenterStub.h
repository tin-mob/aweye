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
#include "AbstractTimeKeeper.h"
#include "AbstractTimer.h"
#include <string>

// That's a big stub...
class EWPresenterStub : public AbstractEWPresenter
{
    public:
        EWPresenterStub(AbstractMsgHandler* mH = nullptr, AbstractTimeKeeper* k = nullptr,
            AbstractTimer* chT = nullptr, AbstractTimer* clT = nullptr, bool pA = false,
            bool sA = false, std::string sP = "",
            boost::posix_time::time_duration rLT = boost::posix_time::seconds(0)) :
            popupAlarm(pA), soundAlarm(sA), soundPath(sP), runningLateThreshold(rLT),
            paused(false), started(false), quitted(false),
            shown(false), statusUpdated(false), timesUpdated(false),
            hideButtonLabel(""), pauseButtonLabel(""), startButtonLabel(""), status(""),
            timeOn(""), timeOff(""), timeRunning(""), timeLeft(""), icon(""),
            msgHandler(mH), keeper(k), checkTimer(chT), clockTimer(clT) {}
        virtual ~EWPresenterStub() {}

        virtual void togglePause() {paused = !paused;}
        virtual void toggleStart() {started = !started;}
        virtual void quit() {quitted = true;}
        virtual void show(bool show) {shown = show;}

        virtual void updateStatus() {statusUpdated = true;}
        virtual void updateTimes() {timesUpdated = true;}

        virtual std::string getHideButtonLabel() const {return hideButtonLabel;}
        virtual std::string getPauseButtonLabel() const {return pauseButtonLabel;}
        virtual std::string getStartButtonLabel() const {return startButtonLabel;}
        virtual std::string getStatus() const {return status;}
        virtual std::string getTimeOn() const {return timeOn;}
        virtual std::string getTimeOff() const {return timeOff;}
        virtual std::string getTimeRunning() const {return timeRunning;}
        virtual std::string getTimeLeft() const {return timeLeft;}
        virtual bool isShown() const {return shown;}
        virtual std::string getIconName()const {return icon;}

        virtual void setRunningLateThreshold(
            boost::posix_time::time_duration val) {runningLateThreshold = val;}
        virtual void setPopupAlarm(bool val) {popupAlarm = val;}
        virtual void setSoundAlarm(bool val) {soundAlarm = val;}
        virtual void setSoundPath(std::string val) {soundPath = val;}

        void notifyStatus() {notify(&EWViewObserver::OnStatusUpdate, this);}
        void notifyTime() {notify(&EWViewObserver::OnTimeUpdate, this);}
        void notifyQuit() {notify(&EWViewObserver::OnQuit, this);}

        void setDisplayValues(std::string hbl, std::string pbl, std::string sbl,
                              std::string s, std::string ton, std::string toff,
                              std::string tr, std::string tl, bool is, std::string in)
        {
            hideButtonLabel = hbl;
            pauseButtonLabel = pbl;
            startButtonLabel = sbl;
            status = s;
            timeOn = ton;
            timeOff = toff;
            timeRunning = tr;
            timeLeft = tl;
            shown = is;
            icon = in;
        }

        bool popupAlarm;
        bool soundAlarm;
        std::string soundPath;
        boost::posix_time::time_duration runningLateThreshold;

        bool paused;
        bool started;
        bool quitted;
        bool shown;
        bool statusUpdated;
        bool timesUpdated;

        std::string hideButtonLabel;
        std::string pauseButtonLabel;
        std::string startButtonLabel;
        std::string status;
        std::string timeOn;
        std::string timeOff;
        std::string timeRunning;
        std::string timeLeft;
        std::string icon;

        AbstractMsgHandler* msgHandler;
        AbstractTimeKeeper* keeper;
        AbstractTimer* checkTimer;
        AbstractTimer* clockTimer;

    protected:
    private:
};

#endif // EWPRESENTERSTUB_H
