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
#include "EWAppControllerStub.h"
#include "EWPresenterStub.h"
#include "EWMainFrameStub.h"

struct EWMainFramePresFixture
{
    EWMainFramePresFixture() : ctrl(true), pres(), framePres(pres, ctrl)
    {
        framePres.attachView(&frame);
    }
    ~EWMainFramePresFixture() {}

    EWAppControllerStub ctrl;
    EWPresenterStub pres;
    EWMainFramePres framePres;
    EWMainFrameStub frame;
};

SUITE(TestEWMainFramePres)
{
    ///////////////////////////////////////////////////////////////////////////
    // Specific
    ///////////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////////
    // Common
    ///////////////////////////////////////////////////////////////////////////
    TEST_FIXTURE(EWMainFramePresFixture, TestQuitUpdate)
    {
        pres.notifyQuit();
        CHECK_EQUAL(true, frame.m_Closed);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestFrameQuit)
    {
        pres.m_Quitted = false;
        framePres.OnViewQuit();
        CHECK_EQUAL(true, pres.m_Quitted);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestFrameAbout)
    {
        framePres.OnViewAbout();
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestFrameOptions)
    {
        framePres.OnViewOptionsButtonClick();
        CHECK_EQUAL(true, ctrl.checkDisplayedDialog());
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestFramePlay)
    {
        pres.m_Started = false;
        framePres.OnViewStartStop();
        CHECK_EQUAL(true, pres.m_Started);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestFrameClose)
    {
        pres.m_DisplayValues.shown = true;
        framePres.OnViewHideRestore();
        CHECK_EQUAL(false, pres.m_DisplayValues.shown);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestFramePause)
    {
        pres.m_Paused = false;
        framePres.OnViewPauseResume();
        CHECK_EQUAL(true, pres.m_Paused);
    }
}

