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
        std::string hbl = "hbl";
        std::string pbl = "pbl";
        std::string sbl = "sbl";
        std::string s = "s";
        std::string ton = "ton";
        std::string toff = "toff";
        std::string tr = "tr";
        std::string tl = "tl";
        bool is = true;
        std::string in = "in";

        pres.setDisplayValues(hbl, pbl, sbl, s, ton, toff, tr, tl, is, in);
        pres.notifyTime();

        CHECK_EQUAL("Last Session : " + ton, bar.onClock);
        CHECK_EQUAL("Last Pause : " + toff, bar.offClock);
        CHECK_EQUAL("Running : " + tr, bar.runningClock);
        CHECK_EQUAL("Time Left : " + tl, bar.leftClock);
        CHECK_EQUAL(in, bar.loc);
    }

    TEST_FIXTURE(EWTaskBarPresFixture, TestTimesUpdateNoIcon)
    {
        std::string hbl = "hbl";
        std::string pbl = "pbl";
        std::string sbl = "sbl";
        std::string s = "s";
        std::string ton = "ton";
        std::string toff = "toff";
        std::string tr = "tr";
        std::string tl = "tl";
        bool is = true;
        std::string in = "";

        bar.loc = "in";

        pres.setDisplayValues(hbl, pbl, sbl, s, ton, toff, tr, tl, is, in);
        pres.notifyTime();

        CHECK_EQUAL("Last Session : " + ton, bar.onClock);
        CHECK_EQUAL("Last Pause : " + toff, bar.offClock);
        CHECK_EQUAL("Running : " + tr, bar.runningClock);
        CHECK_EQUAL("Time Left : " + tl, bar.leftClock);
        CHECK_EQUAL("in", bar.loc);
    }

    TEST_FIXTURE(EWTaskBarPresFixture, TestStatusUpdate)
    {
        std::string hbl = "hbl";
        std::string pbl = "pbl";
        std::string sbl = "sbl";
        std::string s = "s";
        std::string ton = "ton";
        std::string toff = "toff";
        std::string tr = "tr";
        std::string tl = "tl";
        bool is = true;
        std::string in = "in";

        pres.setDisplayValues(hbl, pbl, sbl, s, ton, toff, tr, tl, is, in);
        pres.notifyStatus();

        CHECK_EQUAL(hbl, bar.hideRestoreLabel);
        CHECK_EQUAL(sbl, bar.startStopLabel);
        CHECK_EQUAL(pbl, bar.pauseResumeLabel);
        CHECK_EQUAL(in, bar.loc);
    }

    TEST_FIXTURE(EWTaskBarPresFixture, TestStatusUpdateNoIcon)
    {
        std::string hbl = "hbl";
        std::string pbl = "pbl";
        std::string sbl = "sbl";
        std::string s = "s";
        std::string ton = "ton";
        std::string toff = "toff";
        std::string tr = "tr";
        std::string tl = "tl";
        bool is = true;
        std::string in = "";

        bar.loc = "in";

        pres.setDisplayValues(hbl, pbl, sbl, s, ton, toff, tr, tl, is, in);
        pres.notifyStatus();

        CHECK_EQUAL(hbl, bar.hideRestoreLabel);
        CHECK_EQUAL(sbl, bar.startStopLabel);
        CHECK_EQUAL(pbl, bar.pauseResumeLabel);
        CHECK_EQUAL("in", bar.loc);
    }
}
