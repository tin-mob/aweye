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

#include <memory>

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

/// @todo we know that TEWMainFrame is managed by wx;
/// remove this knowledge

// for testing
template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWAppController,
    class TEWPresenter, class TEWMainFramePres, class TEWMainFrame, class TEWTaskbarPres,
    class TEWTaskbar, class TOptionsDialogPres, class TBuilderOptionsDialogPres, class TDisplayOptionsDialogCmd>
struct EWBuild
{
    const TMsgHandler* m_MsgHandler;
    const TConfigImpl* m_ConfigImpl;
    const TConfig* m_Config;
    const TPresenceHandler* m_PresenceHandler;
    const TTimeHandler* m_TimeHandler;
    const TTimeKeeper* m_TimeKeeper;
    const TTimer* m_CheckTimer;
    const TTimer* m_ClockTimer;
    const TEWAppController* m_AppController;
    const TEWPresenter* m_Presenter;
    const TEWMainFramePres* m_MainFramePres;
    const TEWMainFrame* m_MainFrame; // managed by wx
    const TEWTaskbarPres* m_TaskBarPres;
    const TEWTaskbar* m_TaskBar;
    const TOptionsDialogPres* m_OptionsPres;
    const TDisplayOptionsDialogCmd* m_DisplayOptionsDialogCmd;
};

template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWAppController,
    class TEWPresenter, class TEWMainFramePres, class TEWMainFrame, class TEWTaskbarPres,
    class TEWTaskbar, class TOptionsDialogPres, class TBuilderOptionsDialogPres, class TDisplayOptionsDialogCmd>
class EWBuilder
{
    public:
        EWBuilder(SetTopWindowInt* topInt, std::string configPath, bool canCreateTaskbar) :
            m_MainFrame(nullptr)
        {
            m_MsgHandler.reset(new TMsgHandler());
            try
            {
                m_ConfigImpl.reset(new TConfigImpl(configPath));
                m_Config.reset(new TConfig(*m_ConfigImpl));
                if (m_Config->hasInvalidData())
                {
                    TBuilderOptionsDialogPres pres(*m_Config, *m_MsgHandler, canCreateTaskbar);
                    TDisplayOptionsDialogCmd cmd(pres);

                    // we tried...
                    if (!cmd.execute())
                    {
                        throw InvalidConfigFileException();
                    }
                }
                ConfigData data = m_Config->getData();

                m_PresenceHandler.reset(new TPresenceHandler(data.webcamIndex, data.cascadePath,
                    data.faceSizeX, data.faceSizeY));
                m_TimeHandler.reset(new TTimeHandler());
                m_TimeKeeper.reset(new TTimeKeeper(*m_TimeHandler,
                    *m_PresenceHandler, data.workLength, data.pauseLength, data.remFreq,
                    data.checkFreq, data.pauseTol, data.workTol, data.cummulPause));

                m_CheckTimer.reset(new TTimer());
                m_ClockTimer.reset(new TTimer());
                m_AppController.reset(new TEWAppController(canCreateTaskbar));
                m_Presenter.reset(new TEWPresenter(*m_MsgHandler,
                    *m_TimeKeeper, *m_CheckTimer, *m_ClockTimer, *m_TimeHandler, data.popupAlarm,
                    data.soundAlarm, data.soundPath, data.runningLateThreshold));

                m_MainFramePres.reset(new TEWMainFramePres(*m_Presenter, *m_AppController));
                m_MainFrame = new TEWMainFrame(*m_MainFramePres, canCreateTaskbar && data.trayIcon);

                if (canCreateTaskbar && data.trayIcon)
                {
                    m_TaskBarPres.reset(new TEWTaskbarPres(*m_Presenter, *m_AppController));
                    m_TaskBar.reset(new TEWTaskbar(*m_TaskBarPres));
                }
                m_OptionsPres.reset(new TOptionsDialogPres(*m_AppController));
                m_DisplayOptionsDialogCmd.reset(new TDisplayOptionsDialogCmd(
                    *m_OptionsPres));

                m_AppController->link(&*m_MsgHandler, &*m_Config, &*m_PresenceHandler,
                    &*m_TimeKeeper, &*m_Presenter, &*m_DisplayOptionsDialogCmd);

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
        virtual ~EWBuilder() {}
    protected:
        // for testing
        EWBuild<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler,
                TTimeHandler, TTimeKeeper, TTimer, TEWAppController, TEWPresenter, TEWMainFramePres,
                TEWMainFrame, TEWTaskbarPres, TEWTaskbar, TOptionsDialogPres,
                TBuilderOptionsDialogPres, TDisplayOptionsDialogCmd> getBuild()
        {
            return {&*m_MsgHandler, &*m_ConfigImpl, &*m_Config, &*m_PresenceHandler,
                &*m_TimeHandler, &*m_TimeKeeper, &*m_CheckTimer, &*m_ClockTimer,
                &*m_AppController, &*m_Presenter, &*m_MainFramePres, m_MainFrame,
                &*m_TaskBarPres, &*m_TaskBar, &*m_OptionsPres, &*m_DisplayOptionsDialogCmd};
        }
    private:
        std::unique_ptr<TMsgHandler> m_MsgHandler;
        std::unique_ptr<TConfigImpl> m_ConfigImpl;
        std::unique_ptr<TConfig> m_Config;
        std::unique_ptr<TPresenceHandler> m_PresenceHandler;
        std::unique_ptr<TTimeHandler> m_TimeHandler;
        std::unique_ptr<TTimeKeeper> m_TimeKeeper;
        std::unique_ptr<TTimer> m_CheckTimer;
        std::unique_ptr<TTimer> m_ClockTimer;
        std::unique_ptr<TEWAppController> m_AppController;
        std::unique_ptr<TEWPresenter> m_Presenter;
        std::unique_ptr<TEWMainFramePres> m_MainFramePres;
        TEWMainFrame* m_MainFrame; // managed by wx
        std::unique_ptr<TEWTaskbarPres> m_TaskBarPres;
        std::unique_ptr<TEWTaskbar> m_TaskBar;
        std::unique_ptr<TOptionsDialogPres> m_OptionsPres;
        std::unique_ptr<TDisplayOptionsDialogCmd> m_DisplayOptionsDialogCmd;
};

#endif // EWBUILDER_H
