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
#include "EWLogic.h"
#include "WxHandlerFactory.h"

class EyeWatcherApp : public wxApp
{
    public:
        virtual bool OnInit();
    private:
        EWLogic<WxHandlerFactory> m_Logic;

};

#endif // EYEWATCHERAPP_H
