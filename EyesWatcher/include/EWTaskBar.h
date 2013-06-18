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


#ifndef EWTASKBAR_H
#define EWTASKBAR_H

#include <wx/taskbar.h>
#include <string>
#include "AbstractEWTaskbar.h"
#include "ObservableWxMenu.h"
#include <map>

class AbstractEventHandler;
class wxMenu;
class EWTaskBar : public AbstractEWTaskbar, public wxTaskBarIcon, public ObservableWxMenuObserver
{
    public:
        EWTaskBar(AbstractEventHandler& hdlr);
        virtual ~EWTaskBar();
        virtual void setPopupMenuCommands( std::string hideRestoreLabel,
            std::string startStopLabel, std::string pauseResumeLabel);
        virtual void setPopupMenuTimes( std::string onClock, std::string offClock,
            std::string runningClock, std::string leftClock);
        virtual void setIcon(std::string loc);

        virtual void onMenuDelete(ObservableWxMenu* menu);
    protected:
    private:
        void OnMenuHideRestore(wxCommandEvent&);
        void OnMenuStartStop(wxCommandEvent&);
        void OnMenuPauseResume(wxCommandEvent&);
        void OnMenuExit(wxCommandEvent&);

        virtual wxMenu* CreatePopupMenu();

        AbstractEventHandler& m_EventHandler;
        ObservableWxMenu* m_Menu;

        enum Menu_IDS
        {
            ID_HIDE_RESTORE,
            ID_START_STOP,
            ID_PAUSE_RESUME,
            ID_EXIT,
            ID_ON_TIME,
            ID_OFF_TIME,
            ID_RUNNING_TIME,
            ID_LEFT_TIME,
            ID_MAX
        };

        DECLARE_EVENT_TABLE()
};

#endif // EWTASKBAR_H
