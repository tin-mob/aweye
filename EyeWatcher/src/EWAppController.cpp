#include "EWAppController.h"
#include "AbstractEWFactory.h"
#include "ConfigData.h"
#include "BaseException.h"

#include "AbstractConfigImpl.h"
#include "AbstractConfig.h"
#include "AbstractMsgHandler.h"
#include "AbstractPresenceHandler.h"
#include "AbstractTimeHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractEWPresenter.h"
#include "AbstractEWMainFramePres.h"
#include "AbstractEWMainFrame.h"
#include "AbstractTimer.h"
#include "AbstractOptionsDialogPres.h"
#include "AbstractEWTaskbar.h"
#include "AbstractEWTaskbarPres.h"
#include "SetTopWindowInt.h"
#include "AbstractCommand.h"

///@todo:find a better way to do this. the factory is very large... Bonus point without news.
EWAppController::EWAppController(AbstractEWFactory* factory, SetTopWindowInt* topInt, std::string configPath, bool createTaskbar) :
    m_MsgHandler(NULL), m_ConfigImpl(NULL), m_Config(NULL), m_TimeHandler(NULL),
    m_PresenceHandler(NULL), m_TimeKeeper(NULL), m_ClockTimer(NULL),
    m_Presenter(NULL), m_MainFramePres(NULL), m_MainFrame(NULL),
    m_TaskBarPres(NULL), m_TaskBar(NULL), m_OptionsPres(NULL)
{
    //ctor
    try
    {
        this->m_MsgHandler = factory->createMsgHandler();
        try
        {
            this->m_ConfigImpl = factory->createConfigImpl(configPath);
            this->m_Config = factory->createConfig(m_ConfigImpl);
            ConfigData data = this->m_Config->getData();
            this->m_TimeHandler = factory->createTimeHandler();
            this->m_PresenceHandler = factory->createPresenceHandler(data.webcamIndex,
                data.cascadePath, data.faceSizeX, data.faceSizeY);
            this->m_TimeKeeper = factory->createTimeKeeper(m_TimeHandler,
                m_PresenceHandler, data.workLength, data.pauseLength, data.remFreq,
                data.checkFreq, data.pauseTol);
            this->m_CheckTimer = factory->createTimer();
            this->m_ClockTimer = factory->createTimer();
            this->m_Presenter = factory->createEWPresenter(m_MsgHandler,
                m_TimeKeeper, m_CheckTimer, m_ClockTimer, data.popupAlarm,
                data.soundAlarm, data.soundPath, data.runningLateThreshold);
            this->m_OptionsPres = factory->createOptionsDialogPres(this);
            this->m_MainFramePres = factory->createEWMainFramePres(m_Presenter, this);
            this->m_MainFrame = factory->createEWMainFrame(m_MainFramePres,
                createTaskbar && data.trayIcon);
            if (topInt != NULL)
            {
                topInt->setTopWindow(m_MainFrame);
            }
            if (createTaskbar && data.trayIcon)
            {
                this->m_TaskBarPres = factory->createEWTaskBarPres(m_Presenter);
                this->m_TaskBar = factory->createEWTaskBar(m_TaskBarPres);
            }
            this->m_DisplayOptionsDialogCmd = factory->createDisplayOptionsDialogCmd(
                this, this->m_OptionsPres);
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

EWAppController::~EWAppController()
{
    //dtor
    this->deleteFields();
}

void EWAppController::deleteFields()
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
    if (this->m_DisplayOptionsDialogCmd != NULL) delete this->m_DisplayOptionsDialogCmd;
}


bool EWAppController::saveConfig(const ConfigData& data)
{
    try
    {
        this->m_Config->save(data);

        this->m_PresenceHandler->setCascade(data.cascadePath);
        this->m_PresenceHandler->setFaceSize(data.faceSizeX, data.faceSizeY);
        this->m_PresenceHandler->setIndex(data.webcamIndex);

        this->m_TimeKeeper->setCheckFreq(data.checkFreq);
        this->m_TimeKeeper->setPauseLength(data.pauseLength);
        this->m_TimeKeeper->setPauseTol(data.pauseTol);
        this->m_TimeKeeper->setRemFreq(data.remFreq);
        this->m_TimeKeeper->setWorkLength(data.workLength);

        this->m_Presenter->setPopupAlarm(data.popupAlarm);
        this->m_Presenter->setSoundAlarm(data.soundAlarm);
        this->m_Presenter->setSoundPath(data.soundPath);
        this->m_Presenter->setRunningLateThreshold(data.runningLateThreshold);
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
        return false;
    }
    return true;
}

const ConfigData& EWAppController::getConfigData() const
{
    return this->m_Config->getData();
}

void EWAppController::displayOptionsDialog()
{
    try
    {
        this->m_DisplayOptionsDialogCmd->execute();
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
    }
}
