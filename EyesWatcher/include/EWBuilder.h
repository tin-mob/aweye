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

#include "AbstractConfigImpl.h"
#include "ConfigData.h"
#include "BaseException.h"
#include "SetTopWindowInt.h"

template <class T>
struct PtrTraits
{
  typedef typename std::unique_ptr<T> Ptr;
};

// for testing
template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWPresenter,
    class TEventHandler, class TEWMainFramePres, class TEWMainFrame, class TEWTaskbarPres,
    class TEWTaskbar, class TOptionsDialogPres, class TOptionsDialog,
    class TTKConfigObserver, class TPresHdlrConfigObserver, class TEWPresConfigObserver>
struct EWBuild
{
    const TMsgHandler* m_MsgHandler;
    const TConfigImpl* m_ConfigImpl;
    const TConfig* m_Config;
    const TPresenceHandler* m_PresenceHandler;
    const TTimeHandler* m_TimeHandler;
    const TTimeKeeper* m_TimeKeeper;
    const TTimer* m_ClockTimer;
    const TEWPresenter* m_Presenter;
    const TEventHandler* m_EventHandler;
    const TEWMainFramePres* m_MainFramePres;
    const TEWMainFrame* m_MainFrame;
    const TEWTaskbarPres* m_TaskBarPres;
    const TEWTaskbar* m_TaskBar;
    const TOptionsDialogPres* m_OptionsPres;
    const std::function<bool()>* m_DisplayOptionsDialogCmd;
    const TTKConfigObserver* m_TKConfigObserver;
    const TPresHdlrConfigObserver* m_PresHdlrConfigObserver;
    const TEWPresConfigObserver* m_EWPresConfigObserver;
};

template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWPresenter,
    class TEventHandler, class TEWMainFramePres, class TEWMainFrame, class TEWTaskbarPres,
    class TEWTaskbar, class TOptionsDialogPres, class TOptionsDialog,
    class TTKConfigObserver, class TPresHdlrConfigObserver, class TEWPresConfigObserver>
class EWBuilder
{
    public:
        EWBuilder(SetTopWindowInt* topInt, std::string configPath, bool canCreateTaskbar, int idOk) :
            m_MainFrame(nullptr)
        {
            m_MsgHandler.reset(new TMsgHandler());
            try
            {
                m_ConfigImpl.reset(new TConfigImpl(configPath));
                m_Config.reset(new TConfig(*m_ConfigImpl));
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

                m_PresenceHandler.reset(new TPresenceHandler(data.webcamIndex, data.cascadePath,
                    data.faceSizeX, data.faceSizeY));
                m_TimeHandler.reset(new TTimeHandler());
                m_TimeKeeper.reset(new TTimeKeeper(*m_TimeHandler,
                    *m_PresenceHandler, data.workLength, data.pauseLength, data.remFreq,
                    data.checkFreq, data.pauseTol, data.workTol, data.cummulPause));

                m_ClockTimer.reset(new TTimer());
                m_Presenter.reset(new TEWPresenter(*m_MsgHandler,
                    *m_TimeKeeper, *m_ClockTimer, *m_TimeHandler, data.popupAlarm,
                    data.soundAlarm, data.soundPath, data.runningLateThreshold));

                m_EventHandler.reset(new TEventHandler(*m_MsgHandler, *m_Presenter, m_DisplayOptionsDialogCmd));
                m_MainFrame.reset(new TEWMainFrame(*m_EventHandler, canCreateTaskbar && data.trayIcon));
                m_MainFramePres.reset(new TEWMainFramePres(*m_MainFrame, *m_Presenter, *m_EventHandler));

                if (canCreateTaskbar && data.trayIcon)
                {
                    m_TaskBar.reset(new TEWTaskbar(*m_EventHandler));
                    m_TaskBarPres.reset(new TEWTaskbarPres(*m_TaskBar, *m_Presenter, *m_EventHandler));
                }

                m_TKConfigObserver.reset(new TTKConfigObserver(*m_Config, *m_TimeKeeper));
                m_PresHdlrConfigObserver.reset(new TPresHdlrConfigObserver(*m_Config, *m_PresenceHandler));
                m_EWPresConfigObserver.reset(new TEWPresConfigObserver(*m_Config, *m_Presenter));

                if (topInt != nullptr)
                {
                    topInt->setTopWindow(&*m_MainFrame);
                }
            }
            catch (BaseException e)
            {
                m_MsgHandler->displayError(e.what());
                throw;
            }
        }
        EWBuilder(const EWBuilder&) = delete;
        EWBuilder& operator=(const EWBuilder&) = delete;

