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

EyeWatcherApp::EyeWatcherApp() : m_Builder(NULL)
{
}

EyeWatcherApp::~EyeWatcherApp()
{
    if (this->m_Builder != NULL) delete this->m_Builder;
}

bool EyeWatcherApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        if (this->m_Builder == NULL) this->m_Builder = new EWBuilder();
    	EWMainFrame* Frame = new EWMainFrame(0, this->m_Builder->m_Presenter);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
