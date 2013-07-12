/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "aweye/TKController.h"
#include "aweye/test/ConfigStub.h"
#include "aweye/test/MainFrameStub.h"
#include "aweye/test/MsgHandlerStub.h"
#include "aweye/test/OptionsDialogStub.h"
#include "aweye/test/PresenceHandlerStub.h"
#include "aweye/test/TimeHandlerStub.h"
#include "aweye/test/TimeKeeperStub.h"
#include "aweye/test/TimerStub.h"
#include "aweye/test/TKControllerObserverStub.h"
#include "aweye/test/UtilsStub.h"

#include <unittest++/UnitTest++.h>

namespace Aweye
{
struct TKControllerFixture
{
    public:
        TKControllerFixture() :
            utils("", "path/"), data(ConfigData::getDefault(utils.m_DataDir)),
            msgHandler(), timeHandler(), keeper(), clockTimer(),
            dialog(), viewObserver(),
            controller(TKController(msgHandler, keeper,
                clockTimer, timeHandler, utils, data.popupAlarm, true, data.soundPath))
        {
            data.soundAlarm = true;
            controller.attach(&viewObserver);
        }
        ~TKControllerFixture()
        {
        }

        UtilsStub utils;
        ConfigData data;
        MsgHandlerStub msgHandler;
        TimeHandlerStub timeHandler;
        TimeKeeperStub keeper;
        TimerStub clockTimer;
        OptionsDialogStub dialog;
        TKControllerObserverStub viewObserver;
        TKController controller;

    protected:
    private:
};

SUITE(TestTKController)
{
    TEST_FIXTURE(TKControllerFixture, TestStartStop)
    {
        controller.toggleStart();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(1000, clockTimer.m_Running);
        CHECK_EQUAL(viewObserver.checkStatUpdated(), true);

        controller.toggleStart();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(clockTimer.m_Running, 0);
        CHECK_EQUAL(viewObserver.checkStatUpdated(), true);
    }

    TEST_FIXTURE(TKControllerFixture, TestStartFail)
    {
        keeper.m_Fail = true;
        CHECK_EQUAL(msgHandler.m_LastError, "");
        controller.toggleStart();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(clockTimer.m_Running, 0);
        CHECK_EQUAL(viewObserver.checkStatUpdated(), true);
        CHECK_EQUAL(msgHandler.m_LastError, "Testing!");
    }

    TEST_FIXTURE(TKControllerFixture, TestUpdate)
    {
        CHECK_EQUAL(controller.getStatus(), "Off");
        CHECK_EQUAL(controller.getTimeOn(), "10:59:00");
        CHECK_EQUAL(controller.getTimeOff(), "11:31:01");
        CHECK_EQUAL(controller.getTimeRunning(), "00:00:02");
        CHECK_EQUAL(controller.getTimeLeft(), "00:03:00");
        CHECK_EQUAL(msgHandler.m_LastAlert, "");

        controller.toggleStart();
        keeper.m_HereStamp = boost::posix_time::not_a_date_time;
        keeper.m_AwayStamp = boost::posix_time::not_a_date_time;
        keeper.m_Interval = boost::posix_time::not_a_date_time;
        keeper.m_Left = boost::posix_time::not_a_date_time;

        CHECK_EQUAL(controller.getStatus(), "Here");
        CHECK_EQUAL(controller.getTimeOn(), "00:00:00");
        CHECK_EQUAL(controller.getTimeOff(), "00:00:00");
        CHECK_EQUAL(controller.getTimeRunning(), "00:00:00");
        CHECK_EQUAL(controller.getTimeLeft(), "00:00:00");
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");

        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(TKControllerFixture, TestAlert)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        controller.toggleStart();
        controller.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, controller.m_LateMsg);
        CHECK_EQUAL(msgHandler.m_LastSound, data.soundPath);
    }

