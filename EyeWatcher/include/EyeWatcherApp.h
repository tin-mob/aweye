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


#ifndef EYEWATCHERAPP_H
#define EYEWATCHERAPP_H

#include <wx/app.h>
#include "SetTopWindowInt.h"

class wxCmdLineParser;
template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWAppController, class TEWPresenter,
    class TEWMainFramePres, class TEWMainFrame, class TOptionsDialogPres, class TEWTaskbarPres,
    class TEWTaskbar, class TDisplayOptionsDialogCmd>
class EWBuilder;
class AbstractEWMainFrame;
class MsgHandler;
class wxConfigImpl;
class Config;
class WebcamHandlerProc;
class TimeHandler;
class TimeKeeper;
class MyWxTimer;
class EWAppController;
class EWPresenter;
class EWMainFramePres;
class EWMainFrame;
class OptionsDialogPres;
class EWTaskBarPres;
class EWTaskBar;
class DisplayOptionsDialogCmd;
class EyeWatcherApp : public wxApp, public SetTopWindowInt
{
    public:
        EyeWatcherApp();
       ~EyeWatcherApp();
        virtual bool OnInit();
        virtual void OnInitCmdLine(wxCmdLineParser& parser);
        virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

        virtual void setTopWindow(AbstractEWMainFrame* frame);
    private:
        EWBuilder<MsgHandler, wxConfigImpl, Config,
            WebcamHandlerProc, TimeHandler, TimeKeeper, MyWxTimer, EWAppController,
            EWPresenter, EWMainFramePres, EWMainFrame, OptionsDialogPres,
            EWTaskBarPres, EWTaskBar, DisplayOptionsDialogCmd>* m_AppImpl;
        wxString m_ConfigPath;
};

#endif // EYEWATCHERAPP_H
