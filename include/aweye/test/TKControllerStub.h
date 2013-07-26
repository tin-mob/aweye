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


#ifndef TKCONTROLLERSTUB_H
#define TKCONTROLLERSTUB_H

#include "aweye/core/AbstractMsgHandler.h"
#include "aweye/core/AbstractTimeHandler.h"
#include "aweye/core/AbstractTimeKeeper.h"
#include "aweye/core/AbstractTimer.h"
#include "aweye/core/AbstractTKController.h"
#include "aweye/core/TKControllerObserver.h"
#include "aweye/test/UtilsStub.h"

#include <string>

namespace Aweye
{
class TKControllerStub : public AbstractTKController
{
    public:
        TKControllerStub(AbstractMsgHandler* mH = nullptr, AbstractTimeKeeper* k = nullptr,
            AbstractTimer* clT = nullptr, AbstractTimeHandler* tH = nullptr,
            AbstractUtils* u = nullptr, bool pA = false, bool sA = false, std::string sP = "",
            boost::posix_time::time_duration rLT = boost::posix_time::seconds(0)) :
            m_PopupAlarm(pA), m_SoundAlarm(sA), m_SoundPath(sP),
            m_RunningLateThreshold(rLT), m_Paused(false), m_Started(false), m_Quitted(false),
            m_StatusUpdated(false), m_TimesUpdated(false), m_DisplayValues(),
            m_MsgHandler(mH), m_Keeper(k), m_ClockTimer(clT), m_TimeHandler(tH),
            m_Utils(u) {}

        TKControllerStub(AbstractMsgHandler& mH, AbstractTimeKeeper& k,
            AbstractTimer& clT, AbstractTimeHandler& tH, AbstractUtils& utils, bool pA,
            bool sA, std::string sP, boost::posix_time::time_duration rLT) :
            m_PopupAlarm(pA), m_SoundAlarm(sA), m_SoundPath(sP),
            m_RunningLateThreshold(rLT), m_Paused(false), m_Started(false), m_Quitted(false),
            m_StatusUpdated(false), m_TimesUpdated(false), m_DisplayValues(),
            m_MsgHandler(&mH), m_Keeper(&k), m_ClockTimer(&clT), m_TimeHandler(&tH),
            m_Utils(&utils) {}

        virtual ~TKControllerStub() {}

        virtual void togglePause() {m_Paused = !m_Paused;}
        virtual void toggleStart() {m_Started = !m_Started;}
        virtual void quit() {m_Quitted = true;}
        virtual void show(bool show) {m_DisplayValues.shown = show;}

        virtual void updateStatus() {m_StatusUpdated = true;}
        virtual void updateTimes() {m_TimesUpdated = true;}

        virtual std::string getHideButtonLabel() const {return m_DisplayValues.hideButtonLabel;}
        virtual std::string getPauseButtonLabel() const {return m_DisplayValues.pauseButtonLabel;}
        virtual std::string getStartButtonLabel() const {return m_DisplayValues.startButtonLabel;}
        virtual std::string getStatus() const {return m_DisplayValues.status;}
        virtual std::string getTimeOn() const {return m_DisplayValues.timeOn;}
        virtual std::string getTimeOff() const {return m_DisplayValues.timeOff;}
        virtual std::string getTimeRunning() const {return m_DisplayValues.timeRunning;}
        virtual std::string getTimeLeft() const {return m_DisplayValues.timeLeft;}
        virtual bool isShown() const {return m_DisplayValues.shown;}
        virtual std::string getIconName()const {return m_DisplayValues.icon;}

        virtual void setRunningLateThreshold(
            boost::posix_time::time_duration val) {m_RunningLateThreshold = val;}
        virtual void setPopupAlarm(bool val) {m_PopupAlarm = val;}
        virtual void setSoundAlarm(bool val) {m_SoundAlarm = val;}
        virtual void setSoundPath(std::string val) {m_SoundPath = val;}

        void notifyStatus() {notify(&TKControllerObserver::OnStatusUpdate);}
        void notifyTime() {notify(&TKControllerObserver::OnTimeUpdate);}
        void notifyQuit() {notify(&TKControllerObserver::OnQuit);}


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
        void setDisplayValues(const DisplayValues& v){m_DisplayValues = v;}

        bool m_PopupAlarm;
        bool m_SoundAlarm;
        std::string m_SoundPath;
        boost::posix_time::time_duration m_RunningLateThreshold;

        bool m_Paused;
        bool m_Started;
        bool m_Quitted;
        bool m_StatusUpdated;
        bool m_TimesUpdated;

        DisplayValues m_DisplayValues;

        AbstractMsgHandler* m_MsgHandler;
        AbstractTimeKeeper* m_Keeper;
        AbstractTimer* m_ClockTimer;
        AbstractTimeHandler* m_TimeHandler;
        AbstractUtils* m_Utils;

    protected:
    private:
};
}

#endif // TKCONTROLLERSTUB_H
