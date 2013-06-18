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
#include "EWMainFramePres.h"
#include "EWMainFrameStub.h"
#include "EWPresenterStub.h"
#include "EventHandlerStub.h"

struct EWMainFramePresFixture
{
    EWMainFramePresFixture() : frame(), pres(), handler(), framePres(frame, pres, handler)
    {
    }
    ~EWMainFramePresFixture() {}

    EWMainFrameStub frame;
    EWPresenterStub pres;
    EventHandlerStub handler;
    EWMainFramePres framePres;
};

SUITE(TestEWMainFramePres)
{
    TEST_FIXTURE(EWMainFramePresFixture, TestStatusUpdate)
    {
        EWPresenterStub::DisplayValues values =
            EWPresenterStub::DisplayValues::getTestValues();
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

    TEST_FIXTURE(EWMainFramePresFixture, TestStatusUpdateNoShow)
    {
        frame.m_Shown = true;

        EWPresenterStub::DisplayValues values =
            EWPresenterStub::DisplayValues::getTestValues(false);
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

    TEST_FIXTURE(EWMainFramePresFixture, TestTimesUpdate)
    {
        EWPresenterStub::DisplayValues values =
            EWPresenterStub::DisplayValues::getTestValues();
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

    TEST_FIXTURE(EWMainFramePresFixture, TestTimesUpdateNoShow)
    {
        EWPresenterStub::DisplayValues values =
            EWPresenterStub::DisplayValues::getTestValues(false);
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

    TEST_FIXTURE(EWMainFramePresFixture, TestForceUpdate)
    {
        EWPresenterStub::DisplayValues values =
            EWPresenterStub::DisplayValues::getTestValues();
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

