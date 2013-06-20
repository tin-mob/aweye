/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include <unittest++/UnitTest++.h>
#include "EWPresenter.h"
#include "ConfigStub.h"
#include "EWMainFrameStub.h"
#include "OptionsDialogStub.h"
#include "MsgHandlerStub.h"
#include "TimeHandlerStub.h"
#include "TimeKeeperStub.h"
#include "PresenceHandlerStub.h"
#include "TimerStub.h"
#include "EWViewObserverStub.h"

namespace EW
{
struct EWPresenterFixture
{
    public:
        EWPresenterFixture() :
            data({boost::posix_time::seconds(5), boost::posix_time::seconds(3),
                boost::posix_time::seconds(1), boost::posix_time::seconds(2)}),
            msgHandler(), timeHandler(), keeper(), clockTimer(),
            dialog(), viewObserver(),
            presenter(EWPresenter(msgHandler, keeper,
                clockTimer, timeHandler, data.popupAlarm, true, data.soundPath))
        {
            data.soundAlarm = true;
            presenter.attach(&viewObserver);
        }
        ~EWPresenterFixture()
        {
        }

        ConfigData data;
        MsgHandlerStub msgHandler;
        TimeHandlerStub timeHandler;
        TimeKeeperStub keeper;
        TimerStub clockTimer;
        OptionsDialogStub dialog;
        EWViewObserverStub viewObserver;
        EWPresenter presenter;

    protected:
    private:
};

SUITE(TestEWPresenter)
{
    TEST_FIXTURE(EWPresenterFixture, TestStartStop)
    {
        presenter.toggleStart();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(1000, clockTimer.m_Running);
        CHECK_EQUAL(viewObserver.checkStatUpdated(), true);

        presenter.toggleStart();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(clockTimer.m_Running, 0);
        CHECK_EQUAL(viewObserver.checkStatUpdated(), true);

        keeper.m_Fail = true;
        CHECK_EQUAL(msgHandler.m_LastError, "");
        presenter.toggleStart();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(clockTimer.m_Running, 0);
        CHECK_EQUAL(viewObserver.checkStatUpdated(), false);
        CHECK_EQUAL(msgHandler.m_LastError, "Testing!");
    }

    TEST_FIXTURE(EWPresenterFixture, TestUpdate)
    {
        CHECK_EQUAL(presenter.getStatus(), "Off");
        CHECK_EQUAL(presenter.getTimeOn(), "10:59:00");
        CHECK_EQUAL(presenter.getTimeOff(), "11:31:01");
        CHECK_EQUAL(presenter.getTimeRunning(), "00:00:02");
        CHECK_EQUAL(presenter.getTimeLeft(), "00:03:00");
        CHECK_EQUAL(msgHandler.m_LastAlert, "");

        presenter.toggleStart();
        keeper.m_HereStamp = boost::posix_time::not_a_date_time;
        keeper.m_AwayStamp = boost::posix_time::not_a_date_time;
        keeper.m_Interval = boost::posix_time::not_a_date_time;
        keeper.m_Left = boost::posix_time::not_a_date_time;

        CHECK_EQUAL(presenter.getStatus(), "Here");
        CHECK_EQUAL(presenter.getTimeOn(), "00:00:00");
        CHECK_EQUAL(presenter.getTimeOff(), "00:00:00");
        CHECK_EQUAL(presenter.getTimeRunning(), "00:00:00");
        CHECK_EQUAL(presenter.getTimeLeft(), "00:00:00");
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");

        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(EWPresenterFixture, TestAlert)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        presenter.toggleStart();
        presenter.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, presenter.m_LateMsg);
        CHECK_EQUAL(msgHandler.m_LastSound, data.soundPath);
    }

