#include <unittest++/UnitTest++.h>
#include "EWPresenter.h"
#include "ConfigStub.h"
#include "EWMainFrameStub.h"
#include "ConfigDialogStub.h"
#include "MsgHandlerStub.h"
#include "TimeKeeperStub.h"

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
                this->frame = new EWMainFrameStub();
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
        EWMainFrameStub* frame;
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

        /// @todo : different values

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
        CHECK_EQUAL(frame->running, false);
        presenter->updateTimes(frame);
        CHECK_EQUAL(frame->status, AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::OFF));

        presenter->start(frame);
        presenter->updateTimes(frame);
        CHECK_EQUAL(frame->running, true);
        CHECK_EQUAL(frame->status, AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::HERE));

        presenter->stop(frame);
        presenter->updateTimes(frame);
        CHECK_EQUAL(frame->running, false);
        CHECK_EQUAL(frame->status, AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::OFF));

        keeper->fail = true;
        CHECK_EQUAL(msgHandler->lastError, "");
        presenter->start(frame);
        presenter->updateTimes(frame);
        CHECK_EQUAL(msgHandler->lastError, "Testing!");
    }

    TEST_FIXTURE(EWPresenterFixture, TestUpdate)
    {
        presenter->updateTimes(frame);
        CHECK_EQUAL(frame->status, AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::OFF));
        presenter->updateStatus(frame);
        presenter->updateTimes(frame);
        CHECK_EQUAL(frame->running, true);
        CHECK_EQUAL(frame->lastTotal, 1000);
        CHECK_EQUAL(frame->status, AbstractTimeKeeper::getStatusStr(AbstractTimeKeeper::HERE));
        CHECK_EQUAL(frame->onClock, "10:59:00");
        CHECK_EQUAL(frame->offClock, "11:31:01");
        CHECK_EQUAL(frame->runningClock, "00:00:02");
        CHECK_EQUAL(frame->leftClock, "00:03:00");
        CHECK_EQUAL(msgHandler->lastAlert, "");

        keeper->hereStamp = boost::posix_time::not_a_date_time;
        keeper->awayStamp = boost::posix_time::not_a_date_time;
        keeper->interval = boost::posix_time::not_a_date_time;
        keeper->left = boost::posix_time::not_a_date_time;

        presenter->updateStatus(frame);
        presenter->updateTimes(frame);
        CHECK_EQUAL(frame->onClock, "00:00:00");
        CHECK_EQUAL(frame->offClock, "00:00:00");
        CHECK_EQUAL(frame->runningClock, "00:00:00");
        CHECK_EQUAL(frame->leftClock, "00:00:00");

        keeper->late = true;
        presenter->updateStatus(frame);
        CHECK_EQUAL(msgHandler->lastAlert, presenter->m_LateMsg);

        keeper->fail = true;
        CHECK_EQUAL(msgHandler->lastError, "");
        presenter->updateStatus(frame);
        CHECK_EQUAL(msgHandler->lastError, "Testing!");
    }
}
