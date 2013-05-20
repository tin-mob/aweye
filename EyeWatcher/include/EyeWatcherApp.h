/***************************************************************
 * Name:      EyeWatcherApp.h
 * Purpose:   Defines Application Class
 * Author:    Robert Morin ()
 * Created:   2013-01-06
 * Copyright: Robert Morin ()
 * License:
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
