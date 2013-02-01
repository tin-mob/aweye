/***************************************************************
 * Name:      EyeWatcherMain.h
 * Purpose:   Defines Application Frame
 * Author:    Robert Morin ()
 * Created:   2013-01-06
 * Copyright: Robert Morin ()
 * License:
 **************************************************************/

#ifndef EWMAINFRAME_H
#define EWMAINFRAME_H

//(*Headers(EWMainFrame)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)

#include "EWLogic.h"
#include "WxHandlerFactory.h"

class EWMainFrame: public wxFrame
{
    public:

        EWMainFrame(wxWindow* parent, EWLogic<WxHandlerFactory>* logic, wxWindowID id = -1);
        virtual ~EWMainFrame();

    private:

        //(*Handlers(EWMainFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOptionsButtonClick(wxCommandEvent& event);
        void OnaboutButtonClick(wxCommandEvent& event);
        void OneyeWatcherTimerTrigger(wxTimerEvent& event);
        //*)

        //(*Identifiers(EWMainFrame)
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(EWMainFrame)
        wxStaticText* remainingLabel;
        wxStaticText* onLabel;
        wxButton* playButton;
        wxStaticText* offTime;
        wxButton* pauseButton;
        wxTimer eyeWatcherTimer;
        wxStaticText* offLabel;
        wxStaticText* lastTime;
        wxButton* optionsButton;
        wxStaticText* remainingTime;
        wxButton* stopButton;
        wxButton* aboutButton;
        wxStaticText* lastLabel;
        wxStaticText* onTime;
        //*)

        EWLogic<WxHandlerFactory>* m_Logic;

        DECLARE_EVENT_TABLE()
};

#endif // EWMAINFRAME_H
