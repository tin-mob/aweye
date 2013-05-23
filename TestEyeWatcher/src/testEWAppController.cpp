#include <unittest++/UnitTest++.h>
#include "EWAppController.h"
#include "MsgHandlerStub.h"
#include "ConfigStub.h"
#include "PresenceHandlerStub.h"
#include "TimeKeeperStub.h"
#include "EWPresenterStub.h"
#include "CommandStub.h"
#include "ConfigData.h"

struct EWAppControllerFixture
{
    EWAppControllerFixture() : config(data)
    {
        ctrl.link(&msgHandler, &config, &presenceHandler, &timeKeeper,
                  &presenter, &displayCmd);
    }
    ~EWAppControllerFixture() {}

    EWAppController ctrl;
    MsgHandlerStub msgHandler;
    ConfigData data;
    ConfigStub config;
    PresenceHandlerStub presenceHandler;
    TimeKeeperStub timeKeeper;
    EWPresenterStub presenter;
    CommandStub displayCmd;
};

SUITE(TestEWAppController)
{
    TEST_FIXTURE(EWAppControllerFixture, TestGet)
    {
        ///@todo: put this in a function to remove redundancy
        ConfigData newData =
        {
            ConfigData::default_WorkLength + boost::posix_time::seconds(1),
            ConfigData::default_PauseLength + boost::posix_time::seconds(1),
            ConfigData::default_RemFreq + boost::posix_time::seconds(1),
            ConfigData::default_CheckFreq + boost::posix_time::seconds(1),
            ConfigData::default_PauseTol + 1,
            !ConfigData::default_SoundAlarm,
            !ConfigData::default_PopupAlarm,
            !ConfigData::default_TrayIcon,
            ConfigData::default_WebcamIndex + 1,
            ConfigData::default_FaceSizeX + 1,
            ConfigData::default_FaceSizeY + 1,
            "test.cfg",
            "test.wav",
            ConfigData::default_CheckFreq + boost::posix_time::seconds(1)
        };

        config.save(newData);
        CHECK_EQUAL(newData, ctrl.getConfigData());
    }

    TEST_FIXTURE(EWAppControllerFixture, TestSave)
    {
        ConfigData newData =
        {
            ConfigData::default_WorkLength + boost::posix_time::seconds(1),
            ConfigData::default_PauseLength + boost::posix_time::seconds(1),
            ConfigData::default_RemFreq + boost::posix_time::seconds(1),
            ConfigData::default_CheckFreq + boost::posix_time::seconds(1),
            ConfigData::default_PauseTol + 1,
            !ConfigData::default_SoundAlarm,
            !ConfigData::default_PopupAlarm,
            !ConfigData::default_TrayIcon,
            ConfigData::default_WebcamIndex + 1,
            ConfigData::default_FaceSizeX + 1,
            ConfigData::default_FaceSizeY + 1,
            "test.cfg",
            "test.wav",
            ConfigData::default_CheckFreq + boost::posix_time::seconds(1)
        };

        CHECK_EQUAL(true, ctrl.saveConfig(newData));
        CHECK_EQUAL(newData, config.getData());
        CHECK_EQUAL(newData.cascadePath, presenceHandler.cascadePath);
        CHECK_EQUAL(newData.webcamIndex, presenceHandler.webcamIndex);
        CHECK_EQUAL(newData.faceSizeX, presenceHandler.faceSizeX);
        CHECK_EQUAL(newData.faceSizeY, presenceHandler.faceSizeY);

        CHECK_EQUAL(newData.checkFreq, timeKeeper.checkFreq);
        CHECK_EQUAL(newData.pauseLength, timeKeeper.pauseLength);
        CHECK_EQUAL(newData.pauseTol, timeKeeper.pauseTol);
        CHECK_EQUAL(newData.remFreq, timeKeeper.remFreq);
        CHECK_EQUAL(newData.workLength, timeKeeper.workLength);

        CHECK_EQUAL(newData.popupAlarm, presenter.popupAlarm);
        CHECK_EQUAL(newData.soundAlarm, presenter.soundAlarm);
        CHECK_EQUAL(newData.soundPath, presenter.soundPath);
        CHECK_EQUAL(newData.runningLateThreshold, presenter.runningLateThreshold);
    }

    TEST_FIXTURE(EWAppControllerFixture, TestSaveFail)
    {
        config.fail = true;
        CHECK_EQUAL(false, ctrl.saveConfig(ConfigData()));
        CHECK_EQUAL("Testing!", msgHandler.lastError);
    }

    TEST_FIXTURE(EWAppControllerFixture, TestDisplay)
    {
        ctrl.displayOptionsDialog();
        CHECK_EQUAL(true, displayCmd.executed);
    }

    TEST_FIXTURE(EWAppControllerFixture, TestDisplayFail)
    {
        displayCmd.fail = true;
        ctrl.displayOptionsDialog();
        CHECK_EQUAL("Testing!", msgHandler.lastError);
    }
}
