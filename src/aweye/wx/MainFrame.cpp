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


#include "aweye/AbstractEventHandler.h"
#include "aweye/AbstractUtils.h"
#include "aweye/wx/AboutDialog.h"
#include "aweye/wx/MainFrame.h"
#include "aweye/wx/wx_pch.h"

//(*InternalHeaders(MainFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

namespace Aweye { namespace WX {

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(MainFrame)
const long MainFrame::ID_STATICTEXT9 = wxNewId();
const long MainFrame::ID_STATICLINE1 = wxNewId();
const long MainFrame::ID_STATICTEXT1 = wxNewId();
const long MainFrame::ID_STATICTEXT2 = wxNewId();
const long MainFrame::ID_STATICLINE2 = wxNewId();
const long MainFrame::ID_STATICTEXT3 = wxNewId();
const long MainFrame::ID_STATICTEXT4 = wxNewId();
const long MainFrame::ID_STATICLINE3 = wxNewId();
const long MainFrame::ID_STATICTEXT5 = wxNewId();
const long MainFrame::ID_STATICTEXT6 = wxNewId();
const long MainFrame::ID_STATICLINE4 = wxNewId();
const long MainFrame::ID_STATICTEXT7 = wxNewId();
const long MainFrame::ID_STATICTEXT8 = wxNewId();
const long MainFrame::ID_STARTMENUITEM = wxNewId();
const long MainFrame::ID_PAUSEMENUITEM = wxNewId();
const long MainFrame::ID_OPTIONSMENUITEM = wxNewId();
const long MainFrame::ID_ABOUTMENUITEM = wxNewId();
const long MainFrame::ID_EXITMENUITEM = wxNewId();
//*)

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
    //(*EventTable(MainFrame)
    //*)
END_EVENT_TABLE()

MainFrame::MainFrame(AbstractEventHandler& hdlr, AbstractUtils& utils,
                         bool taskBarCreated, wxWindow* parent, wxWindowID id) :
                         m_EventHandler(hdlr), m_TaskBarCreated(taskBarCreated)
{
    //(*Initialize(MainFrame)
    wxMenuItem* m_ExitMenuItem;
    wxBoxSizer* m_LeftBoxSizer;
    wxMenuItem* m_AboutMenuItem;
    wxMenuItem* m_OptionsMenuItem;
    wxBoxSizer* m_OnBoxSizer;
    wxBoxSizer* m_OffBoxSizer;
    wxBoxSizer* m_RunningBoxSizer;
    wxFlexGridSizer* m_MainFlexGridSizer;
    wxMenuItem* m_PauseMenuItem;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    m_MainFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_StatusLabel = new wxStaticText(this, ID_STATICTEXT9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    m_MainFlexGridSizer->Add(m_StatusLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    m_MainFlexGridSizer->Add(m_StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_OnBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_OnLabel = new wxStaticText(this, ID_STATICTEXT1, _("Last Session"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    m_OnBoxSizer->Add(m_OnLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_OnClock = new wxStaticText(this, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    m_OnBoxSizer->Add(m_OnClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_MainFlexGridSizer->Add(m_OnBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    m_StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    m_MainFlexGridSizer->Add(m_StaticLine2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_OffBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_OffLabel = new wxStaticText(this, ID_STATICTEXT3, _("Last Pause"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    m_OffBoxSizer->Add(m_OffLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_OffClock = new wxStaticText(this, ID_STATICTEXT4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    m_OffBoxSizer->Add(m_OffClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_MainFlexGridSizer->Add(m_OffBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    m_StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    m_MainFlexGridSizer->Add(m_StaticLine3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_RunningBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_RunningLabel = new wxStaticText(this, ID_STATICTEXT5, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    m_RunningBoxSizer->Add(m_RunningLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_RunningClock = new wxStaticText(this, ID_STATICTEXT6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    m_RunningBoxSizer->Add(m_RunningClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_MainFlexGridSizer->Add(m_RunningBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    m_StaticLine4 = new wxStaticLine(this, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    m_MainFlexGridSizer->Add(m_StaticLine4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_LeftBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_LeftLabel = new wxStaticText(this, ID_STATICTEXT7, _("Time Left"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    m_LeftBoxSizer->Add(m_LeftLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_LeftClock = new wxStaticText(this, ID_STATICTEXT8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    m_LeftBoxSizer->Add(m_LeftClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_MainFlexGridSizer->Add(m_LeftBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(m_MainFlexGridSizer);
    m_EwMenuBar = new wxMenuBar();
    m_DoMenu = new wxMenu();
    m_StartMenuItem = new wxMenuItem(m_DoMenu, ID_STARTMENUITEM, _("Start"), wxEmptyString, wxITEM_NORMAL);
    m_DoMenu->Append(m_StartMenuItem);
    m_PauseMenuItem = new wxMenuItem(m_DoMenu, ID_PAUSEMENUITEM, _("Pause"), wxEmptyString, wxITEM_NORMAL);
    m_DoMenu->Append(m_PauseMenuItem);
    m_OptionsMenuItem = new wxMenuItem(m_DoMenu, ID_OPTIONSMENUITEM, _("Options"), wxEmptyString, wxITEM_NORMAL);
    m_DoMenu->Append(m_OptionsMenuItem);
    m_AboutMenuItem = new wxMenuItem(m_DoMenu, ID_ABOUTMENUITEM, _("About"), wxEmptyString, wxITEM_NORMAL);
    m_DoMenu->Append(m_AboutMenuItem);
    m_ExitMenuItem = new wxMenuItem(m_DoMenu, ID_EXITMENUITEM, _("Exit"), wxEmptyString, wxITEM_NORMAL);
    m_DoMenu->Append(m_ExitMenuItem);
    m_EwMenuBar->Append(m_DoMenu, _("Do"));
    SetMenuBar(m_EwMenuBar);
    m_MainFlexGridSizer->Fit(this);
    m_MainFlexGridSizer->SetSizeHints(this);

    Connect(ID_STARTMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrame::OnPlayButtonClick);
    Connect(ID_PAUSEMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrame::OnPauseButtonClick);
    Connect(ID_OPTIONSMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrame::OnOptionsButtonClick);
    Connect(ID_ABOUTMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrame::OnAbout);
    Connect(ID_EXITMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrame::OnQuit);
    //*)

    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&MainFrame::OnClose);

    wxIcon FrameIcon;
    FrameIcon.CopyFromBitmap(wxBitmap(wxImage(utils.getDataPath("icons/webcam.ico"))));
    SetIcon(FrameIcon);
}

MainFrame::~MainFrame()
{
    //(*Destroy(MainFrame)
    //*)
}

void MainFrame::setValues( std::string statusLabel, std::string onClockLabel,
                            std::string offClockLabel, std::string runningClockLabel,
                            std::string leftClockLabel)
{
    m_StatusLabel->SetLabel(wxString(statusLabel.c_str(), wxConvUTF8));
    m_OnClock->SetLabel(wxString(onClockLabel.c_str(), wxConvUTF8));
    m_OffClock->SetLabel(wxString(offClockLabel.c_str(), wxConvUTF8));
    m_RunningClock->SetLabel(wxString(runningClockLabel.c_str(), wxConvUTF8));
    m_LeftClock->SetLabel(wxString(leftClockLabel.c_str(), wxConvUTF8));

    m_StatusLabel->GetParent()->Layout();
    m_OnClock->GetParent()->Layout();
    m_OffClock->GetParent()->Layout();
    m_RunningClock->GetParent()->Layout();
    m_LeftClock->GetParent()->Layout();
}

void MainFrame::show(bool show)
{
    Show(show);
}

void MainFrame::setPauseButtonLabel(std::string label)
{
    m_DoMenu->SetLabel(ID_PAUSEMENUITEM, wxString(label.c_str(), wxConvUTF8));
}

void MainFrame::setStartButtonLabel(std::string label)
{
    m_DoMenu->SetLabel(ID_STARTMENUITEM, wxString(label.c_str(), wxConvUTF8));
}

void MainFrame::close()
{
    Destroy();
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
    m_EventHandler.OnViewQuit();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    AboutDialog dialog(this);
    dialog.ShowModal();
}

void MainFrame::OnOptionsButtonClick(wxCommandEvent& event)
{
    m_EventHandler.OnViewOptionsButtonClick();
}

void MainFrame::OnPlayButtonClick(wxCommandEvent& event)
{
    m_EventHandler.OnViewStartStop();
}

void MainFrame::OnClose(wxCloseEvent& event)
{
    if (!event.CanVeto() || !m_TaskBarCreated)
    {
        m_EventHandler.OnViewQuit();
        Destroy();
    }
    event.Veto();
    m_EventHandler.OnViewHideRestore();
}

void MainFrame::OnPauseButtonClick(wxCommandEvent& event)
{
    m_EventHandler.OnViewPauseResume();
}
}}
