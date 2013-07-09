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


#include "ew/Builder.h"
#include "ew/Config.h"
#include "ew/ConfigObservers.h"
#include "ew/EventHandler.h"
#include "ew/MainFramePres.h"
#include "ew/OptionsDialogPres.h"
#include "ew/TaskBarPres.h"
#include "ew/TimeHandler.h"
#include "ew/TimeKeeper.h"
#include "ew/tr.h"
#include "ew/TKController.h"
#include "ew/WebcamHandlerProc.h"
#include "ew/wx/App.h"
#include "ew/wx/ConfigImpl.h"
#include "ew/wx/Task.h"
#include "ew/wx/MainFrame.h"
#include "ew/wx/MsgHandler.h"
#include "ew/wx/Timer.h"
#include "ew/wx/OptionsDialog.h"
#include "ew/wx/TaskBar.h"
#include "ew/wx/Utils.h"
#include "ew/wx/wx_pch.h"

#include <memory>
#include <wx/cmdline.h>
#include <wx/image.h>
#include <wx/taskbar.h>

IMPLEMENT_APP(EW::WX::App);

namespace EW {

template <class T> class no_delete
{
    public:
        no_delete() {}
        void operator()(T* ptr) const {}
};

// MainFrame is managed by wx
template <>
struct PtrTraits<WX::MainFrame>
{
  typedef typename std::unique_ptr<WX::MainFrame, no_delete<WX::MainFrame>> Ptr;
};

template <>
struct PresenceHandlerFactory<WebcamHandlerProc>
{
    template <class TBuilder>
    static WebcamHandlerProc* create(TBuilder& b, const ConfigData& data)
    {
        auto cmd = [] (std::shared_ptr<const TaskContext> context)
        {
            WX::Task::run(context);
        };
        return new WebcamHandlerProc(*(b.m_Utils), cmd, data.webcamIndex, data.cascadePath,
            data.faceSizeX, data.faceSizeY);
    }
};

// this vs builder param?
template <class TTKController>
struct TaskExceptionLinker<WebcamHandlerProc, TTKController>
{
    static void link(WebcamHandlerProc& p, TTKController& c)
    {
        p.attach(&c);
    }
};

namespace WX {

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
    	    m_AppImpl.reset(new Builder<MsgHandler, ConfigImpl, Config,
                WebcamHandlerProc, TimeHandler, TimeKeeper, Timer, TKController,
                EventHandler, MainFramePres, MainFrame, TaskBarPres, TaskBar,
                OptionsDialogPres, OptionsDialog, TKConfigObserver,
                PresHdlrConfigObserver, EWPresConfigObserver, Utils>
                (this, std::string(m_ConfigPath), wxTaskBarIcon::IsAvailable(), wxID_OK));
    	}
    }
    return wxsOK;
}

void App::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.AddOption(wxT("c"),wxT("config"),
                     _("Use a specific configuration file."),
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
}}
