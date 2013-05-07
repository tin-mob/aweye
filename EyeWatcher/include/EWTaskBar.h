#ifndef EWTASKBAR_H
#define EWTASKBAR_H

#include <wx/taskbar.h>
#include <string>
#include "AbstractEWTaskbar.h"

class wxMenu;
class EWPresenter;
class EWTaskBar : public AbstractEWTaskbar, public wxTaskBarIcon
{
    public:
        EWTaskBar(EWPresenter* presenter, std::string iconLoc);
        virtual ~EWTaskBar();
        virtual void setPopupMenu( bool running, bool snoozed,
            std::string onClock, std::string offClock,
            std::string runningClock, std::string leftClock);
        virtual void reloadIcon();
        virtual void update(Observable*);
    protected:
    private:
        void OnMenuRestore(wxCommandEvent&);
        void OnMenuStart(wxCommandEvent&);
        void OnMenuStop(wxCommandEvent&);
        void OnMenuPause(wxCommandEvent&);
        void OnMenuResume(wxCommandEvent&);
        void OnMenuExit(wxCommandEvent&);

        EWPresenter* m_Presenter;
        std::string m_IconLoc;
        wxMenu* m_Menu;

        enum Menu_IDS
        {
            ID_RESTORE,
            ID_START,
            ID_STOP,
            ID_PAUSE,
            ID_RESUME,
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
