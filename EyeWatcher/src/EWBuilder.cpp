#include "EWBuilder.h"

#include "wxConfigImpl.h"
#include "Config.h"
#include "MsgHandler.h"
#include "WebcamHandlerProc.h"
#include "TimeHandler.h"
#include "TimeKeeper.h"
#include "EWPresenter.h"
#include "EWMainFramePres.h"
#include "EWMainFrame.h"
#include "MyWxTimer.h"
#include "EyeWatcherApp.h"
#include "OptionsDialogPres.h"
#include "EWTaskBar.h"
#include "EWTaskBarPres.h"

/// @todo: make this testable? With an abstract factory perharps?
EWBuilder::EWBuilder(EyeWatcherApp* app, std::string configPath) :
    m_MsgHandler(NULL), m_ConfigImpl(NULL), m_Config(NULL), m_TimeHandler(NULL),
    m_PresenceHandler(NULL), m_TimeKeeper(NULL), m_ClockTimer(NULL),
    m_Presenter(NULL), m_MainFramePres(NULL), m_MainFrame(NULL),
    m_TaskBarPres(NULL), m_TaskBar(NULL), m_OptionsPres(NULL)
{
    //ctor
    try
    {
        this->m_MsgHandler = new MsgHandler();
        try
        {
            this->m_ConfigImpl = new wxConfigImpl(configPath);
            this->m_Config = new Config(m_ConfigImpl);
            ConfigData data = this->m_Config->getData();
            this->m_TimeHandler = new TimeHandler();
            this->m_PresenceHandler = new WebcamHandlerProc(data.webcamIndex, data.cascadePath,
                data.faceSizeX, data.faceSizeY);
            this->m_TimeKeeper = new TimeKeeper(m_TimeHandler,
                m_PresenceHandler, data.workLength, data.pauseLength, data.remFreq,
                data.checkFreq, data.pauseTol);
            this->m_CheckTimer = new MyWxTimer();
            this->m_ClockTimer = new MyWxTimer();
            this->m_Presenter = new EWPresenter(m_MsgHandler, m_Config, m_TimeKeeper,
                m_PresenceHandler, m_CheckTimer, m_ClockTimer);
            this->m_OptionsPres = new OptionsDialogPres(m_Presenter);
            this->m_MainFramePres = new EWMainFramePres(m_Presenter, m_MsgHandler, m_OptionsPres);
            this->m_MainFrame = new EWMainFrame(NULL, m_MainFramePres);
            this->m_TaskBarPres = new EWTaskBarPres(m_Presenter);
            this->m_TaskBar = new EWTaskBar(m_TaskBarPres);
        }
        catch (BaseException e)
        {
            this->m_MsgHandler->displayError(e.what());
            throw;
        }
    }
    catch (...)
    {
       this->deleteFields();
       throw; //rethrow. no memory leak
    }
}

EWBuilder::~EWBuilder()
{
    //dtor
    this->deleteFields();
}

void EWBuilder::deleteFields()
{
    if (this->m_MsgHandler != NULL) delete this->m_MsgHandler;
    if (this->m_ConfigImpl != NULL) delete this->m_ConfigImpl;
    if (this->m_Config != NULL) delete this->m_Config;
    if (this->m_TimeHandler != NULL) delete this->m_TimeHandler;
    if (this->m_PresenceHandler != NULL) delete this->m_PresenceHandler;
    if (this->m_TimeKeeper != NULL) delete this->m_TimeKeeper;
    if (this->m_Presenter != NULL) delete this->m_Presenter;
    if (this->m_MainFramePres != NULL) delete this->m_MainFramePres;
    // since m_MainFrame inherits from wxFrame, it is deleted by wx, not by us
    if (this->m_TaskBarPres != NULL) delete this->m_TaskBarPres;
    if (this->m_TaskBar != NULL) delete this->m_TaskBar;
    if (this->m_OptionsPres != NULL) delete this->m_OptionsPres;
}
