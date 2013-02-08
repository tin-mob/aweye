/***************************************************************
 * Name:      EyeWatcherApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Robert Morin ()
 * Created:   2013-01-06
 * Copyright: Robert Morin ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "EyeWatcherApp.h"
#include "Config.h"
#include "MsgHandler.h"
#include "WebcamHandler.h"
#include "TimeHandler.h"
#include "TimeKeeper.h"
#include "EWLogic.h"

//(*AppHeaders
#include "EWMainFrame.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(EyeWatcherApp);

EyeWatcherApp::EyeWatcherApp() : m_Logic(NULL), m_Config(NULL), m_TimeHandler(NULL), m_PresenceHandler(NULL), m_MsgHandler(NULL), m_TimeKeeper(NULL)
{
    this->m_Config = new Config();
    this->m_MsgHandler = new MsgHandler();
    this->m_PresenceHandler = new WebcamHandler();
    this->m_TimeHandler = new TimeHandler();
    this->m_TimeKeeper = new TimeKeeper(this->m_Config, this->m_TimeHandler, this->m_PresenceHandler);
    this->m_Logic = new EWLogic(this->m_MsgHandler, this->m_Config, this->m_TimeKeeper);
}

EyeWatcherApp::~EyeWatcherApp()
{
    if (this->m_Config != NULL) {delete this->m_Config;}
    if (this->m_MsgHandler != NULL) {delete this->m_MsgHandler;}
    if (this->m_PresenceHandler != NULL) {delete this->m_PresenceHandler;}
    if (this->m_TimeHandler != NULL) {delete this->m_TimeHandler;}
    if (this->m_TimeKeeper != NULL) {delete this->m_TimeKeeper;}
    if (this->m_Logic != NULL) {delete this->m_Logic;}
}

bool EyeWatcherApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	EWMainFrame* Frame = new EWMainFrame(0, m_Logic);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
