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

    TEST_FIXTURE(ConfigFixture, TestEmptyConstruction)
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
    }

    TEST_FIXTURE(ConfigFixture, TestEmptyNameConstruction)
    {
        CHECK(!boost::filesystem::exists(configPath));
        CHECK_THROW(Config config(""), InvalidConfigFileException);
    }

    TEST_FIXTURE(ConfigFixture, TestInvalidFileConstruction)
    {
        std::string fileName = "TestFiles/invalidConfig.cfg";
        CHECK(boost::filesystem::exists(fileName));
        CHECK_THROW(Config config(fileName), InvalidConfigFileException);
    }

    TEST_FIXTURE(ConfigFixture, TestInvalidDataConstruction)
    {
        std::string fileName = "TestFiles/invalidValConfig.cfg";
        CHECK(boost::filesystem::exists(fileName));
        CHECK_THROW(Config config(fileName), InvalidConfigFileException);
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
            !ConfigData::default_Startup,
            !ConfigData::default_SoundAlarm,
            !ConfigData::default_PopupAlarm,
            !ConfigData::default_EmailAlarm,
            "test@test.test"
        };

        Config config(configPath);
        Config config2(configPath);
        config.save(srcData);

        config2.checkLoad();
        data = config2.getData();

        CHECK_EQUAL(srcData.workLength, data.workLength);
        CHECK_EQUAL(srcData.pauseLength, data.pauseLength);
        CHECK_EQUAL(srcData.remFreq, data.remFreq);
        CHECK_EQUAL(srcData.checkFreq, data.checkFreq);
        CHECK_EQUAL(srcData.pauseTol, data.pauseTol);
        CHECK_EQUAL(srcData.startup, data.startup);
        CHECK_EQUAL(srcData.soundAlarm, data.soundAlarm);
        CHECK_EQUAL(srcData.popupAlarm, data.popupAlarm);
        CHECK_EQUAL(srcData.emailAlarm, data.emailAlarm);
        CHECK_EQUAL(srcData.emailAddr, data.emailAddr);

        Config config3(configPath);
        config3.checkLoad();
        data = config3.getData();

        CHECK_EQUAL(srcData.workLength, data.workLength);
        CHECK_EQUAL(srcData.pauseLength, data.pauseLength);
        CHECK_EQUAL(srcData.remFreq, data.remFreq);
        CHECK_EQUAL(srcData.checkFreq, data.checkFreq);
        CHECK_EQUAL(srcData.pauseTol, data.pauseTol);
        CHECK_EQUAL(srcData.startup, data.startup);
        CHECK_EQUAL(srcData.soundAlarm, data.soundAlarm);
        CHECK_EQUAL(srcData.popupAlarm, data.popupAlarm);
        CHECK_EQUAL(srcData.emailAlarm, data.emailAlarm);
        CHECK_EQUAL(srcData.emailAddr, data.emailAddr);

    }
}
