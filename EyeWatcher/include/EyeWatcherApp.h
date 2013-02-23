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

#include "Config.h"
#include "MsgHandler.h"
#include "WebcamHandler.h"
#include "TimeHandler.h"
#include "TimeKeeper.h"
#include "EWLogic.h"

class EyeWatcherApp : public wxApp
{
    public:
        EyeWatcherApp();
       ~EyeWatcherApp();
        virtual bool OnInit();
    private:
        Config m_Config;
        TimeHandler m_TimeHandler;
        WebcamHandler m_PresenceHandler;
        MsgHandler m_MsgHandler;
        TimeKeeper m_TimeKeeper;
        EWLogic m_Logic;
};

#endif // EYEWATCHERAPP_H
