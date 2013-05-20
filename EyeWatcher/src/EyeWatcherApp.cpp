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
#include <wx/cmdline.h>
#include <wx/image.h>
#include <wx/taskbar.h>

#include "EWBuilder.h"

#include "MsgHandler.h"
#include "wxConfigImpl.h"
#include "Config.h"
#include "WebcamHandlerProc.h"
#include "TimeHandler.h"
#include "TimeKeeper.h"
#include "MyWxTimer.h"
#include "EWAppController.h"
#include "EWPresenter.h"
#include "EWMainFramePres.h"
#include "EWMainFrame.h"
#include "OptionsDialogPres.h"
#include "EWTaskBarPres.h"
#include "EWTaskBar.h"
#include "DisplayOptionsDialogCmd.h"

IMPLEMENT_APP(EyeWatcherApp);

EyeWatcherApp::EyeWatcherApp() : m_AppImpl(NULL)
{
}

EyeWatcherApp::~EyeWatcherApp()
{
    if (this->m_AppImpl != NULL) delete this->m_AppImpl;
}

bool EyeWatcherApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	if (this->m_AppImpl == NULL)
    	{
    	    this->m_AppImpl = new EWBuilder<MsgHandler, wxConfigImpl, Config,
                WebcamHandlerProc, TimeHandler, TimeKeeper, MyWxTimer, EWAppController,
                EWPresenter, EWMainFramePres, EWMainFrame, OptionsDialogPres,
                EWTaskBarPres, EWTaskBar, DisplayOptionsDialogCmd>(this,
                std::string(m_ConfigPath.mb_str()), wxTaskBarIcon::IsAvailable());
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
