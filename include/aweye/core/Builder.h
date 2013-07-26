/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef BUILDER_H
#define BUILDER_H

#include "aweye/core/AbstractConfigImpl.h"
#include "aweye/core/ConfigData.h"
#include "aweye/core/SetTopWindowInt.h"

#include <memory>

namespace Aweye {

template <class T>
struct PtrTraits
{
  typedef typename std::unique_ptr<T> Ptr;
};

// factory to allow creation with differents parameters with default version
// limitation - order of creation is not garanteed
// (thinking about how to do that was interesting...)
template <class TPresenceHandler>
struct PresenceHandlerFactory
{
    template <class TBuilder>
    static TPresenceHandler* create(TBuilder& b, const ConfigData& data)
    {
        return new TPresenceHandler(data.webcamIndex, data.cascadePath,
            data.faceSizeX, data.faceSizeY);
    }
};

// this vs builder param?
template <class TPresenceHandler, class TTKController>
struct TaskExceptionLinker
{
    static void link(TPresenceHandler& p, TTKController& c)
    {
    }
};

// for testing
template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TTKController,
    class TEventHandler, class TMainFramePres, class TMainFrame, class TTaskBarPres,
    class TTaskBar, class TOptionsDialogPres, class TOptionsDialog,
    class TTKConfigObserver, class TPresHdlrConfigObserver, class TPresConfigObserver,
    class TUtils>
struct Build
{
    const TMsgHandler* m_MsgHandler;
    const TConfigImpl* m_ConfigImpl;
    const TConfig* m_Config;
    const TPresenceHandler* m_PresenceHandler;
    const TTimeHandler* m_TimeHandler;
    const TTimeKeeper* m_TimeKeeper;
    const TTimer* m_ClockTimer;
    const TTKController* m_TKController;
    const TEventHandler* m_EventHandler;
    const TMainFramePres* m_MainFramePres;
    const TMainFrame* m_MainFrame;
    const TTaskBarPres* m_TaskBarPres;
    const TTaskBar* m_TaskBar;
    const TOptionsDialogPres* m_OptionsPres;
    const std::function<bool()>* m_DisplayOptionsDialogCmd;
    const TTKConfigObserver* m_TKConfigObserver;
    const TPresHdlrConfigObserver* m_PresHdlrConfigObserver;
    const TPresConfigObserver* m_PresConfigObserver;
    const TUtils* m_Utils;
};

template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TTKController,
    class TEventHandler, class TMainFramePres, class TMainFrame, class TTaskBarPres,
    class TTaskBar, class TOptionsDialogPres, class TOptionsDialog,
    class TTKConfigObserver, class TPresHdlrConfigObserver, class TPresConfigObserver,
    class TUtils>
class Builder
{
    public:
        Builder(SetTopWindowInt* topInt, std::string configPath, bool canCreateTaskbar, int idOk) :
            m_MainFrame(nullptr)
        {
            m_MsgHandler.reset(new TMsgHandler());
            try
            {
                m_Utils.reset(new TUtils());

                m_ConfigImpl.reset(new TConfigImpl(configPath));
                m_Config.reset(new TConfig(*m_ConfigImpl, *m_Utils));
                m_OptionsPres.reset(new TOptionsDialogPres(*m_MsgHandler, *m_Config, canCreateTaskbar));

                m_DisplayOptionsDialogCmd = [&] ()
                {
                    TOptionsDialog dialog(nullptr, *m_OptionsPres);
                    return dialog.ShowModal() == idOk;
                };

                if (m_Config->hasInvalidData())
                {
                    // we tried...
                    if (!m_DisplayOptionsDialogCmd())
                    {
                        throw InvalidConfigFileException();
                    }
                }
                ConfigData data = m_Config->getData();

                m_PresenceHandler.reset(PresenceHandlerFactory<TPresenceHandler>::create(*this, data));
                m_TimeHandler.reset(new TTimeHandler());
                m_TimeKeeper.reset(new TTimeKeeper(*m_TimeHandler,
                    *m_PresenceHandler, data.workLength, data.pauseLength, data.remFreq,
                    data.checkFreq, data.pauseTol, data.workTol, data.cummulPause));

                m_ClockTimer.reset(new TTimer());
                m_TKController.reset(new TTKController(*m_MsgHandler,
                    *m_TimeKeeper, *m_ClockTimer, *m_TimeHandler, *m_Utils, data.popupAlarm,
                    data.soundAlarm, data.soundPath, data.runningLateThreshold));

                TaskExceptionLinker<TPresenceHandler,TTKController>::link(*m_PresenceHandler, *m_TKController);

                m_EventHandler.reset(new TEventHandler(*m_MsgHandler, *m_TKController, m_DisplayOptionsDialogCmd));
                m_MainFrame.reset(new TMainFrame(*m_EventHandler, *m_Utils, canCreateTaskbar && data.trayIcon));
                m_MainFramePres.reset(new TMainFramePres(*m_MainFrame, *m_TKController, *m_EventHandler));

                if (canCreateTaskbar && data.trayIcon)
                {
                    m_TaskBar.reset(new TTaskBar(*m_EventHandler));
                    m_TaskBarPres.reset(new TTaskBarPres(*m_TaskBar, *m_TKController, *m_EventHandler));
                }

                m_TKConfigObserver.reset(new TTKConfigObserver(*m_Config, *m_TimeKeeper));
                m_PresHdlrConfigObserver.reset(new TPresHdlrConfigObserver(*m_Config, *m_PresenceHandler));
                m_PresConfigObserver.reset(new TPresConfigObserver(*m_Config, *m_TKController));

                if (topInt != nullptr)
                {
                    topInt->setTopWindow(&*m_MainFrame);
                }
            }
            catch (const BaseException& e)
            {
                m_MsgHandler->displayError(e.what());
                throw;
            }
        }
        Builder(const Builder&) = delete;
        Builder& operator=(const Builder&) = delete;

