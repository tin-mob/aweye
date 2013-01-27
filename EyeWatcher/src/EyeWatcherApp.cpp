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

//(*AppHeaders
#include "EyeWatcherMain.h"
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
    	EyeWatcherFrame* Frame = new EyeWatcherFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

//    try
//    {
//
//    }
//    catch (std::string error)
//    {
//        wxMessageDialog *errorDialog = new wxMessageDialog(NULL,
//            wxString(error.c_str(), wxConvUTF8), wxT("Error"), wxOK | wxICON_ERROR);
//        errorDialog->ShowModal();
//
//        Close();
//    }
