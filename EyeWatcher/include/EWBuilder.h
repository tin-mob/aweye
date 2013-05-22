#ifndef EWBUILDER_H
#define EWBUILDER_H

#include "ConfigData.h"
#include "BaseException.h"

#include "AbstractMsgHandler.h"
#include "AbstractConfigImpl.h"
#include "AbstractConfig.h"
#include "AbstractPresenceHandler.h"
#include "AbstractTimeHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractTimer.h"
#include "AbstractEWAppController.h"
#include "AbstractEWPresenter.h"
#include "AbstractEWViewPres.h"
#include "AbstractEWMainFrame.h"
#include "AbstractOptionsDialogPres.h"
#include "AbstractEWTaskbar.h"
#include "SetTopWindowInt.h"
#include "AbstractCommand.h"

/// @todo: look to remove news
template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWAppController, class TEWPresenter,
    class TEWMainFramePres, class TEWMainFrame, class TOptionsDialogPres, class TEWTaskbarPres,
    class TEWTaskbar, class TDisplayOptionsDialogCmd>
class EWBuilder
{
    public:
        EWBuilder(SetTopWindowInt* topInt, std::string configPath, bool canCreateTaskbar) :
            m_MsgHandler(NULL), m_ConfigImpl(NULL), m_Config(NULL), m_PresenceHandler(NULL),
            m_TimeHandler(NULL), m_TimeKeeper(NULL), m_CheckTimer(NULL), m_ClockTimer(NULL),
            m_AppController(NULL), m_Presenter(NULL), m_MainFramePres(NULL), m_MainFrame(NULL),
            m_OptionsPres(NULL), m_TaskBarPres(NULL), m_TaskBar(NULL),
            m_DisplayOptionsDialogCmd(NULL)
        {
            //ctor
            try
            {
                this->m_MsgHandler = new TMsgHandler();
                try
                {
                    this->m_ConfigImpl = new TConfigImpl(configPath);
                    this->m_Config = new TConfig(m_ConfigImpl);
                    ConfigData data = this->m_Config->getData();

                    this->m_PresenceHandler = new TPresenceHandler(data.webcamIndex, data.cascadePath,
                        data.faceSizeX, data.faceSizeY);
                    this->m_TimeHandler = new TTimeHandler();
                    this->m_TimeKeeper = new TTimeKeeper(m_TimeHandler,
                        m_PresenceHandler, data.workLength, data.pauseLength, data.remFreq,
                        data.checkFreq, data.pauseTol);

                    this->m_CheckTimer = new TTimer();
                    this->m_ClockTimer = new TTimer();
                    TEWAppController* tmpAppCtrl = new TEWAppController();
                    this->m_AppController = tmpAppCtrl;
                    this->m_Presenter = new TEWPresenter(m_MsgHandler,
                        m_TimeKeeper, m_CheckTimer, m_ClockTimer, data.popupAlarm,
                        data.soundAlarm, data.soundPath, data.runningLateThreshold);

                    TEWMainFramePres* tmpMainFramePres = new TEWMainFramePres(m_Presenter, m_AppController);
                    this->m_MainFramePres = tmpMainFramePres;
                    this->m_MainFrame = new TEWMainFrame(NULL, m_MainFramePres, canCreateTaskbar && data.trayIcon);
                    tmpMainFramePres->attachFrame(m_MainFrame);

                    if (canCreateTaskbar && data.trayIcon)
                    {
                        TEWTaskbarPres* tmpTaskBarPres = new TEWTaskbarPres(m_Presenter, m_AppController);
                        this->m_TaskBarPres = tmpTaskBarPres;
                        this->m_TaskBar = new TEWTaskbar(m_TaskBarPres);
                        tmpTaskBarPres->attachTaskBar(m_TaskBar);
                    }
                    this->m_OptionsPres = new TOptionsDialogPres(m_AppController);
                    this->m_DisplayOptionsDialogCmd = new TDisplayOptionsDialogCmd(
                        m_AppController, this->m_OptionsPres);

                    tmpAppCtrl->link(m_MsgHandler, m_Config,
                        m_PresenceHandler, m_TimeKeeper, m_Presenter,
                        m_DisplayOptionsDialogCmd);

                    if (topInt != NULL)
                    {
                        topInt->setTopWindow(m_MainFrame);
                    }
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
        virtual ~EWBuilder() {}
    protected:
    private:
        void deleteFields()
        {
            if (this->m_MsgHandler != NULL) delete this->m_MsgHandler;
            if (this->m_ConfigImpl != NULL) delete this->m_ConfigImpl;
            if (this->m_Config != NULL) delete this->m_Config;
            if (this->m_PresenceHandler != NULL) delete this->m_PresenceHandler;
            if (this->m_TimeHandler != NULL) delete this->m_TimeHandler;
            if (this->m_TimeKeeper != NULL) delete this->m_TimeKeeper;
            if (this->m_CheckTimer != NULL) delete this->m_CheckTimer;
            if (this->m_ClockTimer != NULL) delete this->m_ClockTimer;
            if (this->m_AppController != NULL) delete this->m_AppController;
            if (this->m_Presenter != NULL) delete this->m_Presenter;
            if (this->m_MainFramePres != NULL) delete this->m_MainFramePres;
            // since m_MainFrame inherits from wxFrame, it is deleted by wx, not by us
            if (this->m_OptionsPres != NULL) delete this->m_OptionsPres;
            if (this->m_TaskBarPres != NULL) delete this->m_TaskBarPres;
            if (this->m_TaskBar != NULL) delete this->m_TaskBar;
            if (this->m_DisplayOptionsDialogCmd != NULL) delete this->m_DisplayOptionsDialogCmd;
        }

        AbstractMsgHandler* m_MsgHandler;
        AbstractConfigImpl* m_ConfigImpl;
        AbstractConfig* m_Config;
        AbstractPresenceHandler* m_PresenceHandler;
        AbstractTimeHandler* m_TimeHandler;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractTimer* m_CheckTimer;
        AbstractTimer* m_ClockTimer;
        AbstractEWAppController* m_AppController;
        AbstractEWPresenter* m_Presenter;
        AbstractEWViewPres* m_MainFramePres;
        AbstractEWMainFrame* m_MainFrame;
        AbstractOptionsDialogPres* m_OptionsPres;
        AbstractEWViewPres* m_TaskBarPres;
        AbstractEWTaskbar* m_TaskBar;
        AbstractCommand* m_DisplayOptionsDialogCmd;
};

#endif // EWBUILDER_H
