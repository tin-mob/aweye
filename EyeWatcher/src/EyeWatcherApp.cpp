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
#include "MsgHandler.h"

//(*AppHeaders
#include "EWMainFrame.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(EyeWatcherApp);

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
