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
#include "WxHandlerFactory.h"

class EWLogic;
class AbstractConfig;
class AbstractTimeHandler;
class AbstractPresenceHandler;
class AbstractMsgHandler;
class TimeKeeper;

class EyeWatcherApp : public wxApp
{
    public:
        EyeWatcherApp();
        ~EyeWatcherApp();
        virtual bool OnInit();
    private:
        EWLogic* m_Logic;
        AbstractConfig* m_Config;
        AbstractTimeHandler* m_TimeHandler;
        AbstractPresenceHandler* m_PresenceHandler;
        AbstractMsgHandler* m_MsgHandler;
        TimeKeeper* m_TimeKeeper;

};

#endif // EYEWATCHERAPP_H
