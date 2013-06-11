/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

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

/// @todo look to remove news (unique_ptr), no protected variables
template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWAppController,
    class TEWPresenter, class TEWMainFramePres, class TEWMainFrame, class TEWTaskbarPres,
    class TEWTaskbar, class TOptionsDialogPres, class TBuilderOptionsDialogPres, class TDisplayOptionsDialogCmd>
class EWBuilder
{
    public:
        EWBuilder(SetTopWindowInt* topInt, std::string configPath, bool canCreateTaskbar) :
            m_MsgHandler(nullptr), m_ConfigImpl(nullptr), m_Config(nullptr), m_PresenceHandler(nullptr),
            m_TimeHandler(nullptr), m_TimeKeeper(nullptr), m_CheckTimer(nullptr), m_ClockTimer(nullptr),
            m_AppController(nullptr), m_Presenter(nullptr), m_MainFramePres(nullptr), m_MainFrame(nullptr),
            m_TaskBarPres(nullptr), m_TaskBar(nullptr), m_OptionsPres(nullptr), m_DisplayOptionsDialogCmd(nullptr)
        {
            //ctor
            try
            {
                m_MsgHandler = new TMsgHandler();
                try
                {
                    m_ConfigImpl = new TConfigImpl(configPath);
                    m_Config = new TConfig(m_ConfigImpl);
                    if (m_Config->hasInvalidData())
                    {
                        TBuilderOptionsDialogPres pres(m_Config, m_MsgHandler, canCreateTaskbar);
                        TDisplayOptionsDialogCmd cmd(&pres);

                        // we tried...
                        if (!cmd.execute())
                        {
                            throw InvalidConfigFileException();
                        }
                    }
                    ConfigData data = m_Config->getData();

                    m_PresenceHandler = new TPresenceHandler(data.webcamIndex, data.cascadePath,
                        data.faceSizeX, data.faceSizeY);
                    m_TimeHandler = new TTimeHandler();
                    m_TimeKeeper = new TTimeKeeper(m_TimeHandler,
                        m_PresenceHandler, data.workLength, data.pauseLength, data.remFreq,
                        data.checkFreq, data.pauseTol, data.workTol, data.cummulPause);

                    m_CheckTimer = new TTimer();
                    m_ClockTimer = new TTimer();
                    TEWAppController* tmpAppCtrl = new TEWAppController(canCreateTaskbar);
                    m_AppController = tmpAppCtrl;
                    m_Presenter = new TEWPresenter(m_MsgHandler,
                        m_TimeKeeper, m_CheckTimer, m_ClockTimer, m_TimeHandler, data.popupAlarm,
                        data.soundAlarm, data.soundPath, data.runningLateThreshold);

                    m_MainFramePres = new TEWMainFramePres(m_Presenter, m_AppController);
                    m_MainFrame = new TEWMainFrame(m_MainFramePres, canCreateTaskbar && data.trayIcon);

                    if (canCreateTaskbar && data.trayIcon)
                    {
                        m_TaskBarPres = new TEWTaskbarPres(m_Presenter, m_AppController);
                        m_TaskBar = new TEWTaskbar(m_TaskBarPres);
                    }
                    m_OptionsPres = new TOptionsDialogPres(m_AppController);
                    m_DisplayOptionsDialogCmd = new TDisplayOptionsDialogCmd(
                        m_OptionsPres);

                    tmpAppCtrl->link(m_MsgHandler, m_Config, m_PresenceHandler,
                        m_TimeKeeper, m_Presenter, m_DisplayOptionsDialogCmd);

                    if (topInt != nullptr)
                    {
                        topInt->setTopWindow(m_MainFrame);
                    }
                }
                catch (BaseException e)
                {
                    m_MsgHandler->displayError(e.what());
                    throw;
                }
            }
            catch (...)
            {
               deleteFields();
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
        TEWTaskbarPres* m_TaskBarPres;
        TEWTaskbar* m_TaskBar;
        TOptionsDialogPres* m_OptionsPres;
        TDisplayOptionsDialogCmd* m_DisplayOptionsDialogCmd;
    private:
        void deleteFields()
        {
            if (m_MsgHandler != nullptr) delete m_MsgHandler;
            if (m_ConfigImpl != nullptr) delete m_ConfigImpl;
            if (m_Config != nullptr) delete m_Config;
            if (m_PresenceHandler != nullptr) delete m_PresenceHandler;
            if (m_TimeHandler != nullptr) delete m_TimeHandler;
            if (m_TimeKeeper != nullptr) delete m_TimeKeeper;
            if (m_CheckTimer != nullptr) delete m_CheckTimer;
            if (m_ClockTimer != nullptr) delete m_ClockTimer;
            if (m_AppController != nullptr) delete m_AppController;
            if (m_Presenter != nullptr) delete m_Presenter;
            if (m_MainFramePres != nullptr) delete m_MainFramePres;
            // since m_MainFrame inherits from wxFrame, it is deleted by wx, not by us
            if (m_TaskBarPres != nullptr) delete m_TaskBarPres;
            if (m_TaskBar != nullptr) delete m_TaskBar;
            if (m_OptionsPres != nullptr) delete m_OptionsPres;
            if (m_DisplayOptionsDialogCmd != nullptr) delete m_DisplayOptionsDialogCmd;
        }
};

#endif // EWBUILDER_H
