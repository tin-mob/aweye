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


#include "aweye/core/BaseException.h"
#include "aweye/core/EventHandler.h"
#include "aweye/test/EventHandlerStub.h"
#include "aweye/test/MsgHandlerStub.h"
#include "aweye/test/TKControllerStub.h"

#include <functional>
#include <UnitTest++.h>

namespace Aweye
{
struct EventHandlerFixture
{
    EventHandlerFixture() : displayed(false), displayThrow(false), msgHandler(), controller(),
    displayCmd([this] () {if (displayThrow) throw BaseException("Testing!"); displayed = true; return true;}),
    handler(msgHandler, controller, displayCmd), observer(handler)
    {}

    ~EventHandlerFixture() {}

    bool displayed;
    bool displayThrow;
    MsgHandlerStub msgHandler;
    TKControllerStub controller;
    std::function<bool()> displayCmd;
    EventHandler handler;
    EventHandlerObserverStub observer;
};

SUITE(TestEventHandler)
{
    TEST_FIXTURE(EventHandlerFixture, TestQuit)
    {
        handler.OnViewQuit();
        CHECK_EQUAL(true, controller.m_Quitted);
    }

    TEST_FIXTURE(EventHandlerFixture, TestAbout)
    {
        handler.OnViewAbout();
    }

    TEST_FIXTURE(EventHandlerFixture, TestDisplay)
    {
        handler.OnViewOptionsButtonClick();
        CHECK_EQUAL(true, displayed);
    }

    TEST_FIXTURE(EventHandlerFixture, TestDisplayFail)
    {
        displayThrow = true;
        handler.OnViewOptionsButtonClick();
        CHECK_EQUAL("Testing!", msgHandler.m_LastError);
    }

    TEST_FIXTURE(EventHandlerFixture, TestFramePlay)
    {
        controller.m_Started = false;
        handler.OnViewStartStop();
        CHECK_EQUAL(true, controller.m_Started);
    }

    TEST_FIXTURE(EventHandlerFixture, TestFrameClose)
    {
        controller.m_DisplayValues.shown = true;
        handler.OnViewHideRestore();
        CHECK_EQUAL(false, controller.m_DisplayValues.shown);
    }

    TEST_FIXTURE(EventHandlerFixture, TestFramePause)
    {
        controller.m_Paused = false;
        handler.OnViewPauseResume();
        CHECK_EQUAL(true, controller.m_Paused);
    }

    TEST_FIXTURE(EventHandlerFixture, TestUpdate)
    {
        handler.forceUpdate();
        CHECK_EQUAL(true, observer.m_Refreshed);
    }
}
}
