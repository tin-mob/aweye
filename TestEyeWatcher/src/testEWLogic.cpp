#include <unittest++/UnitTest++.h>
#include "EWLogic.h"
#include "ConfigStub.h"
#include "MsgHandlerStub.h"
#include "TimeKeeperStub.h"
#include "TimerHandlerStub.h"

struct EWLogicFixture
{
    public:
        EWLogicFixture() : config(NULL), msgHandler(NULL), keeper(NULL), logic(NULL)
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
            if (this->config != NULL) {delete this->config;}
            if (this->msgHandler != NULL) {delete this->msgHandler;}
            if (this->keeper != NULL) {delete this->keeper;}
            if (this->logic != NULL) {delete this->logic;}
        }

        ConfigData data;
        ConfigStub* config;
        MsgHandlerStub* msgHandler;
        TimeKeeperStub* keeper;
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

    TEST_FIXTURE(EWLogicFixture, TestStartStop)
    {
        TimerHandlerStub timerHandler;
        CHECK_EQUAL(timerHandler.running, false);
        CHECK_EQUAL(logic->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::OFF));
        logic->start(timerHandler);
        CHECK_EQUAL(timerHandler.running, true);
        CHECK_EQUAL(logic->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::HERE));
        logic->stop(timerHandler);
        CHECK_EQUAL(timerHandler.running, false);
        CHECK_EQUAL(logic->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::OFF));

        keeper->fail = true;
        CHECK_EQUAL(msgHandler->lastError, "");
        logic->start(timerHandler);
        CHECK_EQUAL(msgHandler->lastError, "Testing!");
    }

    TEST_FIXTURE(EWLogicFixture, TestUpdate)
    {
        TimerHandlerStub timerHandler;
        CHECK_EQUAL(logic->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::OFF));
        logic->updateStatus(timerHandler);
        CHECK_EQUAL(timerHandler.running, true);
        CHECK_EQUAL(logic->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::AWAY));

        keeper->fail = true;
        CHECK_EQUAL(msgHandler->lastError, "");
        logic->updateStatus(timerHandler);
        CHECK_EQUAL(msgHandler->lastError, "Testing!");
    }

    TEST_FIXTURE(EWLogicFixture, TestGetNextStatusTimer)
    {
        CHECK_EQUAL(logic->getNextStatusTimer(), boost::posix_time::seconds(1));
    }

    TEST_FIXTURE(EWLogicFixture, TestTimes)
    {
        CHECK_EQUAL(logic->getTimeOn(), "10:59:00");
        CHECK_EQUAL(logic->getTimeOff(), "11:31:01");
        CHECK_EQUAL(logic->getTimeRunning(), "00:00:02");
        CHECK_EQUAL(logic->getTimeLeft(), "00:03:00");

        keeper->hereStamp = boost::posix_time::not_a_date_time;
        keeper->awayStamp = boost::posix_time::not_a_date_time;
        keeper->interval = boost::posix_time::not_a_date_time;
        keeper->left = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(logic->getTimeOn(), "00:00:00");
        CHECK_EQUAL(logic->getTimeOff(), "00:00:00");
        CHECK_EQUAL(logic->getTimeRunning(), "00:00:00");
        CHECK_EQUAL(logic->getTimeLeft(), "00:00:00");
    }
}
