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


#include "wx_pch.h"
#include "EWMainFrame.h"
#include "OptionsDialog.h"
#include "AboutDialog.h"
#include <wx/msgdlg.h>
#include <wx/valgen.h>
#include <wx/utils.h>
#include <wx/notifmsg.h>
#include "BaseException.h"
#include "EWMainFramePres.h"
#include "EWPresenter.h"

//(*InternalHeaders(EWMainFrame)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
//*)

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

//(*IdInit(EWMainFrame)
const long EWMainFrame::ID_STATICTEXT9 = wxNewId();
const long EWMainFrame::ID_STATICLINE1 = wxNewId();
const long EWMainFrame::ID_STATICTEXT1 = wxNewId();
const long EWMainFrame::ID_STATICTEXT2 = wxNewId();
const long EWMainFrame::ID_STATICLINE2 = wxNewId();
const long EWMainFrame::ID_STATICTEXT3 = wxNewId();
const long EWMainFrame::ID_STATICTEXT4 = wxNewId();
const long EWMainFrame::ID_STATICLINE3 = wxNewId();
const long EWMainFrame::ID_STATICTEXT5 = wxNewId();
const long EWMainFrame::ID_STATICTEXT6 = wxNewId();
const long EWMainFrame::ID_STATICLINE4 = wxNewId();
const long EWMainFrame::ID_STATICTEXT7 = wxNewId();
const long EWMainFrame::ID_STATICTEXT8 = wxNewId();
const long EWMainFrame::ID_STARTMENUITEM = wxNewId();
const long EWMainFrame::ID_PAUSEMENUITEM = wxNewId();
const long EWMainFrame::ID_OPTIONSMENUITEM = wxNewId();
const long EWMainFrame::ID_ABOUTMENUITEM = wxNewId();
const long EWMainFrame::ID_EXITMENUITEM = wxNewId();
//*)

BEGIN_EVENT_TABLE(EWMainFrame,wxFrame)
    //(*EventTable(EWMainFrame)
    //*)
END_EVENT_TABLE()

