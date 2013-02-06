#include <unittest++/UnitTest++.h>
#include "EWLogic.h"
#include "ConfigStub.h"
#include "MsgHandlerStub.h"
#include "TimeKeeperStub.h"

struct EWLogicFixture
{
    public:
        EWLogicFixture()
        {
            this->data = {boost::posix_time::seconds(5), boost::posix_time::seconds(3), boost::posix_time::seconds(1),
                boost::posix_time::seconds(2), ConfigData::default_PauseTol, ConfigData::default_Startup, ConfigData::default_SoundAlarm,
                ConfigData::default_PopupAlarm, ConfigData::default_EmailAlarm, ConfigData::default_EmailAddr};

            this->config = new ConfigStub(data);
            this->msgHandler = new MsgHandlerStub();
            this->keeper = new TimeKeeperStub();
            this->logic = new EWLogic(this->msgHandler, this->config, this->keeper);
        }
        ~EWLogicFixture()
        {
            delete this->config;
            delete this->msgHandler;
            delete this->keeper;
            delete this->logic;
        }

        ConfigData data;
        AbstractConfig* config;
        AbstractMsgHandler* msgHandler;
        AbstractTimeKeeper* keeper;
        EWLogic* logic;

    protected:
    private:
};

SUITE(TestEWLogic)
{
    TEST_FIXTURE(EWLogicFixture, TestConfig)
    {
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

        ConfigData newData = {test_WorkLength, test_PauseLength, test_RemFreq, test_CheckFreq, test_PauseTol,
            test_Startup, test_SoundAlarm, test_PopupAlarm, test_EmailAlarm, test_EmailAddr};

        logic->saveConfig(newData);
        ConfigData returnedData = logic->getConfigData();

        CHECK_EQUAL(test_WorkLength, returnedData.workLength);
        CHECK_EQUAL(test_PauseLength, returnedData.pauseLength);
        CHECK_EQUAL(test_RemFreq, returnedData.remFreq);
        CHECK_EQUAL(test_CheckFreq, returnedData.checkFreq);
        CHECK_EQUAL(test_PauseTol, returnedData.pauseTol);
        CHECK_EQUAL(test_Startup, returnedData.startup);
        CHECK_EQUAL(test_SoundAlarm, returnedData.soundAlarm);
        CHECK_EQUAL(test_PopupAlarm, returnedData.popupAlarm);
        CHECK_EQUAL(test_EmailAlarm, returnedData.emailAlarm);
        CHECK_EQUAL(test_EmailAddr, returnedData.emailAddr);
    }

    TEST_FIXTURE(EWLogicFixture, TestStartPauseStop)
    {
    }

    TEST_FIXTURE(EWLogicFixture, TestFailedStart)
    {
    }
}
