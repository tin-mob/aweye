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


#ifndef EWAPP_H
#define EWAPP_H

#include <memory>
#include <wx/app.h>
#include "SetTopWindowInt.h"

class wxCmdLineParser;
template <class T> class no_delete;
template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWAppController,
    class TEWPresenter, class TEWMainFramePres, class TEWMainFrame, class TEWTaskbarPres,
    class TEWTaskbar, class TOptionsDialogPres, class TBuilderOptionsDialogPres,
    class TDisplayOptionsDialogCmd> class EWBuilder;
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
class EWTaskBarPres;
class EWTaskBar;
class OptionsDialog;
class OptionsDialogPres;
class BuilderOptionsDialogPres;
class DisplayOptionsDialogCmd;
class AbstractMsgHandler;
class EWApp : public wxApp, public SetTopWindowInt
{
    public:
        EWApp();
        ~EWApp();

        EWApp(const EWApp&) = delete;
        EWApp& operator=(const EWApp&) = delete;

        virtual bool OnInit();
        virtual void OnInitCmdLine(wxCmdLineParser& parser);
        virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

        virtual void setTopWindow(AbstractEWMainFrame* frame);
    private:
        std::unique_ptr<EWBuilder<MsgHandler, wxConfigImpl, Config, WebcamHandlerProc,
            TimeHandler, TimeKeeper, MyWxTimer, EWAppController, EWPresenter,
            EWMainFramePres, EWMainFrame, EWTaskBarPres, EWTaskBar,
            OptionsDialogPres, BuilderOptionsDialogPres, DisplayOptionsDialogCmd>>
            m_AppImpl;

        wxString m_ConfigPath;
};

#endif // EWAPP_H
