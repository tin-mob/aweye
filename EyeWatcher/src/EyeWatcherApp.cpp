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

//(*AppHeaders
#include "EWMainFrame.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(EyeWatcherApp);

EyeWatcherApp::EyeWatcherApp() : m_Config(), m_TimeHandler(), m_PresenceHandler(), m_MsgHandler(),
    m_TimeKeeper(&m_Config, &m_TimeHandler, &m_PresenceHandler),
    m_Logic(&m_MsgHandler, &m_Config, &m_TimeKeeper)
{
}

EyeWatcherApp::~EyeWatcherApp()
{

}

bool EyeWatcherApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	EWMainFrame* Frame = new EWMainFrame(0, &m_Logic);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