EWMainFrame::EWMainFrame(AbstractEWViewPres<AbstractEWMainFrame>* presenter,
                         bool taskbarCreated, wxWindow* parent, wxWindowID id) :
                         m_Presenter(presenter), m_TaskbarCreated(taskbarCreated)
{
    assert(presenter);
    //(*Initialize(EWMainFrame)
    wxMenuItem* AboutMenuItem;
    wxBoxSizer* offBoxSizer;
    wxMenuItem* OptionsMenuItem;
    wxMenuItem* PauseMenuItem;
    wxMenuItem* ExitMenuItem;
    wxBoxSizer* runningBoxSizer;
    wxFlexGridSizer* mainFlexGridSizer;
    wxBoxSizer* onBoxSizer;
    wxBoxSizer* leftBoxSizer;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("webcam.ico"))));
    	SetIcon(FrameIcon);
    }
    mainFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
    StatusLabel = new wxStaticText(this, ID_STATICTEXT9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    mainFlexGridSizer->Add(StatusLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    mainFlexGridSizer->Add(StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    onBoxSizer = new wxBoxSizer(wxVERTICAL);
    onLabel = new wxStaticText(this, ID_STATICTEXT1, _("Last Session"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    onBoxSizer->Add(onLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    onClock = new wxStaticText(this, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    onBoxSizer->Add(onClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    mainFlexGridSizer->Add(onBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    mainFlexGridSizer->Add(StaticLine2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    offBoxSizer = new wxBoxSizer(wxVERTICAL);
    offLabel = new wxStaticText(this, ID_STATICTEXT3, _("Last Pause"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    offBoxSizer->Add(offLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    offClock = new wxStaticText(this, ID_STATICTEXT4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    offBoxSizer->Add(offClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    mainFlexGridSizer->Add(offBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    mainFlexGridSizer->Add(StaticLine3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    runningBoxSizer = new wxBoxSizer(wxVERTICAL);
    runningLabel = new wxStaticText(this, ID_STATICTEXT5, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    runningBoxSizer->Add(runningLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    runningClock = new wxStaticText(this, ID_STATICTEXT6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    runningBoxSizer->Add(runningClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    mainFlexGridSizer->Add(runningBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticLine4 = new wxStaticLine(this, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    mainFlexGridSizer->Add(StaticLine4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    leftBoxSizer = new wxBoxSizer(wxVERTICAL);
    leftLabel = new wxStaticText(this, ID_STATICTEXT7, _("Time Left"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    leftBoxSizer->Add(leftLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    leftClock = new wxStaticText(this, ID_STATICTEXT8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    leftBoxSizer->Add(leftClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    mainFlexGridSizer->Add(leftBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(mainFlexGridSizer);
    EwMenuBar = new wxMenuBar();
    DoMenu = new wxMenu();
    StartMenuItem = new wxMenuItem(DoMenu, ID_STARTMENUITEM, _("Start"), wxEmptyString, wxITEM_NORMAL);
    DoMenu->Append(StartMenuItem);
    PauseMenuItem = new wxMenuItem(DoMenu, ID_PAUSEMENUITEM, _("Pause"), wxEmptyString, wxITEM_NORMAL);
    DoMenu->Append(PauseMenuItem);
    OptionsMenuItem = new wxMenuItem(DoMenu, ID_OPTIONSMENUITEM, _("Options"), wxEmptyString, wxITEM_NORMAL);
    DoMenu->Append(OptionsMenuItem);
    AboutMenuItem = new wxMenuItem(DoMenu, ID_ABOUTMENUITEM, _("About"), wxEmptyString, wxITEM_NORMAL);
    DoMenu->Append(AboutMenuItem);
    ExitMenuItem = new wxMenuItem(DoMenu, ID_EXITMENUITEM, _("Exit"), wxEmptyString, wxITEM_NORMAL);
    DoMenu->Append(ExitMenuItem);
    EwMenuBar->Append(DoMenu, _("Do"));
    SetMenuBar(EwMenuBar);
    mainFlexGridSizer->Fit(this);
    mainFlexGridSizer->SetSizeHints(this);

    Connect(ID_STARTMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EWMainFrame::OnPlayButtonClick);
    Connect(ID_PAUSEMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EWMainFrame::OnPauseButtonClick);
    Connect(ID_OPTIONSMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EWMainFrame::OnOptionsButtonClick);
    Connect(ID_ABOUTMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EWMainFrame::OnAbout);
    Connect(ID_EXITMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EWMainFrame::OnQuit);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&EWMainFrame::OnClose);
    //*)

    m_Presenter->attachView(this);
}

EWMainFrame::~EWMainFrame()
{
    //(*Destroy(EWMainFrame)
    //*)
}

void EWMainFrame::setValues( std::string status, std::string onClock,
                            std::string offClock, std::string runningClock,
                            std::string leftClock)
{
    this->StatusLabel->SetLabel(wxString(status.c_str(), wxConvUTF8));
    this->onClock->SetLabel(wxString(onClock.c_str(), wxConvUTF8));
    this->offClock->SetLabel(wxString(offClock.c_str(), wxConvUTF8));
    this->runningClock->SetLabel(wxString(runningClock.c_str(), wxConvUTF8));
    this->leftClock->SetLabel(wxString(leftClock.c_str(), wxConvUTF8));

    this->StatusLabel->GetParent()->Layout();
    this->onClock->GetParent()->Layout();
    this->offClock->GetParent()->Layout();
    this->runningClock->GetParent()->Layout();
    this->leftClock->GetParent()->Layout();
}

void EWMainFrame::show(bool show)
{
    Show(show);
}

void EWMainFrame::setPauseButtonLabel(std::string label)
{
    this->DoMenu->SetLabel(this->ID_PAUSEMENUITEM, wxString(label.c_str(), wxConvUTF8));
}

void EWMainFrame::setStartButtonLabel(std::string label)
{
    this->DoMenu->SetLabel(this->ID_STARTMENUITEM, wxString(label.c_str(), wxConvUTF8));
}

void EWMainFrame::close()
{
    Destroy();
}

void EWMainFrame::OnQuit(wxCommandEvent& event)
{
    this->m_Presenter->OnViewQuit();
}

void EWMainFrame::OnAbout(wxCommandEvent& event)
{
    AboutDialog dialog(this);
    dialog.ShowModal();
}

void EWMainFrame::OnOptionsButtonClick(wxCommandEvent& event)
{
    this->m_Presenter->OnViewOptionsButtonClick();
}

void EWMainFrame::OnPlayButtonClick(wxCommandEvent& event)
{
    this->m_Presenter->OnViewStartStop();
}

void EWMainFrame::OnClose(wxCloseEvent& event)
{
    if (!event.CanVeto() || !this->m_TaskbarCreated)
    {
        this->m_Presenter->OnViewQuit();
        Destroy();
    }
    event.Veto();
    this->m_Presenter->OnViewHideRestore();
}

void EWMainFrame::OnPauseButtonClick(wxCommandEvent& event)
{
    this->m_Presenter->OnViewPauseResume();
}
