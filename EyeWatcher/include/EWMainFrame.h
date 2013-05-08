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
//*)
#include <wx/valgen.h>
#include <string>

#include "AbstractEWMainFrame.h"

class EWMainFramePres;
class EWPresenter;
class EWMainFrame: public wxFrame, public AbstractEWMainFrame
{
    public:

        EWMainFrame(wxWindow* parent, EWMainFramePres* presenter, wxWindowID id = -1);
        virtual ~EWMainFrame();

        virtual void setValues( std::string status, std::string onClock,
                       std::string offClock, std::string runningClock,
                       std::string leftClock);
        virtual void notifyMessage(std::string message, bool warning = false);
        virtual void displayOptionsDialog(OptionsDialogPres* presenter);
        virtual void show();
        virtual void setPauseButtonLabel(std::string label);
        virtual void setStartButtonLabel(std::string label);

    private:

        //(*Handlers(EWMainFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOptionsButtonClick(wxCommandEvent& event);
        void OnPlayButtonClick(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnPauseButtonClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(EWMainFrame)
        static const long ID_BUTTON1;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        //*)

        //(*Declarations(EWMainFrame)
        wxButton* quitButton;
        wxStaticText* runningClock;
        wxStaticText* onClock;
        wxStaticText* onLabel;
        wxStaticText* runningLabel;
        wxButton* playButton;
        wxStaticText* leftClock;
        wxButton* pauseButton;
        wxStaticText* offClock;
        wxStaticText* StatusLabel;
        wxStaticText* offLabel;
        wxStaticText* leftLabel;
        wxButton* optionsButton;
        wxButton* aboutButton;
        //*)

        EWMainFramePres* m_Presenter;

        DECLARE_EVENT_TABLE()
};

#endif // EWMAINFRAME_H
