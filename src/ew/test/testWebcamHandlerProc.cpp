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
// the testing code is bigger and more complicated than the tested code...

#include "ew/WebcamHandlerProc.h"
#include "ew/test/UtilsStub.h"

#include <functional>
#include <sstream>
#include <string>
#include <unittest++/UnitTest++.h>

#include <iostream>

namespace EW {

struct WebcamHandlerProcFixture
{
    WebcamHandlerProcFixture() : utils(),
        cmd( [this] (std::function<void (bool)> callback, std::string cmdStr)
        {
            callback(true);
            returnedCmdStr = cmdStr;
        }) , returnedCmdStr("")
    {
    }
    ~WebcamHandlerProcFixture() {}

    UtilsStub utils;
    std::function<void (std::function<void (bool)>, std::string)> cmd;
    std::string returnedCmdStr;
};

SUITE(TestWebcamHandlerProc)
{
    TEST_FIXTURE(WebcamHandlerProcFixture, TestCmd)
    {
        int index = 1;
        std::string cascade = "cascade";
        unsigned int faceX = 2;
        unsigned int faceY = 3;
        WebcamHandlerProc handler(utils, cmd, index, cascade, faceX, faceY);

        bool callbackCalled = false;
        auto callback = [&] (bool) {callbackCalled = true;};
        handler.isHere(callback);

        CHECK_EQUAL(true, callbackCalled);

        std::ostringstream s;
        s  << "./IsHereCmd '" << index << "' '" << cascade << "' '"
            << faceX << "' '" << faceY << "'";
        CHECK_EQUAL(s.str(), returnedCmdStr);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestInvalidFile)
    {
        int index = 1;
        std::string cascade = "cascade";
        unsigned int faceX = 2;
        unsigned int faceY = 3;
        WebcamHandlerProc handler(utils, cmd, index, cascade, faceX, faceY);

        bool callbackCalled = false;
        auto callback = [&] (bool) {callbackCalled = true;};

        utils.m_FailName = cascade;
        bool trown = false;
        try
        {
            handler.isHere(callback);
        }
        catch (MissingCascadeFileException)
        {
            trown = true;
        }

        CHECK_EQUAL(false, callbackCalled);
        CHECK_EQUAL(true, trown);
    }
}
}
