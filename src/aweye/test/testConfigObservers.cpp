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


#include "aweye/ConfigData.h"
#include "aweye/ConfigObservers.h"
#include "aweye/test/ConfigStub.h"
#include "aweye/test/PresenceHandlerStub.h"
#include "aweye/test/TimeKeeperStub.h"
#include "aweye/test/TKControllerStub.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <unittest++/UnitTest++.h>

namespace Aweye
{
struct ConfigObserversFixture
{
    ConfigObserversFixture() : keeperObserver(config, timeKeeper),
        presHdlrObserver(config, presenceHandler), presObserver(config, controller) {}
    ~ConfigObserversFixture() {}

    ConfigStub config;
    TimeKeeperStub timeKeeper;
    PresenceHandlerStub presenceHandler;
    TKControllerStub controller;
    TKConfigObserver keeperObserver;
    PresHdlrConfigObserver presHdlrObserver;
    TKCtrlConfigObserver presObserver;
};

SUITE(TestAppController)
{
    TEST_FIXTURE(ConfigObserversFixture, TestSave)
    {
        const ConfigData newData = ConfigStub::getTestData();

        config.save(newData);
        config.notifyUpdate();

        CHECK_EQUAL(newData.cascadePath, presenceHandler.m_CascadePath);
        CHECK_EQUAL(newData.webcamIndex, presenceHandler.m_WebcamIndex);
        CHECK_EQUAL(newData.faceSizeX, presenceHandler.m_FaceSizeX);
        CHECK_EQUAL(newData.faceSizeY, presenceHandler.m_FaceSizeY);

        CHECK_EQUAL(newData.checkFreq, timeKeeper.m_CheckFreq);
        CHECK_EQUAL(newData.pauseLength, timeKeeper.m_PauseLength);
        CHECK_EQUAL(newData.pauseTol, timeKeeper.m_PauseTol);
        CHECK_EQUAL(newData.workTol, timeKeeper.m_WorkTol);
        CHECK_EQUAL(newData.remFreq, timeKeeper.m_RemFreq);
        CHECK_EQUAL(newData.workLength, timeKeeper.m_WorkLength);
        CHECK_EQUAL(newData.cummulPause, timeKeeper.m_CummulPause);

        CHECK_EQUAL(newData.popupAlarm, controller.m_PopupAlarm);
        CHECK_EQUAL(newData.soundAlarm, controller.m_SoundAlarm);
        CHECK_EQUAL(newData.soundPath, controller.m_SoundPath);
        CHECK_EQUAL(newData.runningLateThreshold, controller.m_RunningLateThreshold);
    }
}
}
