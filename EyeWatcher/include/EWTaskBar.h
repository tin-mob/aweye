#ifndef EWTASKBAR_H
#define EWTASKBAR_H

#include <wx/taskbar.h>
#include <string>
#include "AbstractEWTaskbar.h"

class wxMenu;
class EWTaskBarPres;
class ObservableWxMenu;
class EWTaskBar : public AbstractEWTaskbar, public wxTaskBarIcon
{
    public:
        EWTaskBar(EWTaskBarPres* presenter);
        virtual ~EWTaskBar();
        virtual void setPopupMenuCommands( std::string hideRestoreLabel,
            std::string startStopLabel, std::string pauseResumeLabel);
        virtual void setPopupMenuTimes( std::string onClock, std::string offClock,
            std::string runningClock, std::string leftClock);
        virtual void setIcon(std::string loc);

        virtual void update(Observable*);
    protected:
    private:
        void OnMenuHideRestore(wxCommandEvent&);
        void OnMenuStartStop(wxCommandEvent&);
        void OnMenuPauseResume(wxCommandEvent&);
        void OnMenuExit(wxCommandEvent&);

        virtual wxMenu* CreatePopupMenu();

        EWTaskBarPres* m_Presenter;
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
