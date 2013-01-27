/***************************************************************
 * Name:      EyeWatcherMain.h
 * Purpose:   Defines Application Frame
 * Author:    Robert Morin ()
 * Created:   2013-01-06
 * Copyright: Robert Morin ()
 * License:
 **************************************************************/

#ifndef EYEWATCHERMAIN_H
#define EYEWATCHERMAIN_H

//(*Headers(EyeWatcherFrame)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)

class EyeWatcherFrame: public wxFrame
{
    public:

        EyeWatcherFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~EyeWatcherFrame();

    private:

        //(*Handlers(EyeWatcherFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOptionsButtonClick(wxCommandEvent& event);
        void OnaboutButtonClick(wxCommandEvent& event);
        void OneyeWatcherTimerTrigger(wxTimerEvent& event);
        //*)

        //(*Identifiers(EyeWatcherFrame)
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

        //(*Declarations(EyeWatcherFrame)
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

        DECLARE_EVENT_TABLE()
};

#endif // EYEWATCHERMAIN_H
