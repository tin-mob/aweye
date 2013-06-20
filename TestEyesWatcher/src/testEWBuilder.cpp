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
///@todo test no taskbar

#include <unittest++/UnitTest++.h>
#include <memory>

#include "MsgHandlerStub.h"
#include "ConfigImplStub.h"
#include "ConfigStub.h"
#include "PresenceHandlerStub.h"
#include "TimeHandlerStub.h"
#include "TimeKeeperStub.h"
#include "TimerStub.h"
#include "EWPresenterStub.h"
#include "EWViewPresStub.h"
#include "EWMainFrameStub.h"
#include "OptionsDialogPresStub.h"
#include "EWTaskbarStub.h"
#include "OptionsDialogStub.h"
#include "EWTestBuilder.h"
#include "SetTopWindowStub.h"
#include "ConfigObserverStubs.h"
#include "EventHandlerStub.h"

struct EWBuilderFixture
{
    EWBuilderFixture() : path("path") {}
    ~EWBuilderFixture() {}

    SetTopWindowStub setTop;
    std::string path;
};

SUITE(TestEWBuilder)
{
    TEST_FIXTURE(EWBuilderFixture, TestBuild)
    {
        const EWTestBuilder<MsgHandlerStub, ConfigImplStub, ConfigStub, PresenceHandlerStub,
            TimeHandlerStub, TimeKeeperStub, TimerStub, EWPresenterStub, EventHandlerStub,
            EWViewPresStub<AbstractEWMainFrame>, EWMainFrameStub, EWViewPresStub<AbstractEWTaskbar>,
            EWTaskbarStub, OptionsDialogPresStub, OptionsDialogStub, TKConfigObserverStub,
            PresHdlrConfigObserverStub, EWPresConfigObserverStub> builder(&setTop, path, true, OptionsDialogStub::IdOK);

        CHECK_EQUAL(false, builder.links.m_MsgHandler == nullptr);
        CHECK_EQUAL(false, builder.links.m_ConfigImpl == nullptr);
        CHECK_EQUAL(false, builder.links.m_Config == nullptr);
        CHECK_EQUAL(false, builder.links.m_PresenceHandler == nullptr);
        CHECK_EQUAL(false, builder.links.m_TimeHandler == nullptr);
        CHECK_EQUAL(false, builder.links.m_TimeKeeper == nullptr);
        CHECK_EQUAL(false, builder.links.m_ClockTimer == nullptr);
        CHECK_EQUAL(false, builder.links.m_Presenter == nullptr);
        CHECK_EQUAL(false, builder.links.m_MainFramePres == nullptr);
        CHECK_EQUAL(false, builder.links.m_MainFrame == nullptr);
        CHECK_EQUAL(false, builder.links.m_OptionsPres == nullptr);
        CHECK_EQUAL(false, builder.links.m_TaskBarPres == nullptr);
        CHECK_EQUAL(false, builder.links.m_TaskBar == nullptr);
        CHECK_EQUAL(false, builder.links.m_DisplayOptionsDialogCmd == nullptr);

        CHECK_EQUAL(path, builder.links.m_ConfigImpl->m_Path);
        CHECK_EQUAL(builder.links.m_Config->m_Impl, builder.links.m_ConfigImpl);

        ConfigData data = builder.links.m_Config->getData();
        CHECK_EQUAL(data.cascadePath, builder.links.m_PresenceHandler->m_CascadePath);
        CHECK_EQUAL(data.webcamIndex, builder.links.m_PresenceHandler->m_WebcamIndex);
        CHECK_EQUAL(data.faceSizeX, builder.links.m_PresenceHandler->m_FaceSizeX);
        CHECK_EQUAL(data.faceSizeY, builder.links.m_PresenceHandler->m_FaceSizeY);

        CHECK_EQUAL(builder.links.m_TimeHandler, builder.links.m_TimeKeeper->m_TimeHandler);
        CHECK_EQUAL(builder.links.m_PresenceHandler, builder.links.m_TimeKeeper->m_PresenceHandler);

        CHECK_EQUAL(data.workLength, builder.links.m_TimeKeeper->m_WorkLength);
        CHECK_EQUAL(data.pauseLength, builder.links.m_TimeKeeper->m_PauseLength);
        CHECK_EQUAL(data.remFreq, builder.links.m_TimeKeeper->m_RemFreq);
        CHECK_EQUAL(data.checkFreq, builder.links.m_TimeKeeper->m_CheckFreq);
        CHECK_EQUAL(data.pauseTol, builder.links.m_TimeKeeper->m_PauseTol);
        CHECK_EQUAL(data.workTol, builder.links.m_TimeKeeper->m_WorkTol);

        CHECK_EQUAL(builder.links.m_MsgHandler, builder.links.m_Presenter->m_MsgHandler);
        CHECK_EQUAL(builder.links.m_TimeKeeper, builder.links.m_Presenter->m_Keeper);
        CHECK_EQUAL(builder.links.m_ClockTimer, builder.links.m_Presenter->m_ClockTimer);
        CHECK_EQUAL(builder.links.m_TimeHandler, builder.links.m_Presenter->m_TimeHandler);

        CHECK_EQUAL(data.popupAlarm, builder.links.m_Presenter->m_PopupAlarm);
        CHECK_EQUAL(data.soundAlarm, builder.links.m_Presenter->m_SoundAlarm);
        CHECK_EQUAL(data.soundPath, builder.links.m_Presenter->m_SoundPath);
        CHECK_EQUAL(data.runningLateThreshold, builder.links.m_Presenter->m_RunningLateThreshold);

        CHECK_EQUAL(builder.links.m_MsgHandler, builder.links.m_EventHandler->m_MsgHandler);
        CHECK_EQUAL(builder.links.m_Presenter, builder.links.m_EventHandler->m_Presenter);
        CHECK_EQUAL(builder.links.m_DisplayOptionsDialogCmd, builder.links.m_EventHandler->m_DisplayOptionsDialog);

        CHECK_EQUAL(builder.links.m_EventHandler, builder.links.m_MainFrame->m_EventHandler);
        CHECK_EQUAL(true, builder.links.m_MainFrame->m_TaskbarCreated);

        CHECK_EQUAL(builder.links.m_MainFrame, builder.links.m_MainFramePres->m_View);
        CHECK_EQUAL(builder.links.m_Presenter, builder.links.m_MainFramePres->m_Presenter);
        CHECK_EQUAL(builder.links.m_EventHandler, builder.links.m_MainFramePres->m_EventHandler);

        CHECK_EQUAL(builder.links.m_EventHandler, builder.links.m_TaskBar->m_EventHandler);

        CHECK_EQUAL(builder.links.m_TaskBar, builder.links.m_TaskBarPres->m_View);
        CHECK_EQUAL(builder.links.m_Presenter, builder.links.m_TaskBarPres->m_Presenter);
        CHECK_EQUAL(builder.links.m_EventHandler, builder.links.m_TaskBarPres->m_EventHandler);

        CHECK_EQUAL(builder.links.m_MainFrame, setTop.m_Frame);

        CHECK_EQUAL(builder.links.m_PresenceHandler, &builder.links.m_PresHdlrConfigObserver->m_PresenceHandler);
        CHECK_EQUAL(builder.links.m_TimeKeeper, &builder.links.m_TKConfigObserver->m_TimeKeeper);
        CHECK_EQUAL(builder.links.m_Presenter, &builder.links.m_EWPresConfigObserver->m_Presenter);

        CHECK_EQUAL(false, builder.links.m_OptionsPres->m_Displayed);
    }

    TEST_FIXTURE(EWBuilderFixture, TestBuildNoTaskBar)
    {
        const EWTestBuilder<MsgHandlerStub, ConfigImplStub, ConfigStub, PresenceHandlerStub,
            TimeHandlerStub, TimeKeeperStub, TimerStub, EWPresenterStub, EventHandlerStub,
            EWViewPresStub<AbstractEWMainFrame>, EWMainFrameStub, EWViewPresStub<AbstractEWTaskbar>,
            EWTaskbarStub, OptionsDialogPresStub, OptionsDialogStub, TKConfigObserverStub,
            PresHdlrConfigObserverStub, EWPresConfigObserverStub> builder(&setTop, path, false, OptionsDialogStub::IdOK);
        CHECK_EQUAL(true, builder.links.m_TaskBarPres == nullptr);
        CHECK_EQUAL(true, builder.links.m_TaskBar == nullptr);
    }

    TEST_FIXTURE(EWBuilderFixture, TestBuildBadConfig)
    {
        const EWTestBuilder<MsgHandlerStub, ConfigImplStub, ConfigStubFail, PresenceHandlerStub,
            TimeHandlerStub, TimeKeeperStub, TimerStub, EWPresenterStub, EventHandlerStub,
            EWViewPresStub<AbstractEWMainFrame>, EWMainFrameStub, EWViewPresStub<AbstractEWTaskbar>,
            EWTaskbarStub, OptionsDialogPresStub, OptionsDialogStub, TKConfigObserverStub,
            PresHdlrConfigObserverStub, EWPresConfigObserverStub> builder(&setTop, path, true, OptionsDialogStub::IdOK);
        CHECK_EQUAL(true, builder.links.m_OptionsPres->m_Displayed);
    }

    TEST_FIXTURE(EWBuilderFixture, TestBuildBadConfigUnrecovered)
    {
        bool trown = false;
        try
        {
            const EWTestBuilder<MsgHandlerStub, ConfigImplStub, ConfigStubFail, PresenceHandlerStub,
            TimeHandlerStub, TimeKeeperStub, TimerStub, EWPresenterStub, EventHandlerStub,
            EWViewPresStub<AbstractEWMainFrame>, EWMainFrameStub, EWViewPresStub<AbstractEWTaskbar>,
            EWTaskbarStub, OptionsDialogPresStub, OptionsDialogStub, TKConfigObserverStub,
            PresHdlrConfigObserverStub, EWPresConfigObserverStub> builder(&setTop, path, true, OptionsDialogStub::IdOK + 1);
        }
        catch (InvalidConfigFileException)
        {
            trown = true;
        }
        CHECK_EQUAL(true, trown);
    }
}

