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


#ifndef APP_H
#define APP_H

#include <memory>
#include <wx/app.h>
#include "SetTopWindowInt.h"

class wxCmdLineParser;
namespace EW
{
template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TTKController,
    class TEventHandler, class TMainFramePres, class TMainFrame, class TEWTaskBarPres,
    class TEWTaskBar, class TOptionsDialogPres, class TOptionsDialog,
    class TTKConfigObserver, class TPresHdlrConfigObserver, class TEWPresConfigObserver>
class Builder;
class AbstractMainFrame;
class MsgHandler;
class wxConfigImpl;
class Config;
class WebcamHandlerProc;
class TimeHandler;
class TimeKeeper;
class MyWxTimer;
class EventHandler;
class TKController;
class MainFramePres;
class MainFrame;
class TaskBarPres;
class TaskBar;
class OptionsDialog;
class OptionsDialogPres;
class AbstractMsgHandler;
class TKConfigObserver;
class PresHdlrConfigObserver;
class EWPresConfigObserver;
class App : public wxApp, public SetTopWindowInt
{
    public:
        App();
        ~App();

        App(const App&) = delete;
        App& operator=(const App&) = delete;

        virtual bool OnInit();
        virtual void OnInitCmdLine(wxCmdLineParser& parser);
        virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

        virtual void setTopWindow(AbstractMainFrame* frame);
    private:
        std::unique_ptr<Builder<MsgHandler, wxConfigImpl, Config,
                WebcamHandlerProc, TimeHandler, TimeKeeper, MyWxTimer, TKController,
                EventHandler, MainFramePres, MainFrame, TaskBarPres, TaskBar,
                OptionsDialogPres, OptionsDialog, TKConfigObserver,
                PresHdlrConfigObserver, EWPresConfigObserver>>
            m_AppImpl;

        wxString m_ConfigPath;
};
}

#endif // APP_H
