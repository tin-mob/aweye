/***************************************************************
 * Name:      EyeWatcherMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Robert Morin ()
 * Created:   2013-01-06
 * Copyright: Robert Morin ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "EyeWatcherMain.h"
#include "OptionsDialog.h"
#include "AboutDialog.h"
#include <wx/msgdlg.h>
#include <stdexcept>

//(*InternalHeaders(EyeWatcherFrame)
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

//(*IdInit(EyeWatcherFrame)
const long EyeWatcherFrame::ID_BUTTON1 = wxNewId();
const long EyeWatcherFrame::ID_BUTTON2 = wxNewId();
const long EyeWatcherFrame::ID_BUTTON3 = wxNewId();
const long EyeWatcherFrame::ID_BUTTON4 = wxNewId();
const long EyeWatcherFrame::ID_BUTTON5 = wxNewId();
const long EyeWatcherFrame::ID_STATICTEXT1 = wxNewId();
const long EyeWatcherFrame::ID_STATICTEXT2 = wxNewId();
const long EyeWatcherFrame::ID_STATICTEXT3 = wxNewId();
const long EyeWatcherFrame::ID_STATICTEXT4 = wxNewId();
const long EyeWatcherFrame::ID_STATICTEXT5 = wxNewId();
const long EyeWatcherFrame::ID_STATICTEXT6 = wxNewId();
const long EyeWatcherFrame::ID_STATICTEXT7 = wxNewId();
const long EyeWatcherFrame::ID_STATICTEXT8 = wxNewId();
const long EyeWatcherFrame::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EyeWatcherFrame,wxFrame)
    //(*EventTable(EyeWatcherFrame)
    //*)
END_EVENT_TABLE()

EyeWatcherFrame::EyeWatcherFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(EyeWatcherFrame)
    wxBoxSizer* buttonsBoxSizer;
    wxBoxSizer* offBoxSizer;
    wxBoxSizer* mainBoxSizer;
    wxBoxSizer* remainingBoxSizer;
    wxBoxSizer* lastBoxSizer;
    wxGridSizer* timesGrid;
    wxBoxSizer* onBoxSizer;
    
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
    mainBoxSizer->Add(buttonsBoxSizer, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    timesGrid = new wxGridSizer(2, 4, 0, 0);
    onBoxSizer = new wxBoxSizer(wxVERTICAL);
    onLabel = new wxStaticText(this, ID_STATICTEXT1, _("Time on PC"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    onBoxSizer->Add(onLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    onTime = new wxStaticText(this, ID_STATICTEXT2, _("99:99"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    onBoxSizer->Add(onTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timesGrid->Add(onBoxSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    lastBoxSizer = new wxBoxSizer(wxVERTICAL);
    lastLabel = new wxStaticText(this, ID_STATICTEXT3, _("Last Pause"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    lastBoxSizer->Add(lastLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lastTime = new wxStaticText(this, ID_STATICTEXT4, _("99:99"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    lastBoxSizer->Add(lastTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timesGrid->Add(lastBoxSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    offBoxSizer = new wxBoxSizer(wxVERTICAL);
    offLabel = new wxStaticText(this, ID_STATICTEXT5, _("Time in Pause"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    offBoxSizer->Add(offLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    offTime = new wxStaticText(this, ID_STATICTEXT6, _("99:99"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    offBoxSizer->Add(offTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timesGrid->Add(offBoxSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    remainingBoxSizer = new wxBoxSizer(wxVERTICAL);
    remainingLabel = new wxStaticText(this, ID_STATICTEXT7, _("Time Left"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    remainingBoxSizer->Add(remainingLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    remainingTime = new wxStaticText(this, ID_STATICTEXT8, _("99:99"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    remainingBoxSizer->Add(remainingTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timesGrid->Add(remainingBoxSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    mainBoxSizer->Add(timesGrid, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(mainBoxSizer);
    eyeWatcherTimer.SetOwner(this, ID_TIMER1);
    mainBoxSizer->Fit(this);
    mainBoxSizer->SetSizeHints(this);
    
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EyeWatcherFrame::OnOptionsButtonClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EyeWatcherFrame::OnaboutButtonClick);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&EyeWatcherFrame::OneyeWatcherTimerTrigger);
    //*)
}

EyeWatcherFrame::~EyeWatcherFrame()
{
    //(*Destroy(EyeWatcherFrame)
    //*)
}

void EyeWatcherFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void EyeWatcherFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void EyeWatcherFrame::OnOptionsButtonClick(wxCommandEvent& event)
{
    try
    {
        OptionsDialog dialog(this);
        dialog.ShowModal();
    }
    catch (std::logic_error e)
    {
        wxMessageDialog *dial = new wxMessageDialog(NULL,
            wxString(e.what(), wxConvUTF8), wxT("Error"), wxOK | wxICON_ERROR);
        dial->ShowModal();
    }
}

void EyeWatcherFrame::OnaboutButtonClick(wxCommandEvent& event)
{
    AboutDialog dialog(this);
    dialog.ShowModal();
}

void EyeWatcherFrame::OneyeWatcherTimerTrigger(wxTimerEvent& event)
{
}