        virtual ~EWBuilder() {}
    protected:
        // for testing
        const EWBuild<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler,
                TTimeHandler, TTimeKeeper, TTimer, TEWPresenter, TEventHandler,
                TEWMainFramePres, TEWMainFrame, TEWTaskbarPres, TEWTaskbar,
                TOptionsDialogPres, TOptionsDialog, TTKConfigObserver,
                TPresHdlrConfigObserver, TEWPresConfigObserver> getBuild()
        {
            return {&*m_MsgHandler, &*m_ConfigImpl, &*m_Config, &*m_PresenceHandler,
                &*m_TimeHandler, &*m_TimeKeeper, &*m_ClockTimer, &*m_Presenter,
                &*m_EventHandler, &*m_MainFramePres, &*m_MainFrame, &*m_TaskBarPres,
                &*m_TaskBar, &*m_OptionsPres, &m_DisplayOptionsDialogCmd,
                &*m_TKConfigObserver, &*m_PresHdlrConfigObserver, &*m_EWPresConfigObserver};
        }

    private:
        typedef class PtrTraits<TMsgHandler>::Ptr TMsgHandlerPtr;
        typedef class PtrTraits<TConfigImpl>::Ptr TConfigImplPtr;
        typedef class PtrTraits<TConfig>::Ptr TConfigPtr;
        typedef class PtrTraits<TPresenceHandler>::Ptr TPresenceHandlerPtr;
        typedef class PtrTraits<TTimeHandler>::Ptr TTimeHandlerPtr;
        typedef class PtrTraits<TTimeKeeper>::Ptr TTimeKeeperPtr;
        typedef class PtrTraits<TTimer>::Ptr TTimerPtr;
        typedef class PtrTraits<TEWPresenter>::Ptr TEWPresenterPtr;
        typedef class PtrTraits<TEventHandler>::Ptr TEventHandlerPtr;
        typedef class PtrTraits<TEWMainFramePres>::Ptr TEWMainFramePresPtr;
        typedef class PtrTraits<TEWMainFrame>::Ptr TEWMainFramePtr;
        typedef class PtrTraits<TEWTaskbarPres>::Ptr TEWTaskbarPresPtr;
        typedef class PtrTraits<TEWTaskbar>::Ptr TEWTaskbarPtr;
        typedef class PtrTraits<TOptionsDialogPres>::Ptr TOptionsDialogPresPtr;
        typedef class PtrTraits<TTKConfigObserver>::Ptr TTKConfigObserverPtr;
        typedef class PtrTraits<TPresHdlrConfigObserver>::Ptr TPresHdlrConfigObserverPtr;
        typedef class PtrTraits<TEWPresConfigObserver>::Ptr TEWPresConfigObserverPtr;

        TMsgHandlerPtr m_MsgHandler;
        TConfigImplPtr m_ConfigImpl;
        TConfigPtr m_Config;
        TPresenceHandlerPtr m_PresenceHandler;
        TTimeHandlerPtr m_TimeHandler;
        TTimeKeeperPtr m_TimeKeeper;
        TTimerPtr m_ClockTimer;
        TEWPresenterPtr m_Presenter;
        TEventHandlerPtr m_EventHandler;
        TEWMainFramePresPtr m_MainFramePres;
        TEWMainFramePtr m_MainFrame;
        TEWTaskbarPresPtr m_TaskBarPres;
        TEWTaskbarPtr m_TaskBar;
        TOptionsDialogPresPtr m_OptionsPres;
        std::function<bool()> m_DisplayOptionsDialogCmd;
        TTKConfigObserverPtr m_TKConfigObserver;
        TPresHdlrConfigObserverPtr m_PresHdlrConfigObserver;
        TEWPresConfigObserverPtr m_EWPresConfigObserver;
};

#endif // EWBUILDER_H
