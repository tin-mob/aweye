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


#include <unittest++/UnitTest++.h>

#include "MsgHandlerStub.h"
#include "ConfigImplStub.h"
#include "ConfigStub.h"
#include "PresenceHandlerStub.h"
#include "TimeHandlerStub.h"
#include "TimeKeeperStub.h"
#include "TimerStub.h"
#include "EWAppControllerStub.h"
#include "EWPresenterStub.h"
#include "EWMainFramePresStub.h"
#include "EWMainFrameStub.h"
#include "OptionsDialogPresStub.h"
#include "EWTaskBarPresStub.h"
#include "EWTaskbarStub.h"
#include "DisOptDiaCmdStub.h"
#include "EWTestBuilder.h"
#include "SetTopWindowStub.h"
#include "BuiOptDisPresStub.h"

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
            TimeHandlerStub, TimeKeeperStub, TimerStub, EWAppControllerStub,
            EWPresenterStub, EWMainFramePresStub, EWMainFrameStub,
            EWTaskBarPresStub, EWTaskbarStub, OptionsDialogPresStub,
            BuiOptDisPresStub, DisOptDiaCmdStub> builder(&setTop, path, true);

        CHECK_EQUAL(false, builder.links.m_MsgHandler == nullptr);
        CHECK_EQUAL(false, builder.links.m_ConfigImpl == nullptr);
        CHECK_EQUAL(false, builder.links.m_Config == nullptr);
        CHECK_EQUAL(false, builder.links.m_PresenceHandler == nullptr);
        CHECK_EQUAL(false, builder.links.m_TimeHandler == nullptr);
        CHECK_EQUAL(false, builder.links.m_TimeKeeper == nullptr);
        CHECK_EQUAL(false, builder.links.m_CheckTimer == nullptr);
        CHECK_EQUAL(false, builder.links.m_ClockTimer == nullptr);
        CHECK_EQUAL(false, builder.links.m_AppController == nullptr);
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
        CHECK_EQUAL(data.cascadePath, builder.links.m_PresenceHandler->cascadePath);
        CHECK_EQUAL(data.webcamIndex, builder.links.m_PresenceHandler->webcamIndex);
        CHECK_EQUAL(data.faceSizeX, builder.links.m_PresenceHandler->faceSizeX);
        CHECK_EQUAL(data.faceSizeY, builder.links.m_PresenceHandler->faceSizeY);

        CHECK_EQUAL(builder.links.m_TimeHandler, builder.links.m_TimeKeeper->timeHandler);
        CHECK_EQUAL(builder.links.m_PresenceHandler, builder.links.m_TimeKeeper->presenceHandler);

        CHECK_EQUAL(data.workLength, builder.links.m_TimeKeeper->workLength);
        CHECK_EQUAL(data.pauseLength, builder.links.m_TimeKeeper->pauseLength);
        CHECK_EQUAL(data.remFreq, builder.links.m_TimeKeeper->remFreq);
        CHECK_EQUAL(data.checkFreq, builder.links.m_TimeKeeper->checkFreq);
        CHECK_EQUAL(data.pauseTol, builder.links.m_TimeKeeper->pauseTol);
        CHECK_EQUAL(data.workTol, builder.links.m_TimeKeeper->workTol);

        CHECK_EQUAL(builder.links.m_MsgHandler, builder.links.m_Presenter->msgHandler);
        CHECK_EQUAL(builder.links.m_TimeKeeper, builder.links.m_Presenter->keeper);
        CHECK_EQUAL(builder.links.m_CheckTimer, builder.links.m_Presenter->checkTimer);
        CHECK_EQUAL(builder.links.m_ClockTimer, builder.links.m_Presenter->clockTimer);
        CHECK_EQUAL(builder.links.m_TimeHandler, builder.links.m_Presenter->timeHandler);

        CHECK_EQUAL(data.popupAlarm, builder.links.m_Presenter->popupAlarm);
        CHECK_EQUAL(data.soundAlarm, builder.links.m_Presenter->soundAlarm);
        CHECK_EQUAL(data.soundPath, builder.links.m_Presenter->soundPath);
        CHECK_EQUAL(data.runningLateThreshold, builder.links.m_Presenter->runningLateThreshold);

        CHECK_EQUAL(builder.links.m_Presenter, builder.links.m_MainFramePres->presenter);
        CHECK_EQUAL(builder.links.m_AppController, builder.links.m_MainFramePres->controller);

        CHECK_EQUAL(builder.links.m_MainFramePres, builder.links.m_MainFrame->presenter);
        CHECK_EQUAL(true, builder.links.m_MainFrame->taskbarCreated);

        CHECK_EQUAL(builder.links.m_Presenter, builder.links.m_TaskBarPres->presenter);
        CHECK_EQUAL(builder.links.m_AppController, builder.links.m_TaskBarPres->controller);

        CHECK_EQUAL(builder.links.m_TaskBarPres, builder.links.m_TaskBar->presenter);

        CHECK_EQUAL(builder.links.m_OptionsPres, builder.links.m_DisplayOptionsDialogCmd->m_Presenter);

        CHECK_EQUAL(builder.links.m_MainFrame, setTop.frame);

        CHECK_EQUAL(builder.links.m_MsgHandler, builder.links.m_AppController->msgHandler);
        CHECK_EQUAL(builder.links.m_Config, builder.links.m_AppController->config);
        CHECK_EQUAL(builder.links.m_PresenceHandler, builder.links.m_AppController->presenceHandler);
        CHECK_EQUAL(builder.links.m_TimeKeeper, builder.links.m_AppController->timeKeeper);
        CHECK_EQUAL(builder.links.m_Presenter, builder.links.m_AppController->presenter);
        CHECK_EQUAL(builder.links.m_DisplayOptionsDialogCmd, builder.links.m_AppController->displayCmd);
    }

    TEST_FIXTURE(EWBuilderFixture, TestBuildBadConfig)
    {
        // building it is the test...
        const EWTestBuilder<MsgHandlerStub, ConfigImplStub, ConfigStubFail, PresenceHandlerStub,
            TimeHandlerStub, TimeKeeperStub, TimerStub, EWAppControllerStub,
            EWPresenterStub, EWMainFramePresStub, EWMainFrameStub,
            EWTaskBarPresStub, EWTaskbarStub, OptionsDialogPresStub,
            BuiOptDisPresStub, DisOptDiaCmdStub> builder(&setTop, path, true);
    }

    TEST_FIXTURE(EWBuilderFixture, TestBuildBadConfigUnrecovered)
    {
        bool trown = false;
        try
        {
            const EWTestBuilder<MsgHandlerStub, ConfigImplStub, ConfigStubFail, PresenceHandlerStub,
                TimeHandlerStub, TimeKeeperStub, TimerStub, EWAppControllerStub,
                EWPresenterStub, EWMainFramePresStub, EWMainFrameStub,
                EWTaskBarPresStub, EWTaskbarStub, OptionsDialogPresStub,
                BuiOptDisPresStubFail, DisOptDiaCmdStubFail> builder(&setTop, path, true);
        }
        catch (InvalidConfigFileException)
        {
            trown = true;
        }
        CHECK_EQUAL(true, trown);
    }
}

