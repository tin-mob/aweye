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
    EWMainFramePresFixture() : ctrl(true), pres(), framePres(&pres, &ctrl)
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
        ///@todo: remove redundancy
        const std::string hbl = "hbl";
        const std::string pbl = "pbl";
        const std::string sbl = "sbl";
        const std::string s = "s";
        const std::string ton = "ton";
        const std::string toff = "toff";
        const std::string tr = "tr";
        const std::string tl = "tl";
        const bool is = true;
        const std::string in = "in";
        pres.setDisplayValues(hbl, pbl, sbl, s, ton, toff, tr, tl, is, in);
        pres.notifyStatus();

        CHECK_EQUAL(false, frame.closed);
        CHECK_EQUAL(pbl, frame.pauseLabel);
        CHECK_EQUAL(sbl, frame.startLabel);
        CHECK_EQUAL(s, frame.status);
        CHECK_EQUAL(ton, frame.onClock);
        CHECK_EQUAL(toff, frame.offClock);
        CHECK_EQUAL(tr, frame.runningClock);
        CHECK_EQUAL(tl, frame.leftClock);
        CHECK_EQUAL(is, frame.shown);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestStatusUpdateNoShow)
    {
        frame.shown = true;

        const std::string hbl = "hbl";
        const std::string pbl = "pbl";
        const std::string sbl = "sbl";
        const std::string s = "s";
        const std::string ton = "ton";
        const std::string toff = "toff";
        const std::string tr = "tr";
        const std::string tl = "tl";
        const bool is = false;
        const std::string in = "in";
        pres.setDisplayValues(hbl, pbl, sbl, s, ton, toff, tr, tl, is, in);
        pres.notifyStatus();

        CHECK_EQUAL(false, frame.closed);
        CHECK_EQUAL("", frame.pauseLabel);
        CHECK_EQUAL("", frame.startLabel);
        CHECK_EQUAL("", frame.status);
        CHECK_EQUAL("", frame.onClock);
        CHECK_EQUAL("", frame.offClock);
        CHECK_EQUAL("", frame.runningClock);
        CHECK_EQUAL("", frame.leftClock);
        CHECK_EQUAL(is, frame.shown);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestTimesUpdate)
    {
        const std::string hbl = "hbl";
        const std::string pbl = "pbl";
        const std::string sbl = "sbl";
        const std::string s = "s";
        const std::string ton = "ton";
        const std::string toff = "toff";
        const std::string tr = "tr";
        const std::string tl = "tl";
        const bool is = true;
        const std::string in = "in";
        pres.setDisplayValues(hbl, pbl, sbl, s, ton, toff, tr, tl, is, in);
        pres.notifyTime();

        CHECK_EQUAL(false, frame.closed);
        CHECK_EQUAL("", frame.pauseLabel);
        CHECK_EQUAL("", frame.startLabel);
        CHECK_EQUAL(s, frame.status);
        CHECK_EQUAL(ton, frame.onClock);
        CHECK_EQUAL(toff, frame.offClock);
        CHECK_EQUAL(tr, frame.runningClock);
        CHECK_EQUAL(tl, frame.leftClock);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestTimesUpdateNoShow)
    {
        const std::string hbl = "hbl";
        const std::string pbl = "pbl";
        const std::string sbl = "sbl";
        const std::string s = "s";
        const std::string ton = "ton";
        const std::string toff = "toff";
        const std::string tr = "tr";
        const std::string tl = "tl";
        const bool is = false;
        const std::string in = "in";
        pres.setDisplayValues(hbl, pbl, sbl, s, ton, toff, tr, tl, is, in);
        pres.notifyTime();

        CHECK_EQUAL(false, frame.closed);
        CHECK_EQUAL("", frame.pauseLabel);
        CHECK_EQUAL("", frame.startLabel);
        CHECK_EQUAL("", frame.status);
        CHECK_EQUAL("", frame.onClock);
        CHECK_EQUAL("", frame.offClock);
        CHECK_EQUAL("", frame.runningClock);
        CHECK_EQUAL("", frame.leftClock);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Common
    ///////////////////////////////////////////////////////////////////////////
    TEST_FIXTURE(EWMainFramePresFixture, TestQuitUpdate)
    {
        pres.notifyQuit();
        CHECK_EQUAL(true, frame.closed);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestFrameQuit)
    {
        pres.quitted = false;
        framePres.OnViewQuit();
        CHECK_EQUAL(true, pres.quitted);
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
        pres.started = false;
        framePres.OnViewStartStop();
        CHECK_EQUAL(true, pres.started);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestFrameClose)
    {
        pres.shown = true;
        framePres.OnViewHideRestore();
        CHECK_EQUAL(false, pres.shown);
    }

    TEST_FIXTURE(EWMainFramePresFixture, TestFramePause)
    {
        pres.paused = false;
        framePres.OnViewPauseResume();
        CHECK_EQUAL(true, pres.paused);
    }
}