    TEST_FIXTURE(EWPresenterFixture, TestAlertPaused)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        presenter.toggleStart();
        presenter.togglePause();
        presenter.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(EWPresenterFixture, TestNoAlertAway)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        keeper.m_Status = AbstractTimeKeeper::AWAY;
        presenter.toggleStart();
        presenter.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(EWPresenterFixture, TestNoAlertTooSoon)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        presenter.toggleStart();
        presenter.onTimerRing(&clockTimer);
        msgHandler.m_LastAlert = "";
        msgHandler.m_LastSound = "";
        presenter.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(EWPresenterFixture, TestNoAlertSoonEnough)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        presenter.toggleStart();
        presenter.onTimerRing(&clockTimer);
        msgHandler.m_LastAlert = "";
        msgHandler.m_LastSound = "";
        timeHandler.setTime(timeHandler.getTime() + keeper.getRemFreq());
        presenter.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, presenter.m_LateMsg);
        CHECK_EQUAL(msgHandler.m_LastSound, data.soundPath);
    }

    TEST_FIXTURE(EWPresenterFixture, TestAlertTolerating)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        keeper.m_Tolerating = true;
        presenter.toggleStart();
        presenter.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(EWPresenterFixture, TestFail)
    {
        keeper.m_Fail = true;
        CHECK_EQUAL(msgHandler.m_LastError, "");
        presenter.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastError, "Testing!");
    }

    TEST_FIXTURE(EWPresenterFixture, TestNegatives)
    {

        presenter.toggleStart();
        keeper.m_Left = boost::posix_time::hours(-1) +
            boost::posix_time::minutes(-1) + boost::posix_time::seconds(-1);

        CHECK_EQUAL("-01:01:01", presenter.getTimeLeft());
    }

    TEST_FIXTURE(EWPresenterFixture, TestQuit)
    {
        presenter.quit();
        CHECK_EQUAL(viewObserver.checkQuitUpdated(), true);
    }

    TEST_FIXTURE(EWPresenterFixture, TestPauseButtonsLabels)
    {
        CHECK_EQUAL(presenter.getPauseButtonLabel(), presenter.m_PauseBtnLabel);
        presenter.togglePause();
        CHECK_EQUAL(presenter.getPauseButtonLabel(), presenter.m_ResumeBtnLabel);
    }

    TEST_FIXTURE(EWPresenterFixture, TestStartButtonsLabels)
    {
        CHECK_EQUAL(presenter.getStartButtonLabel(), presenter.m_StartBtnLabel);
        presenter.toggleStart();
        CHECK_EQUAL(presenter.getStartButtonLabel(), presenter.m_StopBtnLabel);
    }

    TEST_FIXTURE(EWPresenterFixture, TestHideButtonsLabels)
    {
        CHECK_EQUAL(presenter.getHideButtonLabel(), presenter.m_HideBtnLabel);
        CHECK_EQUAL(true, presenter.isShown());

        presenter.show(false);
        CHECK_EQUAL(presenter.getHideButtonLabel(), presenter.m_RestoreBtnLabel);
        CHECK_EQUAL(false, presenter.isShown());

        presenter.show(true);
        CHECK_EQUAL(presenter.getHideButtonLabel(), presenter.m_HideBtnLabel);
        CHECK_EQUAL(true, presenter.isShown());
    }

    TEST_FIXTURE(EWPresenterFixture, TestIconName)
    {
        CHECK_EQUAL(presenter.getIconName(), presenter.m_StopWebcamIcon);

        presenter.toggleStart();
        keeper.m_WorkLeft = boost::posix_time::hours(1);
        CHECK_EQUAL(presenter.getIconName(), presenter.m_GreenWebcamIcon);

        keeper.m_WorkLeft = boost::posix_time::seconds(1);
        CHECK_EQUAL(presenter.getIconName(), presenter.m_YellowWebcamIcon);

        keeper.m_WorkLeft = boost::posix_time::seconds(0);
        CHECK_EQUAL(presenter.getIconName(), presenter.m_RedWebcamIcon);

        keeper.m_Status = AbstractTimeKeeper::AWAY;
        keeper.m_Left = boost::posix_time::seconds(0);
        CHECK_EQUAL(presenter.getIconName(), presenter.m_GreenWebcamIcon);
    }

    TEST_FIXTURE(EWPresenterFixture, TestUpdateTime)
    {
        presenter.toggleStart();
        clockTimer.ring();
        CHECK_EQUAL(viewObserver.checkTimeUpdated(), true);
    }
}
}
