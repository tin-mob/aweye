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

struct EWPresenterFixture
{
    public:
        EWPresenterFixture() :
            data({boost::posix_time::seconds(5), boost::posix_time::seconds(3),
                boost::posix_time::seconds(1), boost::posix_time::seconds(2)}),
            msgHandler(), timeHandler(), keeper(), checkTimer(), clockTimer(),
            dialog(), viewObserver(),
            presenter(EWPresenter(&msgHandler, &keeper, &checkTimer,
                &clockTimer, &timeHandler, data.popupAlarm, true, data.soundPath))
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
    TEST_FIXTURE(EWPresenterFixture, TestStartStop)
    {
        presenter.toggleStart();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(checkTimer.running, true);
        CHECK_EQUAL(clockTimer.running, true);
        CHECK_EQUAL(viewObserver.checkStatUpdated(), true);

        presenter.toggleStart();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(checkTimer.running, false);
        CHECK_EQUAL(clockTimer.running, false);
        CHECK_EQUAL(viewObserver.checkStatUpdated(), true);

        keeper.m_Fail = true;
        CHECK_EQUAL(msgHandler.m_LastError, "");
        presenter.toggleStart();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(checkTimer.running, false);
        CHECK_EQUAL(clockTimer.running, false);
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

        keeper.m_Late = true;
        presenter.togglePause();
        checkTimer.ring();
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");

        presenter.togglePause();
        checkTimer.ring();
        CHECK_EQUAL(msgHandler.m_LastAlert, presenter.m_LateMsg);
        CHECK_EQUAL(msgHandler.m_LastSound, data.soundPath);

        keeper.m_Fail = true;
        CHECK_EQUAL(msgHandler.m_LastError, "");
        checkTimer.ring();
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
        CHECK_EQUAL(keeper.m_Hibernated, false);
    }

    TEST_FIXTURE(EWPresenterFixture, TestHibernated)
    {
        presenter.toggleStart();
        keeper.m_Status = AbstractTimeKeeper::OFF;
        timeHandler.setTime(timeHandler.getTime() + boost::posix_time::minutes(2));
        clockTimer.ring();
        CHECK_EQUAL(viewObserver.checkTimeUpdated(), true);
        CHECK_EQUAL(keeper.m_Hibernated, true);
        CHECK_EQUAL(keeper.m_Status, AbstractTimeKeeper::HERE);
    }
}
