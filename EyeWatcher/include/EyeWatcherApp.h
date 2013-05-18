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
class EWBuilder;
class AbstractEWMainFrame;
class EWMainFrame;
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
        EWBuilder* m_Builder;
        wxString m_ConfigPath;
};

#endif // EYEWATCHERAPP_H
