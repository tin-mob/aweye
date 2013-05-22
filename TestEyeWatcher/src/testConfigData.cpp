#include <unittest++/UnitTest++.h>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <string>
#include "ConfigData.h"

struct ConfigDataFixture
{
    ConfigDataFixture() {}
    ~ConfigDataFixture() {}
};

SUITE(TestConfigData)
{
    TEST_FIXTURE(ConfigDataFixture, TestComparison)
    {
        ConfigData src;
        CHECK_EQUAL(src, src);

        ConfigData mod;
        mod.workLength = ConfigData::default_WorkLength + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.pauseLength = ConfigData::default_PauseLength + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.remFreq = ConfigData::default_RemFreq + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.checkFreq = ConfigData::default_CheckFreq + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.pauseTol = ConfigData::default_PauseTol + 1;
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.soundAlarm = !ConfigData::default_SoundAlarm;
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.popupAlarm = !ConfigData::default_PopupAlarm;
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.trayIcon = !ConfigData::default_TrayIcon;
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.webcamIndex = ConfigData::default_WebcamIndex + 1;
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.faceSizeX = ConfigData::default_FaceSizeX + 1;
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.faceSizeY = ConfigData::default_FaceSizeY + 1;
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.cascadePath = "test.cfg";
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.soundPath = "test.wav";
        CHECK_EQUAL(false, mod == src);

        mod = {};
        mod.runningLateThreshold = ConfigData::default_CheckFreq + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);
    }
}
