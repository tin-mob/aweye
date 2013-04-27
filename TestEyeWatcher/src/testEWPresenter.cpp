#include <unittest++/UnitTest++.h>
#include "EWPresenter.h"
#include "ConfigStub.h"
#include "ConfigDialogStub.h"
#include "MsgHandlerStub.h"
#include "TimeKeeperStub.h"
#include "TimerHandlerStub.h"

struct EWPresenterFixture
{
    public:
        EWPresenterFixture() : config(NULL), msgHandler(NULL), keeper(NULL), presenter(NULL)
        {
            this->data = {boost::posix_time::seconds(5), boost::posix_time::seconds(3), boost::posix_time::seconds(1),
                boost::posix_time::seconds(2), ConfigData::default_PauseTol, ConfigData::default_Startup, ConfigData::default_SoundAlarm,
                ConfigData::default_PopupAlarm, ConfigData::default_EmailAlarm, ConfigData::default_EmailAddr};

            try
            {
                this->config = new ConfigStub(data);
                this->msgHandler = new MsgHandlerStub();
                this->keeper = new TimeKeeperStub();
                this->dialog = new OptionsDialogStub();
                this->presenter = new EWPresenter(this->msgHandler, this->config, this->keeper);
            }
            catch (...)
            {
                this->deleteFixture();
                throw;
            }
        }
        ~EWPresenterFixture()
        {
            this->deleteFixture();
        }

        ConfigData data;
        ConfigStub* config;
        MsgHandlerStub* msgHandler;
        TimeKeeperStub* keeper;
        OptionsDialogStub* dialog;
        EWPresenter* presenter;

    protected:
    private:
        void deleteFixture()
        {
            if (this->config != NULL) {delete this->config;}
            if (this->msgHandler != NULL) {delete this->msgHandler;}
            if (this->keeper != NULL) {delete this->keeper;}
            if (this->dialog != NULL) {delete this->dialog;}
            if (this->presenter != NULL) {delete this->presenter;}
        }
};

SUITE(TestEWPresenter)
{
    TEST_FIXTURE(EWPresenterFixture, TestConfig)
    {
        presenter->loadConfig(dialog);
        presenter->saveConfig(dialog);

        ConfigData returnedData = dialog->getData();
        CHECK_EQUAL(data.workLength, returnedData.workLength);
        CHECK_EQUAL(data.pauseLength, returnedData.pauseLength);
        CHECK_EQUAL(data.remFreq, returnedData.remFreq);
        CHECK_EQUAL(data.checkFreq, returnedData.checkFreq);
        CHECK_EQUAL(data.pauseTol, returnedData.pauseTol);
        CHECK_EQUAL(data.startup, returnedData.startup);
        CHECK_EQUAL(data.soundAlarm, returnedData.soundAlarm);
        CHECK_EQUAL(data.popupAlarm, returnedData.popupAlarm);
        CHECK_EQUAL(data.emailAlarm, returnedData.emailAlarm);
        CHECK_EQUAL(data.emailAddr, returnedData.emailAddr);
    }

    TEST_FIXTURE(EWPresenterFixture, TestStartStop)
    {
        TimerHandlerStub timerHandler;
        CHECK_EQUAL(timerHandler.running, false);
        CHECK_EQUAL(presenter->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::OFF));

        presenter->start(timerHandler);
        CHECK_EQUAL(timerHandler.running, true);
        CHECK_EQUAL(presenter->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::HERE));

        presenter->stop(timerHandler);
        CHECK_EQUAL(timerHandler.running, false);
        CHECK_EQUAL(presenter->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::OFF));

        keeper->fail = true;
        CHECK_EQUAL(msgHandler->lastError, "");
        presenter->start(timerHandler);
        CHECK_EQUAL(msgHandler->lastError, "Testing!");
    }

    TEST_FIXTURE(EWPresenterFixture, TestUpdate)
    {
        TimerHandlerStub timerHandler;
        CHECK_EQUAL(presenter->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::OFF));
        presenter->updateStatus(timerHandler);
        CHECK_EQUAL(timerHandler.running, true);
        CHECK_EQUAL(presenter->getStatus(), AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::HERE));
        CHECK_EQUAL(msgHandler->lastAlert, "");

        keeper->late = true;
        presenter->updateStatus(timerHandler);
        CHECK_EQUAL(msgHandler->lastAlert, presenter->m_LateMsg);

        keeper->fail = true;
        CHECK_EQUAL(msgHandler->lastError, "");
        presenter->updateStatus(timerHandler);
        CHECK_EQUAL(msgHandler->lastError, "Testing!");
    }

    TEST_FIXTURE(EWPresenterFixture, TestGetNextStatusTimer)
    {
        CHECK_EQUAL(presenter->getNextStatusTimer(), boost::posix_time::seconds(1));
    }

    TEST_FIXTURE(EWPresenterFixture, TestTimes)
    {
        CHECK_EQUAL(presenter->getTimeOn(), "10:59:00");
        CHECK_EQUAL(presenter->getTimeOff(), "11:31:01");
        CHECK_EQUAL(presenter->getTimeRunning(), "00:00:02");
        CHECK_EQUAL(presenter->getTimeLeft(), "00:03:00");

        keeper->hereStamp = boost::posix_time::not_a_date_time;
        keeper->awayStamp = boost::posix_time::not_a_date_time;
        keeper->interval = boost::posix_time::not_a_date_time;
        keeper->left = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(presenter->getTimeOn(), "00:00:00");
        CHECK_EQUAL(presenter->getTimeOff(), "00:00:00");
        CHECK_EQUAL(presenter->getTimeRunning(), "00:00:00");
        CHECK_EQUAL(presenter->getTimeLeft(), "00:00:00");
    }
}
