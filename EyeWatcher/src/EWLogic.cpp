#include "EWLogic.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "HandlerFactory.h"
#include <stdexcept>
#include <wx/msgdlg.h>

template <class HandlerFactory>
EWLogic<HandlerFactory>::EWLogic() : m_Config(NULL), m_TimeKeeper(NULL)
{
    //ctor
}

template <class HandlerFactory>
EWLogic<HandlerFactory>::~EWLogic()
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

template <class HandlerFactory>
const Config* EWLogic<HandlerFactory>::getConfig()
{
    if (this->m_Config == NULL)
    {
        this->m_Config = new Config();
    }
    else
    {
        this->m_Config->checkLoad();
    }
    return this->m_Config;
}

template <class HandlerFactory>
const TimeKeeper* EWLogic<HandlerFactory>::getTimeKeeper()
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

template <class HandlerFactory>
void  EWLogic<HandlerFactory>::saveConfig(
            unsigned int m_WorkLength,
            unsigned int m_PauseLength,
            unsigned int m_RemFreq,
            unsigned int m_CheckFreq,
            unsigned int m_PauseTol,
            bool m_Startup,
            bool m_SoundAlarm,
            bool m_PopupAlarm,
            bool m_EmailAlarm,
            std::string m_EmailAddr)
{

}

template <class HandlerFactory>
void  EWLogic<HandlerFactory>::start()
{

}

template <class HandlerFactory>
void  EWLogic<HandlerFactory>::stop()
{

}

template <class HandlerFactory>
void  EWLogic<HandlerFactory>::updateStatus()
{

}
