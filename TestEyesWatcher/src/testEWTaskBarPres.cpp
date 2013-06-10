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
#include "EWTaskBarPres.h"
#include "EWAppControllerStub.h"
#include "EWPresenterStub.h"
#include "EWTaskbarStub.h"

///@todo: sort TaskBar/Taskbar
struct EWTaskBarPresFixture
{
    EWTaskBarPresFixture() : ctrl(true), pres(), barPres(&pres, &ctrl)
    {
        barPres.attachView(&bar);
    }
    ~EWTaskBarPresFixture() {}

    EWAppControllerStub ctrl;
    EWPresenterStub pres;
    EWTaskBarPres barPres;
    EWTaskbarStub bar;
};

SUITE(TestEWTaskBarPres)
{
    ///////////////////////////////////////////////////////////////////////////
    // Specific
    ///////////////////////////////////////////////////////////////////////////
    TEST_FIXTURE(EWTaskBarPresFixture, TestTimesUpdate)
    {
        EWPresenterStub::DisplayValues values =
            EWPresenterStub::DisplayValues::getTestValues();
        pres.setDisplayValues(values);
        pres.notifyTime();

        CHECK_EQUAL("Last Session : " + values.timeOn, bar.onClock);
        CHECK_EQUAL("Last Pause : " + values.timeOff, bar.offClock);
        CHECK_EQUAL("Running : " + values.timeRunning, bar.runningClock);
        CHECK_EQUAL("Time Left : " + values.timeLeft, bar.leftClock);
        CHECK_EQUAL(values.icon, bar.loc);
    }

    TEST_FIXTURE(EWTaskBarPresFixture, TestTimesUpdateNoIcon)
    {
        EWPresenterStub::DisplayValues values =
            EWPresenterStub::DisplayValues::getTestValues(true, false);
        bar.loc = "in";
        pres.setDisplayValues(values);
        pres.notifyTime();

        CHECK_EQUAL("Last Session : " + values.timeOn, bar.onClock);
        CHECK_EQUAL("Last Pause : " + values.timeOff, bar.offClock);
        CHECK_EQUAL("Running : " + values.timeRunning, bar.runningClock);
        CHECK_EQUAL("Time Left : " + values.timeLeft, bar.leftClock);
        CHECK_EQUAL("in", bar.loc);
    }

    TEST_FIXTURE(EWTaskBarPresFixture, TestStatusUpdate)
    {
        EWPresenterStub::DisplayValues values =
            EWPresenterStub::DisplayValues::getTestValues();
        pres.setDisplayValues(values);
        pres.notifyStatus();

        CHECK_EQUAL(values.hideButtonLabel, bar.hideRestoreLabel);
        CHECK_EQUAL(values.startButtonLabel, bar.startStopLabel);
        CHECK_EQUAL(values.pauseButtonLabel, bar.pauseResumeLabel);
        CHECK_EQUAL(values.icon, bar.loc);
    }

    TEST_FIXTURE(EWTaskBarPresFixture, TestStatusUpdateNoIcon)
    {
        EWPresenterStub::DisplayValues values =
            EWPresenterStub::DisplayValues::getTestValues(true, false);
        bar.loc = "in";
        pres.setDisplayValues(values);
        pres.notifyStatus();

        CHECK_EQUAL(values.hideButtonLabel, bar.hideRestoreLabel);
        CHECK_EQUAL(values.startButtonLabel, bar.startStopLabel);
        CHECK_EQUAL(values.pauseButtonLabel, bar.pauseResumeLabel);
        CHECK_EQUAL("in", bar.loc);
    }
}
