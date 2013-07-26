/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "aweye/core/AbstractMainFrame.h"

//(*Headers(MainFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/statline.h>
#include <wx/frame.h>
#include <wx/stattext.h>
//*)
#include <string>


namespace Aweye {

class AbstractEventHandler;
class AbstractOptionsDialogPres;
class AbstractUtils;

namespace WX {

class MainFrame: public wxFrame, public AbstractMainFrame
{
    public:
        MainFrame(AbstractEventHandler& hdlr, AbstractUtils& utils,
                    bool taskBarCreated = true, wxWindow* parent = nullptr, wxWindowID id = -1);
        virtual ~MainFrame();

        virtual void setValues( std::string statusLabel, std::string onClockLabel,
                       std::string offClockLabel, std::string runningClockLabel,
                       std::string leftClockLabel);
        virtual void show(bool show = true);
        virtual void setPauseButtonLabel(std::string label);
        virtual void setStartButtonLabel(std::string label);
        virtual void close();

    private:

        //(*Handlers(MainFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOptionsButtonClick(wxCommandEvent& event);
        void OnPlayButtonClick(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnPauseButtonClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(MainFrame)
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

        //(*Declarations(MainFrame)
        wxStaticText* m_StatusLabel;
        wxMenuBar* m_EwMenuBar;
        wxMenu* m_DoMenu;
        wxStaticText* m_LeftClock;
        wxStaticLine* m_StaticLine1;
        wxStaticLine* m_StaticLine2;
        wxStaticText* m_RunningLabel;
        wxStaticText* m_OffClock;
        wxStaticText* m_OffLabel;
        wxStaticText* m_RunningClock;
        wxStaticText* m_OnLabel;
        wxMenuItem* m_StartMenuItem;
        wxStaticLine* m_StaticLine3;
        wxStaticLine* m_StaticLine4;
        wxStaticText* m_OnClock;
        wxStaticText* m_LeftLabel;
        //*)

        AbstractEventHandler& m_EventHandler;
        bool m_TaskBarCreated;

        DECLARE_EVENT_TABLE()
};
}}

#endif // MAINFRAME_H
