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

#include "AbstractEventHandler.h"
#include "EWTaskBar.h"
#include "ObservableWxMenu.h"

#include "wx_pch.h"
#include <wx/menu.h>

BEGIN_EVENT_TABLE(EWTaskBar,wxTaskBarIcon)
    EVT_MENU(ID_HIDE_RESTORE, EWTaskBar::OnMenuHideRestore)
    EVT_MENU(ID_START_STOP, EWTaskBar::OnMenuStartStop)
    EVT_MENU(ID_PAUSE_RESUME,EWTaskBar::OnMenuPauseResume)
    EVT_MENU(ID_EXIT,EWTaskBar::OnMenuExit)
END_EVENT_TABLE()

EWTaskBar::EWTaskBar(AbstractEventHandler& hdlr) :
    m_EventHandler(hdlr), m_Menu(nullptr)
{
}

EWTaskBar::~EWTaskBar()
{
    if (m_Menu != nullptr)
    {
        delete m_Menu;
    }
    RemoveIcon();
}

void EWTaskBar::setPopupMenuCommands( std::string hideRestoreLabel,
    std::string startStopLabel, std::string pauseResumeLabel)
{
    if (m_Menu != nullptr)
    {
        m_Menu->FindItem(EWTaskBar::ID_HIDE_RESTORE)->SetItemLabel(wxString(hideRestoreLabel.c_str(), wxConvUTF8));
        m_Menu->FindItem(EWTaskBar::ID_START_STOP)->SetItemLabel(wxString(startStopLabel.c_str(), wxConvUTF8));
        m_Menu->FindItem(EWTaskBar::ID_PAUSE_RESUME)->SetItemLabel(wxString(pauseResumeLabel.c_str(), wxConvUTF8));
    }
}

void EWTaskBar::setPopupMenuTimes( std::string onClock, std::string offClock,
    std::string runningClock, std::string leftClock)
{
    if (m_Menu != nullptr)
    {
        m_Menu->FindItem(EWTaskBar::ID_ON_TIME)->SetItemLabel(wxString(onClock.c_str(), wxConvUTF8));
        m_Menu->FindItem(EWTaskBar::ID_OFF_TIME)->SetItemLabel(wxString(offClock.c_str(), wxConvUTF8));
        m_Menu->FindItem(EWTaskBar::ID_RUNNING_TIME)->SetItemLabel(wxString(runningClock.c_str(), wxConvUTF8));
        m_Menu->FindItem(EWTaskBar::ID_LEFT_TIME)->SetItemLabel(wxString(leftClock.c_str(), wxConvUTF8));
    }
}

wxMenu* EWTaskBar::CreatePopupMenu()
{
    // is this necessary? Investigate.
    if (m_Menu != nullptr)
    {
        delete m_Menu;
    }
    m_Menu = new ObservableWxMenu();
    m_Menu->attach(this);
    m_Menu->Append(EWTaskBar::ID_HIDE_RESTORE, wxT("Hide/Restore"));
    m_Menu->Append(EWTaskBar::ID_EXIT, wxT("Exit"));
    m_Menu->AppendSeparator();
    m_Menu->Append(EWTaskBar::ID_START_STOP, wxT("Start/Stop"));
    m_Menu->Append(EWTaskBar::ID_PAUSE_RESUME, wxT("Pause/Resume"));
    m_Menu->AppendSeparator();
    m_Menu->Append(EWTaskBar::ID_ON_TIME, wxT("Last Session"));
    m_Menu->Append(EWTaskBar::ID_OFF_TIME, wxT("Last Pause"));
    m_Menu->Append(EWTaskBar::ID_RUNNING_TIME, wxT("Running"));
    m_Menu->Append(EWTaskBar::ID_LEFT_TIME, wxT("Time Left"));

    m_EventHandler.forceUpdate();
    return m_Menu;
}

// all icons are png files for now...
void EWTaskBar::setIcon(std::string loc)
{
    if (loc != "")
    {
        const wxIcon icon(wxString(loc.c_str(), wxConvUTF8), wxBITMAP_TYPE_PNG );
        SetIcon(icon);
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
    m_Menu = nullptr;
}

void EWTaskBar::OnMenuHideRestore(wxCommandEvent&)
{
    m_EventHandler.OnViewHideRestore();
}

void EWTaskBar::OnMenuStartStop(wxCommandEvent&)
{
    m_EventHandler.OnViewStartStop();
}

void EWTaskBar::OnMenuPauseResume(wxCommandEvent&)
{
    m_EventHandler.OnViewPauseResume();
}

void EWTaskBar::OnMenuExit(wxCommandEvent&)
{
    m_EventHandler.OnViewQuit();
}
