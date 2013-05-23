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
#include <wx/menu.h>
#include <wx/statline.h>
#include <wx/frame.h>
#include <wx/stattext.h>
//*)
#include <wx/valgen.h>
#include <string>

#include "AbstractEWMainFrame.h"

template <class TView>
class AbstractEWViewPres;
class EWPresenter;
class AbstractOptionsDialogPres;
class EWMainFrame: public wxFrame, public AbstractEWMainFrame
{
    public:
        EWMainFrame(AbstractEWViewPres<AbstractEWMainFrame>* presenter,
                    bool taskbarCreated = true, wxWindow* parent = nullptr, wxWindowID id = -1);
        virtual ~EWMainFrame();

        virtual void setValues( std::string status, std::string onClock,
                       std::string offClock, std::string runningClock,
                       std::string leftClock);
        virtual void show(bool show = true);
        virtual void setPauseButtonLabel(std::string label);
        virtual void setStartButtonLabel(std::string label);
        virtual void close();

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
        static const long ID_STATICTEXT9;
        static const long ID_STATICLINE1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICLINE2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICLINE3;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICLINE4;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STARTMENUITEM;
        static const long ID_PAUSEMENUITEM;
        static const long ID_OPTIONSMENUITEM;
        static const long ID_ABOUTMENUITEM;
        static const long ID_EXITMENUITEM;
        //*)

        //(*Declarations(EWMainFrame)
        wxStaticText* runningClock;
        wxMenuItem* StartMenuItem;
        wxStaticLine* StaticLine2;
        wxStaticText* onClock;
        wxStaticText* onLabel;
        wxStaticText* runningLabel;
        wxMenu* DoMenu;
        wxMenuBar* EwMenuBar;
        wxStaticText* leftClock;
        wxStaticText* offClock;
        wxStaticLine* StaticLine1;
        wxStaticLine* StaticLine3;
        wxStaticText* StatusLabel;
        wxStaticText* offLabel;
        wxStaticText* leftLabel;
        wxStaticLine* StaticLine4;
        //*)

        AbstractEWViewPres<AbstractEWMainFrame>* m_Presenter;
        bool m_TaskbarCreated;

        DECLARE_EVENT_TABLE()
};

#endif // EWMAINFRAME_H
