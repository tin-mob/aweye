/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "EWTaskBar.h"
#include "AbstractEWViewPres.h"
#include "wx_pch.h"
#include <wx/menu.h>
#include "ObservableWxMenu.h"

BEGIN_EVENT_TABLE(EWTaskBar,wxTaskBarIcon)
    EVT_MENU(ID_HIDE_RESTORE, EWTaskBar::OnMenuHideRestore)
    EVT_MENU(ID_START_STOP, EWTaskBar::OnMenuStartStop)
    EVT_MENU(ID_PAUSE_RESUME,EWTaskBar::OnMenuPauseResume)
    EVT_MENU(ID_EXIT,EWTaskBar::OnMenuExit)
END_EVENT_TABLE()

EWTaskBar::EWTaskBar(AbstractEWViewPres<AbstractEWTaskbar>* presenter) :
    m_Presenter(presenter), m_Menu(nullptr)
{
    assert(presenter);
    m_Presenter->attachView(this);
}

EWTaskBar::~EWTaskBar()
{
    if (this->m_Menu != nullptr)
    {
        delete this->m_Menu;
    }
    this->RemoveIcon();
}

void EWTaskBar::setPopupMenuCommands( std::string hideRestoreLabel,
    std::string startStopLabel, std::string pauseResumeLabel)
{
    if (this->m_Menu != nullptr)
    {
        this->m_Menu->FindItem(EWTaskBar::ID_HIDE_RESTORE)->SetItemLabel(wxString(hideRestoreLabel.c_str(), wxConvUTF8));
        this->m_Menu->FindItem(EWTaskBar::ID_START_STOP)->SetItemLabel(wxString(startStopLabel.c_str(), wxConvUTF8));
        this->m_Menu->FindItem(EWTaskBar::ID_PAUSE_RESUME)->SetItemLabel(wxString(pauseResumeLabel.c_str(), wxConvUTF8));
    }
}

void EWTaskBar::setPopupMenuTimes( std::string onClock, std::string offClock,
    std::string runningClock, std::string leftClock)
{
    if (this->m_Menu != nullptr)
    {
        this->m_Menu->FindItem(EWTaskBar::ID_ON_TIME)->SetItemLabel(wxString(onClock.c_str(), wxConvUTF8));
        this->m_Menu->FindItem(EWTaskBar::ID_OFF_TIME)->SetItemLabel(wxString(offClock.c_str(), wxConvUTF8));
        this->m_Menu->FindItem(EWTaskBar::ID_RUNNING_TIME)->SetItemLabel(wxString(runningClock.c_str(), wxConvUTF8));
        this->m_Menu->FindItem(EWTaskBar::ID_LEFT_TIME)->SetItemLabel(wxString(leftClock.c_str(), wxConvUTF8));
    }
}

wxMenu* EWTaskBar::CreatePopupMenu()
{
    // is this necessary? Investigate.
    if (this->m_Menu != nullptr)
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
    this->m_Presenter->forceUpdate();

    return this->m_Menu;
}

// all icons are png files for now...
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
void EWTaskBar::onMenuDelete(ObservableWxMenu* menu)
{
    this->m_Menu = nullptr;
}

void EWTaskBar::OnMenuHideRestore(wxCommandEvent&)
{
    this->m_Presenter->OnViewHideRestore();
}

void EWTaskBar::OnMenuStartStop(wxCommandEvent&)
{
    this->m_Presenter->OnViewStartStop();
}

void EWTaskBar::OnMenuPauseResume(wxCommandEvent&)
{
    this->m_Presenter->OnViewPauseResume();
}

void EWTaskBar::OnMenuExit(wxCommandEvent&)
{
    this->m_Presenter->OnViewQuit();
}
