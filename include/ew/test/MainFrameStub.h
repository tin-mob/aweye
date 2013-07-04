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


#ifndef MAINFRAMESTUB_H
#define MAINFRAMESTUB_H

#include "ew/AbstractMainFrame.h"

namespace EW
{
class AbstractEventHandler;
class AbstractUtils;
class MainFrameStub : public AbstractMainFrame
{
    public:
        MainFrameStub(AbstractEventHandler* hdlr = nullptr, AbstractUtils* utils = nullptr,
            bool tc = true) :
            m_Closed(false), m_Shown(false), m_Status(""),
            m_OnClock(""), m_OffClock(""), m_RunningClock(""), m_LeftClock(""),
            m_PauseLabel(""), m_StartLabel(""), m_EventHandler(hdlr),
            m_Utils(utils), m_TaskBarCreated(tc) {}

        MainFrameStub(AbstractEventHandler& hdlr, AbstractUtils& utils,
            bool tc = true) :
            m_Closed(false), m_Shown(false), m_Status(""),
            m_OnClock(""), m_OffClock(""), m_RunningClock(""), m_LeftClock(""),
            m_PauseLabel(""), m_StartLabel(""), m_EventHandler(&hdlr),
            m_Utils(&utils), m_TaskBarCreated(tc) {}

        virtual ~MainFrameStub() {}

        virtual void setValues( std::string s, std::string onC,
                               std::string offC, std::string r,
                               std::string l)
        {
            m_Status = s;
            m_OnClock = onC;
            m_OffClock = offC;
            m_RunningClock = r;
            m_LeftClock = l;
        }

        virtual void show(bool show = true) {m_Shown = show;}

        bool m_Closed;
        bool m_Shown;
        std::string m_Status;
        std::string m_OnClock;
        std::string m_OffClock;
        std::string m_RunningClock;
        std::string m_LeftClock;
        std::string m_PauseLabel;
        std::string m_StartLabel;

        AbstractEventHandler* m_EventHandler;
        AbstractUtils* m_Utils;
        bool m_TaskBarCreated;

        virtual void setPauseButtonLabel(std::string label) {m_PauseLabel = label;}
        virtual void setStartButtonLabel(std::string label) {m_StartLabel = label;}
        virtual void close() {m_Closed = true;}

    protected:
    private:
};
}

#endif // MAINFRAMESTUB_H
