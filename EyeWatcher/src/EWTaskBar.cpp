#include "EWTaskBar.h"

#include "EWPresenter.h"
#include "wx_pch.h"
#include <wx/menu.h>

BEGIN_EVENT_TABLE(EWTaskBar,wxTaskBarIcon)
    EVT_MENU(ID_RESTORE, EWTaskBar::OnMenuRestore)
    EVT_MENU(ID_START,    EWTaskBar::OnMenuStart)
    EVT_MENU(ID_STOP,EWTaskBar::OnMenuStop)
    EVT_MENU(ID_PAUSE,EWTaskBar::OnMenuPause)
    EVT_MENU(ID_RESUME,EWTaskBar::OnMenuResume)
    EVT_MENU(ID_EXIT,EWTaskBar::OnMenuExit)
END_EVENT_TABLE()

EWTaskBar::EWTaskBar(EWPresenter* presenter, std::string iconLoc) :
    m_Presenter(presenter), m_IconLoc(iconLoc), m_Menu(NULL)
{
    //ctor
    // get icon from this->m_IconLoc
    this->m_Presenter->attach(this);
    this->SetIcon(wxIcon(wxString(this->m_IconLoc.c_str(), wxConvUTF8)));
}

EWTaskBar::~EWTaskBar()
{
    //dtor
    if (this->m_Menu != NULL)
    {
        delete this->m_Menu;
    }
    this->RemoveIcon();
}

void EWTaskBar::setPopupMenu( bool running, bool snoozed, std::string onClock,
    std::string offClock, std::string runningClock, std::string leftClock)
{
    if (this->m_Menu != NULL)
    {
        delete this->m_Menu;
    }
    this->m_Menu = new wxMenu();
    this->m_Menu->Append(EWTaskBar::ID_RESTORE, wxT("Restore"));
    this->m_Menu->AppendSeparator();
}

void EWTaskBar::reloadIcon()
{
    if(this->IsIconInstalled())
    {
        this->RemoveIcon();
    }
    this->SetIcon(wxIcon(wxString(this->m_IconLoc.c_str(), wxConvUTF8)));
}

void EWTaskBar::update(Observable*)
{

}


void EWTaskBar::OnMenuRestore(wxCommandEvent&)
{

}

void EWTaskBar::OnMenuStart(wxCommandEvent&)
{

}

void EWTaskBar::OnMenuStop(wxCommandEvent&)
{

}

void EWTaskBar::OnMenuPause(wxCommandEvent&)
{

}

void EWTaskBar::OnMenuResume(wxCommandEvent&)
{

}

void EWTaskBar::OnMenuExit(wxCommandEvent&)
{

}

