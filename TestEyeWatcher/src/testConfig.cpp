#include <unittest++/UnitTest++.h>
#include <string>
#include "Config.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

struct ConfigFixture
{
    ConfigFixture() : configPath("/tmp/test.cfg") {remove(configPath);}
    ~ConfigFixture() {remove(configPath);}

    const std::string configPath;
};

SUITE(TestConfig)
{
    TEST_FIXTURE(ConfigFixture, TestAll)
    {
        CHECK(!exists(configPath));

        Config config(configPath);

        CHECK(exists(configPath));

        CHECK_EQUAL(Config::default_WorkLength, config.getWorkLength());
        CHECK_EQUAL(Config::default_PauseLength, config.getPauseLength());
        CHECK_EQUAL(Config::default_RemFreq, config.getRemFreq());
        CHECK_EQUAL(Config::default_CheckFreq, config.getCheckFreq());
        CHECK_EQUAL(Config::default_PauseTol, config.getPauseTol());
        CHECK_EQUAL(Config::default_Startup, config.getStartup());
        CHECK_EQUAL(Config::default_SoundAlarm, config.getSoundAlarm());
        CHECK_EQUAL(Config::default_PopupAlarm, config.getPopupAlarm());
        CHECK_EQUAL(Config::default_EmailAlarm, config.getEmailAlarm());
        CHECK_EQUAL(Config::default_EmailAddr, config.getEmailAddr());

        const unsigned int test_WorkLength = Config::default_WorkLength + 1;
        const unsigned int test_PauseLength = Config::default_PauseLength + 1;
        const unsigned int test_RemFreq = Config::default_RemFreq + 1;
        const unsigned int test_CheckFreq = Config::default_CheckFreq + 1;
        const unsigned int test_PauseTol = Config::default_PauseTol + 1;
        const bool test_Startup = !Config::default_Startup;
        const bool test_SoundAlarm = !Config::default_SoundAlarm;
        const bool test_PopupAlarm = !Config::default_PopupAlarm;
        const bool test_EmailAlarm = !Config::default_EmailAlarm;
        const std::string test_EmailAddr = "test@test.test";

        config.setWorkLength(test_WorkLength);
        config.setPauseLength(test_PauseLength);
        config.setRemFreq(test_RemFreq);
        config.setCheckFreq(test_CheckFreq);
        config.setPauseTol(test_PauseTol);
        config.setStartup(test_Startup);
        config.setSoundAlarm(test_SoundAlarm);
        config.setPopupAlarm(test_PopupAlarm);
        config.setEmailAlarm(test_EmailAlarm);
        config.setEmailAddr(test_EmailAddr);

        CHECK_EQUAL(test_WorkLength, config.getWorkLength());
        CHECK_EQUAL(test_PauseLength, config.getPauseLength());
        CHECK_EQUAL(test_RemFreq, config.getRemFreq());
        CHECK_EQUAL(test_CheckFreq, config.getCheckFreq());
        CHECK_EQUAL(test_PauseTol, config.getPauseTol());
        CHECK_EQUAL(test_Startup, config.getStartup());
        CHECK_EQUAL(test_SoundAlarm, config.getSoundAlarm());
        CHECK_EQUAL(test_PopupAlarm, config.getPopupAlarm());
        CHECK_EQUAL(test_EmailAlarm, config.getEmailAlarm());
        CHECK_EQUAL(test_EmailAddr, config.getEmailAddr());

        config.save();
        config.checkLoad();

        CHECK_EQUAL(test_WorkLength, config.getWorkLength());
        CHECK_EQUAL(test_PauseLength, config.getPauseLength());
        CHECK_EQUAL(test_RemFreq, config.getRemFreq());
        CHECK_EQUAL(test_CheckFreq, config.getCheckFreq());
        CHECK_EQUAL(test_PauseTol, config.getPauseTol());
        CHECK_EQUAL(test_Startup, config.getStartup());
        CHECK_EQUAL(test_SoundAlarm, config.getSoundAlarm());
        CHECK_EQUAL(test_PopupAlarm, config.getPopupAlarm());
        CHECK_EQUAL(test_EmailAlarm, config.getEmailAlarm());
        CHECK_EQUAL(test_EmailAddr, config.getEmailAddr());

        Config config2(configPath);

        CHECK_EQUAL(test_WorkLength, config2.getWorkLength());
        CHECK_EQUAL(test_PauseLength, config2.getPauseLength());
        CHECK_EQUAL(test_RemFreq, config2.getRemFreq());
        CHECK_EQUAL(test_CheckFreq, config2.getCheckFreq());
        CHECK_EQUAL(test_PauseTol, config2.getPauseTol());
        CHECK_EQUAL(test_Startup, config2.getStartup());
        CHECK_EQUAL(test_SoundAlarm, config2.getSoundAlarm());
        CHECK_EQUAL(test_PopupAlarm, config2.getPopupAlarm());
        CHECK_EQUAL(test_EmailAlarm, config2.getEmailAlarm());
        CHECK_EQUAL(test_EmailAddr, config2.getEmailAddr());
    }
}
