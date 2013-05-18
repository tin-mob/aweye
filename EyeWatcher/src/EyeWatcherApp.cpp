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
#include "EWBuilder.h"
#include "WxEWFactory.h"
#include "EWMainFrame.h"
#include <wx/cmdline.h>
#include "EWMainFrame.h"
#include <wx/image.h>
#include <wx/taskbar.h>

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
    if (!wxApp::OnInit())
        return false;

    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	if (this->m_Builder == NULL)
    	{
    	    WxEWFactory factory;
    	    this->m_Builder =
            new EWBuilder(&factory, this, std::string(m_ConfigPath.mb_str()), wxTaskBarIcon::IsAvailable());
    	}
    }
    return wxsOK;

}

void EyeWatcherApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.AddOption(wxT("c"),wxT("config"),
                     wxT("Use a specific configuration file."),
                     wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL);
    parser.SetSwitchChars (wxT("-"));
}

bool EyeWatcherApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    parser.Found(wxT("c"), &m_ConfigPath);
    return true;
}

void EyeWatcherApp::setTopWindow(AbstractEWMainFrame* frame)
{
    EWMainFrame* castedFrame = dynamic_cast<EWMainFrame*>(frame);

    assert(castedFrame != NULL);
    if (castedFrame != NULL)
    {
        SetTopWindow(castedFrame);
    }
}
