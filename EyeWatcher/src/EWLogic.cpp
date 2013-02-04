#include "EWLogic.h"
#include "Config.h"
#include "TimeKeeper.h"
#include "HandlerFactory.h"
#include "AbstractMsgHandler.h"

#include <stdexcept>
#include <wx/msgdlg.h>

// TimeKeeper can fail when the camera is closed/whatever, must do lazy instance
EWLogic::EWLogic(HandlerFactory* handlerFactory)
{
    //ctor
    this->m_MsgHandler = handlerFactory->getMsgHandler();
    this->m_Config = new Config();
    this->m_TimeKeeper = new TimeKeeper(this->m_Config, handlerFactory);
}

EWLogic::~EWLogic()
{
    //dtor
    delete this->m_Config;
    this->m_Config = NULL;

    delete this->m_TimeKeeper;
    this->m_TimeKeeper = NULL;

    delete this->m_MsgHandler;
    this->m_MsgHandler = NULL;
}

const Config* EWLogic::getConfig()
{
    return this->m_Config;
}

const TimeKeeper* EWLogic::getTimeKeeper()
{
    return this->m_TimeKeeper;
}

void  EWLogic::saveConfig(
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

void  EWLogic::start()
{

}

void  EWLogic::stop()
{

}

void  EWLogic::updateStatus()
{

}
