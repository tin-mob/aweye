/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


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
            m_MsgHandler(nullptr), m_ConfigImpl(nullptr), m_Config(nullptr), m_PresenceHandler(nullptr),
            m_TimeHandler(nullptr), m_TimeKeeper(nullptr), m_CheckTimer(nullptr), m_ClockTimer(nullptr),
            m_AppController(nullptr), m_Presenter(nullptr), m_MainFramePres(nullptr), m_MainFrame(nullptr),
            m_OptionsPres(nullptr), m_TaskBarPres(nullptr), m_TaskBar(nullptr),
            m_DisplayOptionsDialogCmd(nullptr)
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

                    this->m_MainFramePres = new TEWMainFramePres(m_Presenter, m_AppController);
                    this->m_MainFrame = new TEWMainFrame(m_MainFramePres, canCreateTaskbar && data.trayIcon);

                    if (canCreateTaskbar && data.trayIcon)
                    {
                        this->m_TaskBarPres = new TEWTaskbarPres(m_Presenter, m_AppController);
                        this->m_TaskBar = new TEWTaskbar(m_TaskBarPres);
                    }
                    this->m_OptionsPres = new TOptionsDialogPres(m_AppController);
                    this->m_DisplayOptionsDialogCmd = new TDisplayOptionsDialogCmd(
                        this->m_OptionsPres);

                    tmpAppCtrl->link(m_MsgHandler, m_Config,
                        m_PresenceHandler, m_TimeKeeper, m_Presenter,
                        m_DisplayOptionsDialogCmd);

                    if (topInt != nullptr)
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
        TMsgHandler* m_MsgHandler;
        TConfigImpl* m_ConfigImpl;
        TConfig* m_Config;
        TPresenceHandler* m_PresenceHandler;
        TTimeHandler* m_TimeHandler;
        TTimeKeeper* m_TimeKeeper;
        TTimer* m_CheckTimer;
        TTimer* m_ClockTimer;
        TEWAppController* m_AppController;
        TEWPresenter* m_Presenter;
        TEWMainFramePres* m_MainFramePres;
        TEWMainFrame* m_MainFrame;
        TOptionsDialogPres* m_OptionsPres;
        TEWTaskbarPres* m_TaskBarPres;
        TEWTaskbar* m_TaskBar;
        TDisplayOptionsDialogCmd* m_DisplayOptionsDialogCmd;
    private:
        void deleteFields()
        {
            if (this->m_MsgHandler != nullptr) delete this->m_MsgHandler;
            if (this->m_ConfigImpl != nullptr) delete this->m_ConfigImpl;
            if (this->m_Config != nullptr) delete this->m_Config;
            if (this->m_PresenceHandler != nullptr) delete this->m_PresenceHandler;
            if (this->m_TimeHandler != nullptr) delete this->m_TimeHandler;
            if (this->m_TimeKeeper != nullptr) delete this->m_TimeKeeper;
            if (this->m_CheckTimer != nullptr) delete this->m_CheckTimer;
            if (this->m_ClockTimer != nullptr) delete this->m_ClockTimer;
            if (this->m_AppController != nullptr) delete this->m_AppController;
            if (this->m_Presenter != nullptr) delete this->m_Presenter;
            if (this->m_MainFramePres != nullptr) delete this->m_MainFramePres;
            // since m_MainFrame inherits from wxFrame, it is deleted by wx, not by us
            if (this->m_OptionsPres != nullptr) delete this->m_OptionsPres;
            if (this->m_TaskBarPres != nullptr) delete this->m_TaskBarPres;
            if (this->m_TaskBar != nullptr) delete this->m_TaskBar;
            if (this->m_DisplayOptionsDialogCmd != nullptr) delete this->m_DisplayOptionsDialogCmd;
        }
};

#endif // EWBUILDER_H
