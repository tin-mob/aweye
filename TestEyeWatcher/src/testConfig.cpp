#include <unittest++/UnitTest++.h>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <string>
#include "Config.h"
#include "ConfigImplStub.h"

struct ConfigFixture
{
    ConfigFixture() {}
    ~ConfigFixture() {}

    ConfigImplStub impl;
};

SUITE(TestConfig)
{
    TEST_FIXTURE(ConfigFixture, TestValidation)
    {
        ConfigData data;

        CHECK_EQUAL(true, Config::validateData(data));

        data.workLength = boost::posix_time::seconds(0);
        CHECK_EQUAL(false, Config::validateData(data));
        data.workLength = ConfigData::default_WorkLength;

        data.pauseLength = boost::posix_time::seconds(0);
        CHECK_EQUAL(false, Config::validateData(data));
        data.pauseLength = ConfigData::default_PauseLength;

        data.remFreq = boost::posix_time::seconds(0);
        CHECK_EQUAL(false, Config::validateData(data));
        data.remFreq = ConfigData::default_RemFreq;

        data.checkFreq = boost::posix_time::seconds(0);
        CHECK_EQUAL(false, Config::validateData(data));
        data.checkFreq = ConfigData::default_CheckFreq;

        data.workLength = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, Config::validateData(data));
        data.workLength = ConfigData::default_WorkLength;

        data.pauseLength = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, Config::validateData(data));
        data.pauseLength = ConfigData::default_PauseLength;

        data.remFreq = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, Config::validateData(data));
        data.remFreq = ConfigData::default_RemFreq;

        data.checkFreq = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, Config::validateData(data));
        data.checkFreq = ConfigData::default_CheckFreq;

        data.runningLateThreshold = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, Config::validateData(data));
        data.runningLateThreshold = ConfigData::default_RunningLateThreshold;
    }

    TEST_FIXTURE(ConfigFixture, TestEmptyConstruction)
    {
        Config config(&impl);

        ConfigData data = config.getData();
        CHECK_EQUAL(ConfigData(), data);
    }

    TEST_FIXTURE(ConfigFixture, TestSaveLoad)
    {
        ConfigData data;
        ConfigData srcData =
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

        Config config(&impl);
        Config config2(&impl);
        config.save(srcData);

        config2.load();
        data = config2.getData();

        CHECK_EQUAL(srcData, data);

        Config config3(&impl);
        config3.load();
        data = config3.getData();

        CHECK_EQUAL(srcData, data);
    }


    TEST_FIXTURE(ConfigFixture, TestInvalidSave)
    {
        ConfigData data = {boost::posix_time::neg_infin};
        Config config(&impl);
        CHECK_THROW(config.save(data), InvalidConfigDataException);
    }
}

