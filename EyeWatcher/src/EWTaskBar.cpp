#include "EWTaskBar.h"

#include "EWTaskBarPres.h"
#include "wx_pch.h"
#include <wx/menu.h>
#include "ObservableWxMenu.h"

BEGIN_EVENT_TABLE(EWTaskBar,wxTaskBarIcon)
    EVT_MENU(ID_HIDE_RESTORE, EWTaskBar::OnMenuHideRestore)
    EVT_MENU(ID_START_STOP, EWTaskBar::OnMenuStartStop)
    EVT_MENU(ID_PAUSE_RESUME,EWTaskBar::OnMenuPauseResume)
    EVT_MENU(ID_EXIT,EWTaskBar::OnMenuExit)
END_EVENT_TABLE()

EWTaskBar::EWTaskBar(EWTaskBarPres* presenter) :
    m_Presenter(presenter), m_Menu(NULL)
{
    //ctor
    m_Presenter->attachTaskBar(this);
}

EWTaskBar::~EWTaskBar()
{
    //dtor
    if (this->m_Menu != NULL)
    {
        delete this->m_Menu;
    }
    this->RemoveIcon();
}

void EWTaskBar::setPopupMenuCommands( std::string hideRestoreLabel,
    std::string startStopLabel, std::string pauseResumeLabel)
{
    if (this->m_Menu == NULL)
    {
        return;
    }
    this->m_Menu->FindItem(EWTaskBar::ID_HIDE_RESTORE)->SetItemLabel(wxString(hideRestoreLabel.c_str(), wxConvUTF8));
    this->m_Menu->FindItem(EWTaskBar::ID_START_STOP)->SetItemLabel(wxString(startStopLabel.c_str(), wxConvUTF8));
    this->m_Menu->FindItem(EWTaskBar::ID_PAUSE_RESUME)->SetItemLabel(wxString(pauseResumeLabel.c_str(), wxConvUTF8));
}

void EWTaskBar::setPopupMenuTimes( std::string onClock, std::string offClock,
    std::string runningClock, std::string leftClock)
{
    if (this->m_Menu == NULL)
    {
        return;
    }
    this->m_Menu->FindItem(EWTaskBar::ID_ON_TIME)->SetItemLabel(wxString(onClock.c_str(), wxConvUTF8));
    this->m_Menu->FindItem(EWTaskBar::ID_OFF_TIME)->SetItemLabel(wxString(offClock.c_str(), wxConvUTF8));
    this->m_Menu->FindItem(EWTaskBar::ID_RUNNING_TIME)->SetItemLabel(wxString(runningClock.c_str(), wxConvUTF8));
    this->m_Menu->FindItem(EWTaskBar::ID_LEFT_TIME)->SetItemLabel(wxString(leftClock.c_str(), wxConvUTF8));
}

wxMenu* EWTaskBar::CreatePopupMenu()
{
    // is this necessary? Investigate.
    if (this->m_Menu != NULL)
    {
        delete this->m_Menu;
    }
    this->m_Menu = new ObservableWxMenu();
    this->m_Menu->attach(this);
    this->m_Menu->Append(EWTaskBar::ID_HIDE_RESTORE, wxT("Hide/Restore"));
    this->m_Menu->Append(EWTaskBar::ID_EXIT, wxT("Exit"));
    this->m_Menu->AppendSeparator();
    this->m_Menu->Append(EWTaskBar::ID_START_STOP, wxT("Start/Stop"));
    this->m_Menu->Append(EWTaskBar::ID_PAUSE_RESUME, wxT("Pause/Resume"));
    this->m_Menu->AppendSeparator();
    this->m_Menu->Append(EWTaskBar::ID_ON_TIME, wxT("Last Session"));
    this->m_Menu->Append(EWTaskBar::ID_OFF_TIME, wxT("Last Pause"));
    this->m_Menu->Append(EWTaskBar::ID_RUNNING_TIME, wxT("Running"));
    this->m_Menu->Append(EWTaskBar::ID_LEFT_TIME, wxT("Time Left"));

    // force update
    this->m_Presenter->OnStatusUpdate();
    this->m_Presenter->OnTimeUpdate();

    return this->m_Menu;
}

// all icons are png files for now...
///@todo: load icons so that we don't have to create them again...
void EWTaskBar::setIcon(std::string loc)
{
    if (loc != "")
    {
        wxIcon icon(wxString(loc.c_str(), wxConvUTF8), wxBITMAP_TYPE_PNG );
        this->SetIcon(icon);
    }
    else
    {
        RemoveIcon();
    }

}

// the menu is managed by Wx. When It decides to delete it, we receive
// a nice warning...
void EWTaskBar::update(Observable*)
{
    this->m_Menu = NULL;
}

void EWTaskBar::OnMenuHideRestore(wxCommandEvent&)
{
    this->m_Presenter->OnMenuHideRestore();
}

void EWTaskBar::OnMenuStartStop(wxCommandEvent&)
{
    this->m_Presenter->OnMenuStartStop();
}

void EWTaskBar::OnMenuPauseResume(wxCommandEvent&)
{
    this->m_Presenter->OnMenuPauseResume();
}

void EWTaskBar::OnMenuExit(wxCommandEvent&)
{
    this->m_Presenter->OnMenuExit();
}
