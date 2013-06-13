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


#ifndef EWTASKBARSTUB_H
#define EWTASKBARSTUB_H

#include "AbstractEWTaskbar.h"

class EWTaskbarStub : public AbstractEWTaskbar
{
    public:
        EWTaskbarStub(AbstractEWViewPres<AbstractEWTaskbar>* p = nullptr) : m_HideRestoreLabel(""),
            m_StartStopLabel(""), m_PauseResumeLabel(""), m_OnClock(""),
            m_OffClock(""), m_RunningClock(""), m_LeftClock(""),
            m_Loc(""), m_Presenter(p){}

        EWTaskbarStub(AbstractEWViewPres<AbstractEWTaskbar>& p) : m_HideRestoreLabel(""),
            m_StartStopLabel(""), m_PauseResumeLabel(""), m_OnClock(""),
            m_OffClock(""), m_RunningClock(""), m_LeftClock(""),
            m_Loc(""), m_Presenter(&p){}

        virtual ~EWTaskbarStub() {}

        virtual void setPopupMenuCommands( std::string hrl,
            std::string ssl, std::string prl)
        {
            m_HideRestoreLabel = hrl;
            m_StartStopLabel = ssl;
            m_PauseResumeLabel = prl;
        }

        virtual void setPopupMenuTimes( std::string onc, std::string offc,
            std::string rc, std::string lc)
        {
            m_OnClock = onc;
            m_OffClock = offc;
            m_RunningClock = rc;
            m_LeftClock = lc;
        }

        virtual void setIcon(std::string l)
        {
            m_Loc = l;
        }

        std::string m_HideRestoreLabel;
        std::string m_StartStopLabel;
        std::string m_PauseResumeLabel;
        std::string m_OnClock;
        std::string m_OffClock;
        std::string m_RunningClock;
        std::string m_LeftClock;
        std::string m_Loc;

        AbstractEWViewPres<AbstractEWTaskbar>* m_Presenter;
    protected:
    private:
};


#endif // EWTASKBARSTUB_H
