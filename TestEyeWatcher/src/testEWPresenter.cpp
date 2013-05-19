#include <unittest++/UnitTest++.h>
#include "EWPresenter.h"
#include "ConfigStub.h"
#include "EWMainFrameStub.h"
#include "ConfigDialogStub.h"
#include "MsgHandlerStub.h"
#include "TimeKeeperStub.h"
#include "PresenceHandlerStub.h"
#include "TimerStub.h"
#include "EWViewObserverStub.h"

struct EWPresenterFixture
{
    public:
        EWPresenterFixture() : msgHandler(NULL), keeper(NULL),
            checkTimer(NULL), clockTimer(NULL), presenter(NULL)
        {
            this->data = {boost::posix_time::seconds(5), boost::posix_time::seconds(3),
                boost::posix_time::seconds(1), boost::posix_time::seconds(2)};
            data.soundAlarm = true;
            try
            {
                this->msgHandler = new MsgHandlerStub();
                this->keeper = new TimeKeeperStub();
                this->checkTimer = new TimerStub();
                this->clockTimer = new TimerStub();
                this->dialog = new OptionsDialogStub();
                this->viewObserver = new EWViewObserverStub();
                this->presenter = new EWPresenter(this->msgHandler,
                    this->keeper, this->checkTimer, this->clockTimer,
                    data.popupAlarm, data.soundAlarm, data.soundPath);

                this->presenter->attach(this->viewObserver);
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
        MsgHandlerStub* msgHandler;
        TimeKeeperStub* keeper;
        TimerStub* checkTimer;
        TimerStub* clockTimer;
        OptionsDialogStub* dialog;
        EWViewObserverStub* viewObserver;

        EWPresenter* presenter;

    protected:
    private:
        void deleteFixture()
        {
            if (this->msgHandler != NULL) {delete this->msgHandler;}
            if (this->keeper != NULL) {delete this->keeper;}
            if (this->checkTimer != NULL) {delete this->checkTimer;}
            if (this->clockTimer != NULL) {delete this->clockTimer;}
            if (this->dialog != NULL) {delete this->dialog;}
            if (this->viewObserver != NULL) {delete this->viewObserver;}
            if (this->presenter != NULL) {delete this->presenter;}
        }
};

SUITE(TestEWPresenter)
{
    /// @todo: move this in future AppController test suite
    /*
    TEST_FIXTURE(EWPresenterFixture, TestValidConfig)
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
            "test.wav"
        };

        CHECK_EQUAL(true, presenter->saveConfig(newData));
        ConfigData returnedData = presenter->getConfigData();

        CHECK_EQUAL(newData.workLength, returnedData.workLength);
        CHECK_EQUAL(newData.pauseLength, returnedData.pauseLength);
        CHECK_EQUAL(newData.remFreq, returnedData.remFreq);
        CHECK_EQUAL(newData.checkFreq, returnedData.checkFreq);
        CHECK_EQUAL(newData.pauseTol, returnedData.pauseTol);
        CHECK_EQUAL(newData.soundAlarm, returnedData.soundAlarm);
        CHECK_EQUAL(newData.popupAlarm, returnedData.popupAlarm);
        CHECK_EQUAL(newData.trayIcon, returnedData.trayIcon);
        CHECK_EQUAL(newData.webcamIndex, returnedData.webcamIndex);
        CHECK_EQUAL(newData.faceSizeX, returnedData.faceSizeX);
        CHECK_EQUAL(newData.faceSizeY, returnedData.faceSizeY);
        CHECK_EQUAL(newData.cascadePath, returnedData.cascadePath);
        CHECK_EQUAL(newData.soundPath, returnedData.soundPath);

        CHECK_EQUAL(newData.cascadePath, this->presHandler->cascadePath);
        CHECK_EQUAL(newData.webcamIndex, this->presHandler->webcamIndex);
        CHECK_EQUAL(newData.faceSizeX, this->presHandler->faceSizeX);
        CHECK_EQUAL(newData.faceSizeY, this->presHandler->faceSizeY);

        CHECK_EQUAL(newData.checkFreq, this->keeper->checkFreq);
        CHECK_EQUAL(newData.pauseLength, this->keeper->pauseLength);
        CHECK_EQUAL(newData.pauseTol, this->keeper->pauseTol);
        CHECK_EQUAL(newData.remFreq, this->keeper->remFreq);
        CHECK_EQUAL(newData.workLength, this->keeper->workLength);
    }

    TEST_FIXTURE(EWPresenterFixture, TestInvalidConfig)
    {
            config->fail = true;
            CHECK_EQUAL(false, presenter->saveConfig(data));
            CHECK_EQUAL("Testing!", msgHandler->lastError);
    }*/

    TEST_FIXTURE(EWPresenterFixture, TestStartStop)
    {
        presenter->toggleStart();
        CHECK_EQUAL(keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(checkTimer->running, true);
        CHECK_EQUAL(clockTimer->running, true);
        CHECK_EQUAL(viewObserver->checkStatUpdated(), true);

        presenter->toggleStart();
        CHECK_EQUAL(keeper->getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(checkTimer->running, false);
        CHECK_EQUAL(clockTimer->running, false);
        CHECK_EQUAL(viewObserver->checkStatUpdated(), true);

        keeper->fail = true;
        CHECK_EQUAL(msgHandler->lastError, "");
        presenter->toggleStart();
        CHECK_EQUAL(keeper->getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(checkTimer->running, false);
        CHECK_EQUAL(clockTimer->running, false);
        CHECK_EQUAL(viewObserver->checkStatUpdated(), false);
        CHECK_EQUAL(msgHandler->lastError, "Testing!");
    }

    TEST_FIXTURE(EWPresenterFixture, TestUpdate)
    {
        CHECK_EQUAL(presenter->getStatus(), "Off");
        CHECK_EQUAL(presenter->getTimeOn(), "10:59:00");
        CHECK_EQUAL(presenter->getTimeOff(), "11:31:01");
        CHECK_EQUAL(presenter->getTimeRunning(), "00:00:02");
        CHECK_EQUAL(presenter->getTimeLeft(), "00:03:00");
        CHECK_EQUAL(msgHandler->lastAlert, "");

        presenter->toggleStart();
        keeper->hereStamp = boost::posix_time::not_a_date_time;
        keeper->awayStamp = boost::posix_time::not_a_date_time;
        keeper->interval = boost::posix_time::not_a_date_time;
        keeper->left = boost::posix_time::not_a_date_time;

        CHECK_EQUAL(presenter->getStatus(), "Here");
        CHECK_EQUAL(presenter->getTimeOn(), "00:00:00");
        CHECK_EQUAL(presenter->getTimeOff(), "00:00:00");
        CHECK_EQUAL(presenter->getTimeRunning(), "00:00:00");
        CHECK_EQUAL(presenter->getTimeLeft(), "00:00:00");
        CHECK_EQUAL(msgHandler->lastAlert, "");
        CHECK_EQUAL(msgHandler->lastSound, "");

        keeper->late = true;
        presenter->togglePause();
        presenter->update(this->checkTimer);
        CHECK_EQUAL(msgHandler->lastAlert, "");
        CHECK_EQUAL(msgHandler->lastSound, "");

        presenter->togglePause();
        presenter->update(this->checkTimer);
        CHECK_EQUAL(msgHandler->lastAlert, presenter->m_LateMsg);
        CHECK_EQUAL(msgHandler->lastSound, data.soundPath);

        keeper->fail = true;
        CHECK_EQUAL(msgHandler->lastError, "");
        presenter->update(this->checkTimer);
        CHECK_EQUAL(msgHandler->lastError, "Testing!");
    }

    TEST_FIXTURE(EWPresenterFixture, TestQuit)
    {
        presenter->quit();
        CHECK_EQUAL(viewObserver->checkQuitUpdated(), true);
    }

    TEST_FIXTURE(EWPresenterFixture, TestPauseButtonsLabels)
    {
        CHECK_EQUAL(presenter->getPauseButtonLabel(), presenter->m_PauseBtnLabel);
        presenter->togglePause();
        CHECK_EQUAL(presenter->getPauseButtonLabel(), presenter->m_ResumeBtnLabel);
    }

    TEST_FIXTURE(EWPresenterFixture, TestStartButtonsLabels)
    {
        CHECK_EQUAL(presenter->getStartButtonLabel(), presenter->m_StartBtnLabel);
        presenter->toggleStart();
        CHECK_EQUAL(presenter->getStartButtonLabel(), presenter->m_StopBtnLabel);
    }

    TEST_FIXTURE(EWPresenterFixture, TestHideButtonsLabels)
    {
        CHECK_EQUAL(presenter->getHideButtonLabel(), presenter->m_HideBtnLabel);
        CHECK_EQUAL(true, presenter->isShown());

        presenter->show(false);
        CHECK_EQUAL(presenter->getHideButtonLabel(), presenter->m_RestoreBtnLabel);
        CHECK_EQUAL(false, presenter->isShown());

        presenter->show(true);
        CHECK_EQUAL(presenter->getHideButtonLabel(), presenter->m_HideBtnLabel);
        CHECK_EQUAL(true, presenter->isShown());
    }

    TEST_FIXTURE(EWPresenterFixture, TestIconName)
    {
        CHECK_EQUAL(presenter->getIconName(), presenter->m_StopWebcamIcon);

        presenter->toggleStart();
        keeper->workLeft = boost::posix_time::hours(1);
        CHECK_EQUAL(presenter->getIconName(), presenter->m_GreenWebcamIcon);

        keeper->workLeft = boost::posix_time::seconds(1);
        CHECK_EQUAL(presenter->getIconName(), presenter->m_YellowWebcamIcon);

        keeper->workLeft = boost::posix_time::seconds(0);
        CHECK_EQUAL(presenter->getIconName(), presenter->m_RedWebcamIcon);

        keeper->status = AbstractTimeKeeper::AWAY;
        keeper->left = boost::posix_time::seconds(0);
        CHECK_EQUAL(presenter->getIconName(), presenter->m_GreenWebcamIcon);
    }

    TEST_FIXTURE(EWPresenterFixture, TestUpdateTime)
    {
        presenter->update(this->clockTimer);
        CHECK_EQUAL(viewObserver->checkTimeUpdated(), true);
    }
}
