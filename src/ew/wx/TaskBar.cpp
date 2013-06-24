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


#include "ew/AbstractEventHandler.h"
#include "ew/wx/ObservableMenu.h"
#include "ew/wx/TaskBar.h"
#include "ew/wx/wx_pch.h"

#include <wx/menu.h>

namespace EW { namespace WX {

BEGIN_EVENT_TABLE(TaskBar,wxTaskBarIcon)
    EVT_MENU(ID_HIDE_RESTORE, TaskBar::OnMenuHideRestore)
    EVT_MENU(ID_START_STOP, TaskBar::OnMenuStartStop)
    EVT_MENU(ID_PAUSE_RESUME,TaskBar::OnMenuPauseResume)
    EVT_MENU(ID_EXIT,TaskBar::OnMenuExit)
END_EVENT_TABLE()

TaskBar::TaskBar(AbstractEventHandler& hdlr) :
    m_EventHandler(hdlr), m_Menu(nullptr)
{
}

TaskBar::~TaskBar()
{
    if (m_Menu != nullptr)
    {
        delete m_Menu;
    }
    RemoveIcon();
}

void TaskBar::setPopupMenuCommands( std::string hideRestoreLabel,
    std::string startStopLabel, std::string pauseResumeLabel)
{
    if (m_Menu != nullptr)
    {
        m_Menu->FindItem(TaskBar::ID_HIDE_RESTORE)->SetItemLabel(wxString(hideRestoreLabel.c_str(), wxConvUTF8));
        m_Menu->FindItem(TaskBar::ID_START_STOP)->SetItemLabel(wxString(startStopLabel.c_str(), wxConvUTF8));
        m_Menu->FindItem(TaskBar::ID_PAUSE_RESUME)->SetItemLabel(wxString(pauseResumeLabel.c_str(), wxConvUTF8));
    }
}

void TaskBar::setPopupMenuTimes( std::string onClock, std::string offClock,
    std::string runningClock, std::string leftClock)
{
    if (m_Menu != nullptr)
    {
        m_Menu->FindItem(TaskBar::ID_ON_TIME)->SetItemLabel(wxString(onClock.c_str(), wxConvUTF8));
        m_Menu->FindItem(TaskBar::ID_OFF_TIME)->SetItemLabel(wxString(offClock.c_str(), wxConvUTF8));
        m_Menu->FindItem(TaskBar::ID_RUNNING_TIME)->SetItemLabel(wxString(runningClock.c_str(), wxConvUTF8));
        m_Menu->FindItem(TaskBar::ID_LEFT_TIME)->SetItemLabel(wxString(leftClock.c_str(), wxConvUTF8));
    }
}

wxMenu* TaskBar::CreatePopupMenu()
{
    // is this necessary? Investigate.
    if (m_Menu != nullptr)
    {
        delete m_Menu;
    }
    m_Menu = new ObservableMenu();
    m_Menu->attach(this);
    m_Menu->Append(TaskBar::ID_HIDE_RESTORE, _("Hide/Restore"));
    m_Menu->Append(TaskBar::ID_EXIT, _("Exit"));
    m_Menu->AppendSeparator();
    m_Menu->Append(TaskBar::ID_START_STOP, _("Start/Stop"));
    m_Menu->Append(TaskBar::ID_PAUSE_RESUME, _("Pause/Resume"));
    m_Menu->AppendSeparator();
    m_Menu->Append(TaskBar::ID_ON_TIME, _("Last Session"));
    m_Menu->Append(TaskBar::ID_OFF_TIME, _("Last Pause"));
    m_Menu->Append(TaskBar::ID_RUNNING_TIME, _("Running"));
    m_Menu->Append(TaskBar::ID_LEFT_TIME, _("Time Left"));

    m_EventHandler.forceUpdate();
    return m_Menu;
}

// all icons are png files for now...
void TaskBar::setIcon(std::string loc)
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
void TaskBar::onMenuDelete(ObservableMenu* menu)
{
    m_Menu = nullptr;
}

void TaskBar::OnMenuHideRestore(wxCommandEvent&)
{
    m_EventHandler.OnViewHideRestore();
}

void TaskBar::OnMenuStartStop(wxCommandEvent&)
{
    m_EventHandler.OnViewStartStop();
}

void TaskBar::OnMenuPauseResume(wxCommandEvent&)
{
    m_EventHandler.OnViewPauseResume();
}

void TaskBar::OnMenuExit(wxCommandEvent&)
{
    m_EventHandler.OnViewQuit();
}
}}
