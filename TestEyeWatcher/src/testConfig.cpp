#include <unittest++/UnitTest++.h>
#include <string>
#include "Config.h"

#include <boost/filesystem.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

struct ConfigFixture
{
    ConfigFixture() : configPath("/tmp/test.cfg") {boost::filesystem::remove(configPath);}
    ~ConfigFixture() {boost::filesystem::remove(configPath);}

    const std::string configPath;
};

SUITE(TestConfig)
{
    TEST_FIXTURE(ConfigFixture, TestValidation)
    {
        ConfigData data = {ConfigData::default_WorkLength,
            ConfigData::default_PauseLength, ConfigData::default_RemFreq,
            ConfigData::default_CheckFreq, ConfigData::default_PauseTol,
            ConfigData::default_Startup, ConfigData::default_SoundAlarm,
            ConfigData::default_PopupAlarm, ConfigData::default_EmailAlarm,
            ConfigData::default_EmailAddr};

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


    }

    TEST_FIXTURE(ConfigFixture, TestSaveLoad)
    {
        CHECK(!boost::filesystem::exists(configPath));

        Config config(configPath);

        CHECK(boost::filesystem::exists(configPath));

        ConfigData data = config.getData();

        CHECK_EQUAL(ConfigData::default_WorkLength, data.workLength);
        CHECK_EQUAL(ConfigData::default_PauseLength, data.pauseLength);
        CHECK_EQUAL(ConfigData::default_RemFreq, data.remFreq);
        CHECK_EQUAL(ConfigData::default_CheckFreq, data.checkFreq);
        CHECK_EQUAL(ConfigData::default_PauseTol, data.pauseTol);
        CHECK_EQUAL(ConfigData::default_Startup, data.startup);
        CHECK_EQUAL(ConfigData::default_SoundAlarm, data.soundAlarm);
        CHECK_EQUAL(ConfigData::default_PopupAlarm, data.popupAlarm);
        CHECK_EQUAL(ConfigData::default_EmailAlarm, data.emailAlarm);
        CHECK_EQUAL(ConfigData::default_EmailAddr, data.emailAddr);

        const boost::posix_time::time_duration test_WorkLength = ConfigData::default_WorkLength + boost::posix_time::seconds(1);
        const boost::posix_time::time_duration test_PauseLength = ConfigData::default_PauseLength + boost::posix_time::seconds(1);
        const boost::posix_time::time_duration test_RemFreq = ConfigData::default_RemFreq + boost::posix_time::seconds(1);
        const boost::posix_time::time_duration test_CheckFreq = ConfigData::default_CheckFreq + boost::posix_time::seconds(1);
        const unsigned int test_PauseTol = ConfigData::default_PauseTol + 1;
        const bool test_Startup = !ConfigData::default_Startup;
        const bool test_SoundAlarm = !ConfigData::default_SoundAlarm;
        const bool test_PopupAlarm = !ConfigData::default_PopupAlarm;
        const bool test_EmailAlarm = !ConfigData::default_EmailAlarm;
        const std::string test_EmailAddr = "test@test.test";

        data.workLength = test_WorkLength;
        data.pauseLength = test_PauseLength;
        data.remFreq = test_RemFreq;
        data.checkFreq = test_CheckFreq;
        data.pauseTol = test_PauseTol;
        data.startup = test_Startup;
        data.soundAlarm = test_SoundAlarm;
        data.popupAlarm = test_PopupAlarm;
        data.emailAlarm = test_EmailAlarm;
        data.emailAddr = test_EmailAddr;

        config.save(data);
        config.checkLoad();
        data = config.getData();

        CHECK_EQUAL(test_WorkLength, data.workLength);
        CHECK_EQUAL(test_PauseLength, data.pauseLength);
        CHECK_EQUAL(test_RemFreq, data.remFreq);
        CHECK_EQUAL(test_CheckFreq, data.checkFreq);
        CHECK_EQUAL(test_PauseTol, data.pauseTol);
        CHECK_EQUAL(test_Startup, data.startup);
        CHECK_EQUAL(test_SoundAlarm, data.soundAlarm);
        CHECK_EQUAL(test_PopupAlarm, data.popupAlarm);
        CHECK_EQUAL(test_EmailAlarm, data.emailAlarm);
        CHECK_EQUAL(test_EmailAddr, data.emailAddr);

        Config config2(configPath);
        data = config2.getData();

        CHECK_EQUAL(test_WorkLength, data.workLength);
        CHECK_EQUAL(test_PauseLength, data.pauseLength);
        CHECK_EQUAL(test_RemFreq, data.remFreq);
        CHECK_EQUAL(test_CheckFreq, data.checkFreq);
        CHECK_EQUAL(test_PauseTol, data.pauseTol);
        CHECK_EQUAL(test_Startup, data.startup);
        CHECK_EQUAL(test_SoundAlarm, data.soundAlarm);
        CHECK_EQUAL(test_PopupAlarm, data.popupAlarm);
        CHECK_EQUAL(test_EmailAlarm, data.emailAlarm);
        CHECK_EQUAL(test_EmailAddr, data.emailAddr);
    }
}
