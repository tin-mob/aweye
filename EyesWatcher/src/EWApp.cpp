/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "wx_pch.h"
#include "EWApp.h"
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

IMPLEMENT_APP(EWApp);

EWApp::EWApp() : m_AppImpl(nullptr)
{
}

EWApp::~EWApp()
{
    if (this->m_AppImpl != nullptr) delete this->m_AppImpl;
}

bool EWApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	if (this->m_AppImpl == nullptr)
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

void EWApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.AddOption(wxT("c"),wxT("config"),
                     wxT("Use a specific configuration file."),
                     wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL);
    parser.SetSwitchChars (wxT("-"));
}

bool EWApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    parser.Found(wxT("c"), &m_ConfigPath);
    return true;
}

void EWApp::setTopWindow(AbstractEWMainFrame* frame)
{
    EWMainFrame* castedFrame = dynamic_cast<EWMainFrame*>(frame);

    assert(castedFrame != nullptr);
    if (castedFrame != nullptr)
    {
        SetTopWindow(castedFrame);
    }
}