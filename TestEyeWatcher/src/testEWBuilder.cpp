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

struct EWBuilderFixture
{
    EWBuilderFixture() : path("path") {}
    ~EWBuilderFixture() {}

    SetTopWindowStub setTop;
    std::string path;
};

SUITE(TestEWBuilder)
{
    TEST_FIXTURE(EWBuilderFixture, TestGet)
    {
        EWTestBuilder<MsgHandlerStub, ConfigImplStub, ConfigStub, PresenceHandlerStub,
        TimeHandlerStub, TimeKeeperStub, TimerStub, EWAppControllerStub,
        EWPresenterStub, EWMainFramePresStub, EWMainFrameStub, OptionsDialogPresStub,
        EWTaskBarPresStub, EWTaskbarStub, DisOptDiaCmdStub> builder(&setTop, path, true);

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

        CHECK_EQUAL(path, builder.links.m_ConfigImpl->path);
        CHECK_EQUAL(builder.links.m_Config->impl, builder.links.m_ConfigImpl);

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

        CHECK_EQUAL(builder.links.m_MsgHandler, builder.links.m_Presenter->msgHandler);
        CHECK_EQUAL(builder.links.m_TimeKeeper, builder.links.m_Presenter->keeper);
        CHECK_EQUAL(builder.links.m_CheckTimer, builder.links.m_Presenter->checkTimer);
        CHECK_EQUAL(builder.links.m_ClockTimer, builder.links.m_Presenter->clockTimer);

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

        CHECK_EQUAL(builder.links.m_AppController, builder.links.m_DisplayOptionsDialogCmd->controller);
        CHECK_EQUAL(builder.links.m_OptionsPres, builder.links.m_DisplayOptionsDialogCmd->presenter);

        CHECK_EQUAL(builder.links.m_MainFrame, setTop.frame);

        CHECK_EQUAL(builder.links.m_MsgHandler, builder.links.m_AppController->msgHandler);
        CHECK_EQUAL(builder.links.m_Config, builder.links.m_AppController->config);
        CHECK_EQUAL(builder.links.m_PresenceHandler, builder.links.m_AppController->presenceHandler);
        CHECK_EQUAL(builder.links.m_TimeKeeper, builder.links.m_AppController->timeKeeper);
        CHECK_EQUAL(builder.links.m_Presenter, builder.links.m_AppController->presenter);
        CHECK_EQUAL(builder.links.m_DisplayOptionsDialogCmd, builder.links.m_AppController->displayCmd);
    }
}
