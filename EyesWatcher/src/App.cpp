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
#include "App.h"
#include <wx/cmdline.h>
#include <wx/image.h>
#include <wx/taskbar.h>

#include "Builder.h"

#include "MsgHandler.h"
#include "wxConfigImpl.h"
#include "Config.h"
#include "WebcamHandlerProc.h"
#include "TimeHandler.h"
#include "TimeKeeper.h"
#include "MyWxTimer.h"
#include "EventHandler.h"
#include "Builder.h"
#include "TKController.h"
#include "MainFramePres.h"
#include "MainFrame.h"
#include "OptionsDialogPres.h"
#include "TaskBarPres.h"
#include "TaskBar.h"
#include "ConfigObservers.h"
#include "OptionsDialog.h"

#include <memory>

IMPLEMENT_APP(EW::App);

namespace EW
{
template <class T> class no_delete
{
    public:
        no_delete() {}
        void operator()(T* ptr) const {}
};

// MainFrame is managed by wx
template <>
struct PtrTraits<MainFrame>
{
  typedef typename std::unique_ptr<MainFrame, no_delete<MainFrame>> Ptr;
};

App::App() : m_AppImpl(nullptr)
{
}

App::~App()
{
}

bool App::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	if (m_AppImpl.get() == nullptr)
    	{
    	    m_AppImpl.reset(new Builder<MsgHandler, wxConfigImpl, Config,
                WebcamHandlerProc, TimeHandler, TimeKeeper, MyWxTimer, TKController,
                EventHandler, MainFramePres, MainFrame, TaskBarPres, TaskBar,
                OptionsDialogPres, OptionsDialog, TKConfigObserver,
                PresHdlrConfigObserver, EWPresConfigObserver>
                (this, std::string(m_ConfigPath.mb_str()), wxTaskBarIcon::IsAvailable(), wxID_OK));
    	}
    }
    return wxsOK;
}

void App::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.AddOption(wxT("c"),wxT("config"),
                     wxT("Use a specific configuration file."),
                     wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL);
    parser.SetSwitchChars (wxT("-"));
}

bool App::OnCmdLineParsed(wxCmdLineParser& parser)
{
    parser.Found(wxT("c"), &m_ConfigPath);
    return true;
}

void App::setTopWindow(AbstractMainFrame* frame)
{
    MainFrame* castedFrame = dynamic_cast<MainFrame*>(frame);

    assert(castedFrame != nullptr);
    if (castedFrame != nullptr)
    {
        SetTopWindow(castedFrame);
    }
}
}
