#include "EyeWatcherInt.h"
#include "Config.h"
#include "TimeKeeper.h"

#include <stdexcept>
#include <wx/msgdlg.h>

/// @todo: check everywhere constness...

EyeWatcherInt* EyeWatcherInt::m_Instance = NULL;

EyeWatcherInt* EyeWatcherInt::Instance()
{
    if (EyeWatcherInt::m_Instance == NULL)
    {
        EyeWatcherInt::m_Instance = new EyeWatcherInt();
    }
    return EyeWatcherInt::m_Instance;
}

void EyeWatcherInt::DisplayMsg(std::string msg)
{
    wxMessageDialog *dial = new wxMessageDialog(NULL,
        wxT("Error loading file"), wxT("Error"), wxOK | wxICON_ERROR);
    dial->ShowModal();
}

EyeWatcherInt::EyeWatcherInt() : m_Config(NULL), m_TimeKeeper(NULL)
{
    //ctor
}

EyeWatcherInt::~EyeWatcherInt()
{
    //dtor
    if (this->m_Config != NULL)
    {
        delete this->m_Config;
        this->m_Config = NULL;
    }

    if (this->m_TimeKeeper != NULL)
    {
        delete this->m_TimeKeeper;
        this->m_TimeKeeper = NULL;
    }
}

Config* EyeWatcherInt::getConfig()
{
    if (this->m_Config == NULL)
    {
        this->m_Config = new Config();
    }
    return this->m_Config;
}

TimeKeeper* EyeWatcherInt::getTimeKeeper()
{
    if (this->m_TimeKeeper == NULL)
    {
        if (this->m_Config == NULL)
        {
            this->m_Config = new Config();
        }
        this->m_TimeKeeper = new TimeKeeper(this->m_Config);
    }
    return this->m_TimeKeeper;
}
