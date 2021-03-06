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


#include "aweye/core/MainFramePres.h"
#include "aweye/test/EventHandlerStub.h"
#include "aweye/test/MainFrameStub.h"
#include "aweye/test/TKControllerStub.h"

#include <UnitTest++.h>

namespace Aweye
{
struct MainFramePresFixture
{
    MainFramePresFixture() : frame(), pres(), handler(), framePres(frame, pres, handler)
    {
    }
    ~MainFramePresFixture() {}

    MainFrameStub frame;
    TKControllerStub pres;
    EventHandlerStub handler;
    MainFramePres framePres;
};

SUITE(TestMainFramePres)
{
    TEST_FIXTURE(MainFramePresFixture, TestStatusUpdate)
    {
        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues();
        pres.setDisplayValues(values);
        pres.notifyStatus();

        CHECK_EQUAL(false, frame.m_Closed);
        CHECK_EQUAL(values.pauseButtonLabel, frame.m_PauseLabel);
        CHECK_EQUAL(values.startButtonLabel, frame.m_StartLabel);
        CHECK_EQUAL(values.status, frame.m_Status);
        CHECK_EQUAL(values.timeOn, frame.m_OnClock);
        CHECK_EQUAL(values.timeOff, frame.m_OffClock);
        CHECK_EQUAL(values.timeRunning, frame.m_RunningClock);
        CHECK_EQUAL(values.timeLeft, frame.m_LeftClock);
        CHECK_EQUAL(values.shown, frame.m_Shown);
    }

    TEST_FIXTURE(MainFramePresFixture, TestStatusUpdateNoShow)
    {
        frame.m_Shown = true;

        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues(false);
        pres.setDisplayValues(values);
        pres.notifyStatus();

        CHECK_EQUAL(false, frame.m_Closed);
        CHECK_EQUAL("", frame.m_PauseLabel);
        CHECK_EQUAL("", frame.m_StartLabel);
        CHECK_EQUAL("", frame.m_Status);
        CHECK_EQUAL("", frame.m_OnClock);
        CHECK_EQUAL("", frame.m_OffClock);
        CHECK_EQUAL("", frame.m_RunningClock);
        CHECK_EQUAL("", frame.m_LeftClock);
        CHECK_EQUAL(false, frame.m_Shown);
    }

    TEST_FIXTURE(MainFramePresFixture, TestTimesUpdate)
    {
        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues();
        pres.setDisplayValues(values);
        pres.notifyTime();

        CHECK_EQUAL(false, frame.m_Closed);
        CHECK_EQUAL("", frame.m_PauseLabel);
        CHECK_EQUAL("", frame.m_StartLabel);
        CHECK_EQUAL(values.status, frame.m_Status);
        CHECK_EQUAL(values.timeOn, frame.m_OnClock);
        CHECK_EQUAL(values.timeOff, frame.m_OffClock);
        CHECK_EQUAL(values.timeRunning, frame.m_RunningClock);
        CHECK_EQUAL(values.timeLeft, frame.m_LeftClock);
    }

    TEST_FIXTURE(MainFramePresFixture, TestTimesUpdateNoShow)
    {
        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues(false);
        pres.setDisplayValues(values);
        pres.notifyTime();

        CHECK_EQUAL(false, frame.m_Closed);
        CHECK_EQUAL("", frame.m_PauseLabel);
        CHECK_EQUAL("", frame.m_StartLabel);
        CHECK_EQUAL("", frame.m_Status);
        CHECK_EQUAL("", frame.m_OnClock);
        CHECK_EQUAL("", frame.m_OffClock);
        CHECK_EQUAL("", frame.m_RunningClock);
        CHECK_EQUAL("", frame.m_LeftClock);
    }

    TEST_FIXTURE(MainFramePresFixture, TestForceUpdate)
    {
        TKControllerStub::DisplayValues values =
            TKControllerStub::DisplayValues::getTestValues();
        pres.setDisplayValues(values);
        handler.forceUpdate();

        CHECK_EQUAL(false, frame.m_Closed);
        CHECK_EQUAL(values.pauseButtonLabel, frame.m_PauseLabel);
        CHECK_EQUAL(values.startButtonLabel, frame.m_StartLabel);
        CHECK_EQUAL(values.status, frame.m_Status);
        CHECK_EQUAL(values.timeOn, frame.m_OnClock);
        CHECK_EQUAL(values.timeOff, frame.m_OffClock);
        CHECK_EQUAL(values.timeRunning, frame.m_RunningClock);
        CHECK_EQUAL(values.timeLeft, frame.m_LeftClock);
        CHECK_EQUAL(values.shown, frame.m_Shown);
    }
}
}
