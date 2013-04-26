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

#include "EWBuilder.h"

#include <wx/app.h>

class EyeWatcherApp : public wxApp
{
    public:
        EyeWatcherApp();
       ~EyeWatcherApp();
        virtual bool OnInit();
    private:
        EWBuilder* m_Builder;
};

#endif // EYEWATCHERAPP_H
