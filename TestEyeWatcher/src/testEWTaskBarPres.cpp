#include <unittest++/UnitTest++.h>
#include "EWTaskBarPres.h"
#include "EWAppControllerStub.h"
#include "EWPresenterStub.h"
#include "EWTaskbarStub.h"

///@todo: sort TaskBar/Taskbar
struct EWTaskBarPresFixture
{
    EWTaskBarPresFixture() : ctrl(), pres(), barPres(&pres, &ctrl)
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
