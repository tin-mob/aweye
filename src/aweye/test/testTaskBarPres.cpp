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


#include "aweye/core/TaskBarPres.h"
#include "aweye/test/EventHandlerStub.h"
#include "aweye/test/TaskBarStub.h"
#include "aweye/test/TKControllerStub.h"

#include <unittest++/UnitTest++.h>

namespace Aweye
{
struct TaskBarPresFixture
{
    TaskBarPresFixture() : bar(), pres(), handler(), barPres(bar, pres, handler)
    {
    }
    ~TaskBarPresFixture() {}

    TaskBarStub bar;
    TKControllerStub pres;
    EventHandlerStub handler;
    TaskBarPres barPres;
};

SUITE(TestTaskBarPres)
{
    TEST_FIXTURE(TaskBarPresFixture, TestTimesUpdate)
    {
        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues();
        pres.setDisplayValues(values);
        pres.notifyTime();

        CHECK_EQUAL("Last Session : " + values.timeOn, bar.m_OnClock);
        CHECK_EQUAL("Last Pause : " + values.timeOff, bar.m_OffClock);
        CHECK_EQUAL("Running : " + values.timeRunning, bar.m_RunningClock);
        CHECK_EQUAL("Time Left : " + values.timeLeft, bar.m_LeftClock);
        CHECK_EQUAL(values.icon, bar.m_Loc);
    }

    TEST_FIXTURE(TaskBarPresFixture, TestTimesUpdateNoIcon)
    {
        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues(true, false);
        bar.m_Loc = "in";
        pres.setDisplayValues(values);
        pres.notifyTime();

        CHECK_EQUAL("Last Session : " + values.timeOn, bar.m_OnClock);
        CHECK_EQUAL("Last Pause : " + values.timeOff, bar.m_OffClock);
        CHECK_EQUAL("Running : " + values.timeRunning, bar.m_RunningClock);
        CHECK_EQUAL("Time Left : " + values.timeLeft, bar.m_LeftClock);
        CHECK_EQUAL("in", bar.m_Loc);
    }

    TEST_FIXTURE(TaskBarPresFixture, TestStatusUpdate)
    {
        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues();
        pres.setDisplayValues(values);
        pres.notifyStatus();

        CHECK_EQUAL(values.hideButtonLabel, bar.m_HideRestoreLabel);
        CHECK_EQUAL(values.startButtonLabel, bar.m_StartStopLabel);
        CHECK_EQUAL(values.pauseButtonLabel, bar.m_PauseResumeLabel);
        CHECK_EQUAL(values.icon, bar.m_Loc);
    }

    TEST_FIXTURE(TaskBarPresFixture, TestStatusUpdateNoIcon)
    {
        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues(true, false);
        bar.m_Loc = "in";
        pres.setDisplayValues(values);
        pres.notifyStatus();

        CHECK_EQUAL(values.hideButtonLabel, bar.m_HideRestoreLabel);
        CHECK_EQUAL(values.startButtonLabel, bar.m_StartStopLabel);
        CHECK_EQUAL(values.pauseButtonLabel, bar.m_PauseResumeLabel);
        CHECK_EQUAL("in", bar.m_Loc);
    }

    TEST_FIXTURE(TaskBarPresFixture, TestForceUpdate)
    {
        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues();
        pres.setDisplayValues(values);
        handler.forceUpdate();

        CHECK_EQUAL("Last Session : " + values.timeOn, bar.m_OnClock);
        CHECK_EQUAL("Last Pause : " + values.timeOff, bar.m_OffClock);
        CHECK_EQUAL("Running : " + values.timeRunning, bar.m_RunningClock);
        CHECK_EQUAL("Time Left : " + values.timeLeft, bar.m_LeftClock);
        CHECK_EQUAL(values.hideButtonLabel, bar.m_HideRestoreLabel);
        CHECK_EQUAL(values.startButtonLabel, bar.m_StartStopLabel);
        CHECK_EQUAL(values.pauseButtonLabel, bar.m_PauseResumeLabel);
        CHECK_EQUAL(values.icon, bar.m_Loc);
    }
}
}
