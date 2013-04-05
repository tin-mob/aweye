/***************************************************************
 * Name:      EWMainFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Robert Morin ()
 * Created:   2013-01-06
 * Copyright: Robert Morin ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "EWMainFrame.h"
#include "OptionsDialog.h"
#include "AboutDialog.h"
#include <wx/msgdlg.h>
#include <wx/valgen.h>
#include "BaseException.h"
#include "wxTimerHandler.h"

//(*InternalHeaders(EWMainFrame)
#include <wx/string.h>
#include <wx/intl.h>
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
const long EWMainFrame::ID_BUTTON1 = wxNewId();
const long EWMainFrame::ID_BUTTON2 = wxNewId();
const long EWMainFrame::ID_BUTTON3 = wxNewId();
const long EWMainFrame::ID_BUTTON4 = wxNewId();
const long EWMainFrame::ID_BUTTON5 = wxNewId();
const long EWMainFrame::ID_STATICTEXT9 = wxNewId();
const long EWMainFrame::ID_STATICTEXT1 = wxNewId();
const long EWMainFrame::ID_STATICTEXT2 = wxNewId();
const long EWMainFrame::ID_STATICTEXT3 = wxNewId();
const long EWMainFrame::ID_STATICTEXT4 = wxNewId();
const long EWMainFrame::ID_STATICTEXT5 = wxNewId();
const long EWMainFrame::ID_STATICTEXT6 = wxNewId();
const long EWMainFrame::ID_STATICTEXT7 = wxNewId();
const long EWMainFrame::ID_STATICTEXT8 = wxNewId();
const long EWMainFrame::ID_TIMER1 = wxNewId();
const long EWMainFrame::ID_TIMER2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EWMainFrame,wxFrame)
    //(*EventTable(EWMainFrame)
    //*)
END_EVENT_TABLE()

EWMainFrame::EWMainFrame(wxWindow* parent, EWLogic* logic, wxWindowID id) : m_Logic(logic)
{
    //(*Initialize(EWMainFrame)
    wxBoxSizer* buttonsBoxSizer;
    wxBoxSizer* offBoxSizer;
    wxBoxSizer* mainBoxSizer;
    wxGridSizer* timesGrid;
    wxBoxSizer* runningBoxSizer;
    wxBoxSizer* onBoxSizer;
    wxBoxSizer* leftBoxSizer;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    mainBoxSizer = new wxBoxSizer(wxVERTICAL);
    buttonsBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    pauseButton = new wxButton(this, ID_BUTTON1, _("Pause"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    pauseButton->SetMinSize(wxSize(-1,-1));
    buttonsBoxSizer->Add(pauseButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    stopButton = new wxButton(this, ID_BUTTON2, _("Stop"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    buttonsBoxSizer->Add(stopButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    playButton = new wxButton(this, ID_BUTTON3, _("Start"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    buttonsBoxSizer->Add(playButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    optionsButton = new wxButton(this, ID_BUTTON4, _("Options"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    buttonsBoxSizer->Add(optionsButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    aboutButton = new wxButton(this, ID_BUTTON5, _("About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    buttonsBoxSizer->Add(aboutButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    mainBoxSizer->Add(buttonsBoxSizer, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    timesGrid = new wxGridSizer(2, 5, 0, 0);
    StatusLabel = new wxStaticText(this, ID_STATICTEXT9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    timesGrid->Add(StatusLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    onBoxSizer = new wxBoxSizer(wxVERTICAL);
    onLabel = new wxStaticText(this, ID_STATICTEXT1, _("Last Session"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    onBoxSizer->Add(onLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    onClock = new wxStaticText(this, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    onBoxSizer->Add(onClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timesGrid->Add(onBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    offBoxSizer = new wxBoxSizer(wxVERTICAL);
    offLabel = new wxStaticText(this, ID_STATICTEXT3, _("Last Pause"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    offBoxSizer->Add(offLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    offClock = new wxStaticText(this, ID_STATICTEXT4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    offBoxSizer->Add(offClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timesGrid->Add(offBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    runningBoxSizer = new wxBoxSizer(wxVERTICAL);
    runningLabel = new wxStaticText(this, ID_STATICTEXT5, _("Running"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    runningBoxSizer->Add(runningLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    runningClock = new wxStaticText(this, ID_STATICTEXT6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    runningBoxSizer->Add(runningClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timesGrid->Add(runningBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    leftBoxSizer = new wxBoxSizer(wxVERTICAL);
    leftLabel = new wxStaticText(this, ID_STATICTEXT7, _("Time Left"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    leftBoxSizer->Add(leftLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    leftClock = new wxStaticText(this, ID_STATICTEXT8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    leftBoxSizer->Add(leftClock, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timesGrid->Add(leftBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    mainBoxSizer->Add(timesGrid, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(mainBoxSizer);
    clockTimer.SetOwner(this, ID_TIMER1);
    clockTimer.Start(1000, false);
    checkTimer.SetOwner(this, ID_TIMER2);
    mainBoxSizer->Fit(this);
    mainBoxSizer->SetSizeHints(this);

    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EWMainFrame::OnStopButtonClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EWMainFrame::OnPlayButtonClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EWMainFrame::OnOptionsButtonClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EWMainFrame::OnaboutButtonClick);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&EWMainFrame::OnClockTimerTrigger);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&EWMainFrame::OnCheckTimerTrigger);
    //*)

    this->updateTimes();
}

void EWMainFrame::updateTimes()
{
    this->StatusLabel->SetLabel(wxString(this->m_Logic->getStatus().c_str(), wxConvUTF8));
    this->onClock->SetLabel(wxString(this->m_Logic->getTimeOn().c_str(), wxConvUTF8));
    this->offClock->SetLabel(wxString(this->m_Logic->getTimeOff().c_str(), wxConvUTF8));
    this->runningClock->SetLabel(wxString(this->m_Logic->getTimeRunning().c_str(), wxConvUTF8));
    this->leftClock->SetLabel(wxString(this->m_Logic->getTimeLeft().c_str(), wxConvUTF8));
}

EWMainFrame::~EWMainFrame()
{
    //(*Destroy(EWMainFrame)
    //*)
}

void EWMainFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void EWMainFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void EWMainFrame::OnOptionsButtonClick(wxCommandEvent& event)
{
    try
    {
        OptionsDialog dialog(this, m_Logic);
        dialog.ShowModal();
    }
    catch (BaseException e)
    {
        wxMessageDialog *dial = new wxMessageDialog(NULL,
            wxString(e.what(), wxConvUTF8), wxT("Error"), wxOK | wxICON_ERROR);
        dial->ShowModal();
    }
}

void EWMainFrame::OnaboutButtonClick(wxCommandEvent& event)
{
    AboutDialog dialog(this);
    dialog.ShowModal();
}

void EWMainFrame::OnPlayButtonClick(wxCommandEvent& event)
{
    wxTimerHandler handler(&this->checkTimer);
    this->m_Logic->start(handler);
}

void EWMainFrame::OnStopButtonClick(wxCommandEvent& event)
{
    wxTimerHandler handler(&this->checkTimer);
    this->m_Logic->stop(handler);
}

void EWMainFrame::OnClockTimerTrigger(wxTimerEvent& event)
{
    this->updateTimes();
}

void EWMainFrame::OnCheckTimerTrigger(wxTimerEvent& event)
{
    wxTimerHandler handler(&this->checkTimer);
    this->m_Logic->updateStatus(handler);
}

void EWMainFrame::OnClose(wxCloseEvent& event)
{
}
