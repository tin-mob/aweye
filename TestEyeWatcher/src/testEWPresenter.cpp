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
        EWPresenterFixture() :
            data({boost::posix_time::seconds(5), boost::posix_time::seconds(3),
                boost::posix_time::seconds(1), boost::posix_time::seconds(2)}),
            msgHandler(), keeper(), checkTimer(), clockTimer(), dialog(), viewObserver(),
            presenter(EWPresenter(&msgHandler, &keeper, &checkTimer,
                &clockTimer, data.popupAlarm, true, data.soundPath))
        {
            data.soundAlarm = true;
            presenter.attach(&viewObserver);
        }
        ~EWPresenterFixture()
        {
        }

        ConfigData data;
        MsgHandlerStub msgHandler;
        TimeKeeperStub keeper;
        TimerStub checkTimer;
        TimerStub clockTimer;
        OptionsDialogStub dialog;
        EWViewObserverStub viewObserver;
        EWPresenter presenter;

    protected:
    private:
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

        CHECK_EQUAL(true, this->presenter.saveConfig(newData));
        ConfigData returnedData = this->presenter.getConfigData();

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

        CHECK_EQUAL(newData.checkFreq, this->keeper.checkFreq);
        CHECK_EQUAL(newData.pauseLength, this->keeper.pauseLength);
        CHECK_EQUAL(newData.pauseTol, this->keeper.pauseTol);
        CHECK_EQUAL(newData.remFreq, this->keeper.remFreq);
        CHECK_EQUAL(newData.workLength, this->keeper.workLength);
    }

    TEST_FIXTURE(EWPresenterFixture, TestInvalidConfig)
    {
            config->fail = true;
            CHECK_EQUAL(false, this->presenter.saveConfig(data));
            CHECK_EQUAL("Testing!", this->msgHandler.lastError);
    }*/

    TEST_FIXTURE(EWPresenterFixture, TestStartStop)
    {
        this->presenter.toggleStart();
        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->checkTimer.running, true);
        CHECK_EQUAL(this->clockTimer.running, true);
        CHECK_EQUAL(this->viewObserver.checkStatUpdated(), true);

        this->presenter.toggleStart();
        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(this->checkTimer.running, false);
        CHECK_EQUAL(this->clockTimer.running, false);
        CHECK_EQUAL(this->viewObserver.checkStatUpdated(), true);

        this->keeper.fail = true;
        CHECK_EQUAL(this->msgHandler.lastError, "");
        this->presenter.toggleStart();
        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(this->checkTimer.running, false);
        CHECK_EQUAL(this->clockTimer.running, false);
        CHECK_EQUAL(this->viewObserver.checkStatUpdated(), false);
        CHECK_EQUAL(this->msgHandler.lastError, "Testing!");
    }

    TEST_FIXTURE(EWPresenterFixture, TestUpdate)
    {
        CHECK_EQUAL(this->presenter.getStatus(), "Off");
        CHECK_EQUAL(this->presenter.getTimeOn(), "10:59:00");
        CHECK_EQUAL(this->presenter.getTimeOff(), "11:31:01");
        CHECK_EQUAL(this->presenter.getTimeRunning(), "00:00:02");
        CHECK_EQUAL(this->presenter.getTimeLeft(), "00:03:00");
        CHECK_EQUAL(this->msgHandler.lastAlert, "");

        this->presenter.toggleStart();
        this->keeper.hereStamp = boost::posix_time::not_a_date_time;
        this->keeper.awayStamp = boost::posix_time::not_a_date_time;
        this->keeper.interval = boost::posix_time::not_a_date_time;
        this->keeper.left = boost::posix_time::not_a_date_time;

        CHECK_EQUAL(this->presenter.getStatus(), "Here");
        CHECK_EQUAL(this->presenter.getTimeOn(), "00:00:00");
        CHECK_EQUAL(this->presenter.getTimeOff(), "00:00:00");
        CHECK_EQUAL(this->presenter.getTimeRunning(), "00:00:00");
        CHECK_EQUAL(this->presenter.getTimeLeft(), "00:00:00");
        CHECK_EQUAL(this->msgHandler.lastAlert, "");
        CHECK_EQUAL(this->msgHandler.lastSound, "");

        this->keeper.late = true;
        this->presenter.togglePause();
        this->checkTimer.ring();
        CHECK_EQUAL(this->msgHandler.lastAlert, "");
        CHECK_EQUAL(this->msgHandler.lastSound, "");

        this->presenter.togglePause();
        this->checkTimer.ring();
        CHECK_EQUAL(this->msgHandler.lastAlert, this->presenter.m_LateMsg);
        CHECK_EQUAL(this->msgHandler.lastSound, data.soundPath);

        this->keeper.fail = true;
        CHECK_EQUAL(this->msgHandler.lastError, "");
        this->checkTimer.ring();
        CHECK_EQUAL(this->msgHandler.lastError, "Testing!");
    }

    TEST_FIXTURE(EWPresenterFixture, TestQuit)
    {
        this->presenter.quit();
        CHECK_EQUAL(this->viewObserver.checkQuitUpdated(), true);
    }

    TEST_FIXTURE(EWPresenterFixture, TestPauseButtonsLabels)
    {
        CHECK_EQUAL(this->presenter.getPauseButtonLabel(), this->presenter.m_PauseBtnLabel);
        this->presenter.togglePause();
        CHECK_EQUAL(this->presenter.getPauseButtonLabel(), this->presenter.m_ResumeBtnLabel);
    }

    TEST_FIXTURE(EWPresenterFixture, TestStartButtonsLabels)
    {
        CHECK_EQUAL(this->presenter.getStartButtonLabel(), this->presenter.m_StartBtnLabel);
        this->presenter.toggleStart();
        CHECK_EQUAL(this->presenter.getStartButtonLabel(), this->presenter.m_StopBtnLabel);
    }

    TEST_FIXTURE(EWPresenterFixture, TestHideButtonsLabels)
    {
        CHECK_EQUAL(this->presenter.getHideButtonLabel(), this->presenter.m_HideBtnLabel);
        CHECK_EQUAL(true, this->presenter.isShown());

        this->presenter.show(false);
        CHECK_EQUAL(this->presenter.getHideButtonLabel(), this->presenter.m_RestoreBtnLabel);
        CHECK_EQUAL(false, this->presenter.isShown());

        this->presenter.show(true);
        CHECK_EQUAL(this->presenter.getHideButtonLabel(), this->presenter.m_HideBtnLabel);
        CHECK_EQUAL(true, this->presenter.isShown());
    }

    TEST_FIXTURE(EWPresenterFixture, TestIconName)
    {
        CHECK_EQUAL(this->presenter.getIconName(), this->presenter.m_StopWebcamIcon);

        this->presenter.toggleStart();
        this->keeper.workLeft = boost::posix_time::hours(1);
        CHECK_EQUAL(this->presenter.getIconName(), this->presenter.m_GreenWebcamIcon);

        this->keeper.workLeft = boost::posix_time::seconds(1);
        CHECK_EQUAL(this->presenter.getIconName(), this->presenter.m_YellowWebcamIcon);

        this->keeper.workLeft = boost::posix_time::seconds(0);
        CHECK_EQUAL(this->presenter.getIconName(), this->presenter.m_RedWebcamIcon);

        this->keeper.status = AbstractTimeKeeper::AWAY;
        this->keeper.left = boost::posix_time::seconds(0);
        CHECK_EQUAL(this->presenter.getIconName(), this->presenter.m_GreenWebcamIcon);
    }

    TEST_FIXTURE(EWPresenterFixture, TestUpdateTime)
    {
        this->clockTimer.ring();
        CHECK_EQUAL(this->viewObserver.checkTimeUpdated(), true);
    }
}
