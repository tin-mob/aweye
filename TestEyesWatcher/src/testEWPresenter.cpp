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

    TEST_FIXTURE(EWPresenterFixture, TestNegatives)
    {

        this->presenter.toggleStart();
        this->keeper.left = boost::posix_time::hours(-1) +
            boost::posix_time::minutes(-1) + boost::posix_time::seconds(-1);

        CHECK_EQUAL("-01:01:01", this->presenter.getTimeLeft());
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
        this->presenter.toggleStart();
        this->clockTimer.ring();
        CHECK_EQUAL(this->viewObserver.checkTimeUpdated(), true);
        CHECK_EQUAL(this->keeper.hibernated, false);
    }

    TEST_FIXTURE(EWPresenterFixture, TestHibernated)
    {
        this->presenter.toggleStart();
        this->timeHandler.setTime(this->timeHandler.getTime() + boost::posix_time::minutes(2));
        this->clockTimer.ring();
        CHECK_EQUAL(this->viewObserver.checkTimeUpdated(), true);
        CHECK_EQUAL(this->keeper.hibernated, true);
    }
}
