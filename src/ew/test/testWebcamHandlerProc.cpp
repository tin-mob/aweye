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


#include "ew/IsHereCmd.h"
#include "ew/TaskContext.h"
#include "ew/WebcamHandlerProc.h"
#include "ew/test/TaskExceptionObserverStub.h"
#include "ew/test/UtilsStub.h"

#include <functional>
#include <sstream>
#include <string>
#include <unittest++/UnitTest++.h>

#include <iostream>

namespace EW {

struct WebcamHandlerProcFixture
{
    WebcamHandlerProcFixture() : utils(), index(1), cascade("cascade"),
        faceX(2), faceY(3), commandString(""),
        cmd( [this] (std::shared_ptr<const TaskContext> context)
        {
            commandString = context->m_Command;
        }),
        handler(utils, cmd, index, cascade, faceX, faceY)
    {
    }
    ~WebcamHandlerProcFixture() {}

    UtilsStub utils;
    int index;
    std::string cascade;
    unsigned int faceX;
    unsigned int faceY;

    std::string commandString;
    std::function<void (std::shared_ptr<const TaskContext> context)> cmd;
    WebcamHandlerProc handler;
};

SUITE(TestWebcamHandlerProc)
{
    TEST_FIXTURE(WebcamHandlerProcFixture, TestCmd)
    {
        auto callback = [&] (bool) {};
        handler.isHere(callback);

        std::ostringstream s;
        s  << "./IsHereCmd '" << index << "' '" << cascade << "' '"
            << faceX << "' '" << faceY << "'";
        CHECK_EQUAL(s.str(), commandString);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCmdInvalidFile)
    {
        auto callback = [&] (bool) {};

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

        CHECK_EQUAL(true, trown);
        CHECK_EQUAL("", commandString);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackHere)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const IsHereTaskContext> context(new IsHereTaskContext("cmd", handler, callback));

        handler.onTaskEnded((int)IsHereCmdRetCode::HERE, context);

        CHECK_EQUAL(true, called);
        CHECK_EQUAL(true, here);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackAway)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const IsHereTaskContext> context(new IsHereTaskContext("cmd", handler, callback));

        handler.onTaskEnded((int)IsHereCmdRetCode::AWAY, context);

        CHECK_EQUAL(true, called);
        CHECK_EQUAL(false, here);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackInvalidContext)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const TaskContext> context(new TaskContext("cmd", handler));

        TaskExceptionObserverStub observer;
        handler.attach(&observer);

        handler.onTaskEnded((int)IsHereCmdRetCode::AWAY, context);

        CHECK_EQUAL(GenericPresenceHandlerException().what(), observer.what);
        CHECK_EQUAL(false, called);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackInvalidNbArgs)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const IsHereTaskContext> context(new IsHereTaskContext("cmd", handler, callback));

        TaskExceptionObserverStub observer;
        handler.attach(&observer);

        handler.onTaskEnded((int)IsHereCmdRetCode::INVALID_NB_ARGS, context);

        CHECK_EQUAL(GenericPresenceHandlerException().what(), observer.what);
        CHECK_EQUAL(false, called);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackInvalidIndex)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const IsHereTaskContext> context(new IsHereTaskContext("cmd", handler, callback));

        TaskExceptionObserverStub observer;
        handler.attach(&observer);

        handler.onTaskEnded((int)IsHereCmdRetCode::INVALID_INDEX, context);

        CHECK_EQUAL(GenericPresenceHandlerException().what(), observer.what);
        CHECK_EQUAL(false, called);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackInvalidFaceX)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const IsHereTaskContext> context(new IsHereTaskContext("cmd", handler, callback));

        TaskExceptionObserverStub observer;
        handler.attach(&observer);

        handler.onTaskEnded((int)IsHereCmdRetCode::INVALID_FACEX, context);

        CHECK_EQUAL(GenericPresenceHandlerException().what(), observer.what);
        CHECK_EQUAL(false, called);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackInvalidFaceY)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const IsHereTaskContext> context(new IsHereTaskContext("cmd", handler, callback));

        TaskExceptionObserverStub observer;
        handler.attach(&observer);

        handler.onTaskEnded((int)IsHereCmdRetCode::INVALID_FACEY, context);

        CHECK_EQUAL(GenericPresenceHandlerException().what(), observer.what);
        CHECK_EQUAL(false, called);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackInvalidCascade)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const IsHereTaskContext> context(new IsHereTaskContext("cmd", handler, callback));

        TaskExceptionObserverStub observer;
        handler.attach(&observer);

        handler.onTaskEnded((int)IsHereCmdRetCode::INVALID_CASCADE, context);

        CHECK_EQUAL(MissingCascadeFileException().what(), observer.what);
        CHECK_EQUAL(false, called);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackInvalidCamera)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const IsHereTaskContext> context(new IsHereTaskContext("cmd", handler, callback));

        TaskExceptionObserverStub observer;
        handler.attach(&observer);

        handler.onTaskEnded((int)IsHereCmdRetCode::INVALID_CAMERA, context);

        CHECK_EQUAL(InvalidCameraException().what(), observer.what);
        CHECK_EQUAL(false, called);
    }

    TEST_FIXTURE(WebcamHandlerProcFixture, TestCallbackOtherError)
    {
        bool called = false;
        bool here = false;
        auto callback = [&] (bool h) {here = h; called = true;};

        std::shared_ptr<const IsHereTaskContext> context(new IsHereTaskContext("cmd", handler, callback));

        TaskExceptionObserverStub observer;
        handler.attach(&observer);

        handler.onTaskEnded((int)IsHereCmdRetCode::OTHER_ERROR, context);

        CHECK_EQUAL(GenericPresenceHandlerException().what(), observer.what);
        CHECK_EQUAL(false, called);
    }
}
}