    TEST_FIXTURE(TKControllerFixture, TestAlertPaused)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        controller.toggleStart();
        controller.togglePause();
        controller.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(TKControllerFixture, TestNoAlertAway)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        keeper.m_Status = AbstractTimeKeeper::AWAY;
        controller.toggleStart();
        controller.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(TKControllerFixture, TestNoAlertTooSoon)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        controller.toggleStart();
        controller.onTimerRing(&clockTimer);
        msgHandler.m_LastAlert = "";
        msgHandler.m_LastSound = "";
        controller.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(TKControllerFixture, TestNoAlertSoonEnough)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        controller.toggleStart();
        controller.onTimerRing(&clockTimer);
        msgHandler.m_LastAlert = "";
        msgHandler.m_LastSound = "";
        timeHandler.setTime(timeHandler.getTime() + keeper.getRemFreq());
        controller.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, controller.m_LateMsg);
        CHECK_EQUAL(msgHandler.m_LastSound, data.soundPath);
    }

    TEST_FIXTURE(TKControllerFixture, TestAlertTolerating)
    {
        keeper.m_Updated = true;
        keeper.m_Late = true;
        keeper.m_Tolerating = true;
        controller.toggleStart();
        controller.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastAlert, "");
        CHECK_EQUAL(msgHandler.m_LastSound, "");
    }

    TEST_FIXTURE(TKControllerFixture, TestFail)
    {
        keeper.m_Fail = true;
        CHECK_EQUAL(msgHandler.m_LastError, "");
        controller.onTimerRing(&clockTimer);
        CHECK_EQUAL(msgHandler.m_LastError, "Testing!");
    }

    TEST_FIXTURE(TKControllerFixture, TestNegatives)
    {

        controller.toggleStart();
        keeper.m_Left = boost::posix_time::hours(-1) +
            boost::posix_time::minutes(-1) + boost::posix_time::seconds(-1);

        CHECK_EQUAL("-01:01:01", controller.getTimeLeft());
    }

    TEST_FIXTURE(TKControllerFixture, TestQuit)
    {
        controller.quit();
        CHECK_EQUAL(viewObserver.checkQuitUpdated(), true);
    }

    TEST_FIXTURE(TKControllerFixture, TestPauseButtonsLabels)
    {
        CHECK_EQUAL(controller.getPauseButtonLabel(), controller.m_PauseBtnLabel);
        controller.togglePause();
        CHECK_EQUAL(controller.getPauseButtonLabel(), controller.m_ResumeBtnLabel);
    }

    TEST_FIXTURE(TKControllerFixture, TestStartButtonsLabels)
    {
        CHECK_EQUAL(controller.getStartButtonLabel(), controller.m_StartBtnLabel);
        controller.toggleStart();
        CHECK_EQUAL(controller.getStartButtonLabel(), controller.m_StopBtnLabel);
    }

    TEST_FIXTURE(TKControllerFixture, TestHideButtonsLabels)
    {
        CHECK_EQUAL(controller.getHideButtonLabel(), controller.m_HideBtnLabel);
        CHECK_EQUAL(true, controller.isShown());

        controller.show(false);
        CHECK_EQUAL(controller.getHideButtonLabel(), controller.m_RestoreBtnLabel);
        CHECK_EQUAL(false, controller.isShown());

        controller.show(true);
        CHECK_EQUAL(controller.getHideButtonLabel(), controller.m_HideBtnLabel);
        CHECK_EQUAL(true, controller.isShown());
    }

    TEST_FIXTURE(TKControllerFixture, TestIconName)
    {
        CHECK_EQUAL(controller.getIconName(), utils.getDataPath(controller.m_StopWebcamIcon));

        controller.toggleStart();
        keeper.m_WorkLeft = boost::posix_time::hours(1);
        CHECK_EQUAL(controller.getIconName(), utils.getDataPath(controller.m_GreenWebcamIcon));

        keeper.m_WorkLeft = boost::posix_time::seconds(1);
        CHECK_EQUAL(controller.getIconName(), utils.getDataPath(controller.m_YellowWebcamIcon));

        keeper.m_WorkLeft = boost::posix_time::seconds(0);
        CHECK_EQUAL(controller.getIconName(), utils.getDataPath(controller.m_RedWebcamIcon));

        keeper.m_Status = AbstractTimeKeeper::AWAY;
        keeper.m_Left = boost::posix_time::seconds(0);
        CHECK_EQUAL(controller.getIconName(), utils.getDataPath(controller.m_GreenWebcamIcon));
    }

    TEST_FIXTURE(TKControllerFixture, TestUpdateTime)
    {
        controller.toggleStart();
        clockTimer.ring();
        CHECK_EQUAL(viewObserver.checkTimeUpdated(), true);
    }
}
}