        virtual ~Builder() {}
    protected:
        // for testing
        const Build<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler,
                TTimeHandler, TTimeKeeper, TTimer, TTKController, TEventHandler,
                TMainFramePres, TMainFrame, TTaskBarPres, TTaskBar,
                TOptionsDialogPres, TOptionsDialog, TTKConfigObserver,
                TPresHdlrConfigObserver, TPresConfigObserver, TUtils> getBuild()
        {
            return {&*m_MsgHandler, &*m_ConfigImpl, &*m_Config, &*m_PresenceHandler,
                &*m_TimeHandler, &*m_TimeKeeper, &*m_ClockTimer, &*m_TKController,
                &*m_EventHandler, &*m_MainFramePres, &*m_MainFrame, &*m_TaskBarPres,
                &*m_TaskBar, &*m_OptionsPres, &m_DisplayOptionsDialogCmd,
                &*m_TKConfigObserver, &*m_PresHdlrConfigObserver, &*m_PresConfigObserver,
                &*m_Utils};
        }

    private:
        friend class PresenceHandlerFactory<TPresenceHandler>;

        typedef class PtrTraits<TMsgHandler>::Ptr TMsgHandlerPtr;
        typedef class PtrTraits<TConfigImpl>::Ptr TConfigImplPtr;
        typedef class PtrTraits<TConfig>::Ptr TConfigPtr;
        typedef class PtrTraits<TPresenceHandler>::Ptr TPresenceHandlerPtr;
        typedef class PtrTraits<TTimeHandler>::Ptr TTimeHandlerPtr;
        typedef class PtrTraits<TTimeKeeper>::Ptr TTimeKeeperPtr;
        typedef class PtrTraits<TTimer>::Ptr TTimerPtr;
        typedef class PtrTraits<TTKController>::Ptr TTKControllerPtr;
        typedef class PtrTraits<TEventHandler>::Ptr TEventHandlerPtr;
        typedef class PtrTraits<TMainFramePres>::Ptr TMainFramePresPtr;
        typedef class PtrTraits<TMainFrame>::Ptr TMainFramePtr;
        typedef class PtrTraits<TTaskBarPres>::Ptr TTaskBarPresPtr;
        typedef class PtrTraits<TTaskBar>::Ptr TTaskBarPtr;
        typedef class PtrTraits<TOptionsDialogPres>::Ptr TOptionsDialogPresPtr;
        typedef class PtrTraits<TTKConfigObserver>::Ptr TTKConfigObserverPtr;
        typedef class PtrTraits<TPresHdlrConfigObserver>::Ptr TPresHdlrConfigObserverPtr;
        typedef class PtrTraits<TPresConfigObserver>::Ptr TPresConfigObserverPtr;
        typedef class PtrTraits<TUtils>::Ptr TUtilsPtr;

        TMsgHandlerPtr m_MsgHandler;
        TConfigImplPtr m_ConfigImpl;
        TConfigPtr m_Config;
        TPresenceHandlerPtr m_PresenceHandler;
        TTimeHandlerPtr m_TimeHandler;
        TTimeKeeperPtr m_TimeKeeper;
        TTimerPtr m_ClockTimer;
        TTKControllerPtr m_TKController;
        TEventHandlerPtr m_EventHandler;
        TMainFramePresPtr m_MainFramePres;
        TMainFramePtr m_MainFrame;
        TTaskBarPresPtr m_TaskBarPres;
        TTaskBarPtr m_TaskBar;
        TOptionsDialogPresPtr m_OptionsPres;
        std::function<bool()> m_DisplayOptionsDialogCmd;
        TTKConfigObserverPtr m_TKConfigObserver;
        TPresHdlrConfigObserverPtr m_PresHdlrConfigObserver;
        TPresConfigObserverPtr m_PresConfigObserver;
        TUtilsPtr m_Utils;
};
}

#endif // BUILDER_H
