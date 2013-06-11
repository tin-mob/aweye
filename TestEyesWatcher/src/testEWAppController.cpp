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
#include "EWAppController.h"
#include "MsgHandlerStub.h"
#include "ConfigStub.h"
#include "PresenceHandlerStub.h"
#include "TimeKeeperStub.h"
#include "EWPresenterStub.h"
#include "CommandStub.h"
#include "ConfigData.h"

struct EWAppControllerFixture
{
    EWAppControllerFixture() : ctrl(true), config(data)
    {
        ctrl.link(&msgHandler, &config, &presenceHandler, &timeKeeper,
                  &presenter, &displayCmd);
    }
    ~EWAppControllerFixture() {}

    EWAppController ctrl;
    MsgHandlerStub msgHandler;
    ConfigData data;
    ConfigStub config;
    PresenceHandlerStub presenceHandler;
    TimeKeeperStub timeKeeper;
    EWPresenterStub presenter;
    CommandStub displayCmd;
};

SUITE(TestEWAppController)
{
    TEST_FIXTURE(EWAppControllerFixture, TestGet)
    {
        const ConfigData newData = ConfigStub::getTestData();
        config.save(newData);
        CHECK_EQUAL(newData, ctrl.getConfigData());
    }

    TEST_FIXTURE(EWAppControllerFixture, TestSave)
    {
        const ConfigData newData = ConfigStub::getTestData();

        CHECK_EQUAL(true, ctrl.saveConfig(newData));
        CHECK_EQUAL(newData, config.getData());
        CHECK_EQUAL(newData.cascadePath, presenceHandler.cascadePath);
        CHECK_EQUAL(newData.webcamIndex, presenceHandler.webcamIndex);
        CHECK_EQUAL(newData.faceSizeX, presenceHandler.faceSizeX);
        CHECK_EQUAL(newData.faceSizeY, presenceHandler.faceSizeY);

        CHECK_EQUAL(newData.checkFreq, timeKeeper.checkFreq);
        CHECK_EQUAL(newData.pauseLength, timeKeeper.pauseLength);
        CHECK_EQUAL(newData.pauseTol, timeKeeper.pauseTol);
        CHECK_EQUAL(newData.workTol, timeKeeper.workTol);
        CHECK_EQUAL(newData.remFreq, timeKeeper.remFreq);
        CHECK_EQUAL(newData.workLength, timeKeeper.workLength);
        CHECK_EQUAL(newData.cummulPause, timeKeeper.cummulPause);

        CHECK_EQUAL(newData.popupAlarm, presenter.popupAlarm);
        CHECK_EQUAL(newData.soundAlarm, presenter.soundAlarm);
        CHECK_EQUAL(newData.soundPath, presenter.soundPath);
        CHECK_EQUAL(newData.runningLateThreshold, presenter.runningLateThreshold);
    }

    TEST_FIXTURE(EWAppControllerFixture, TestSaveFail)
    {
        config.m_Fail = true;
        CHECK_EQUAL(false, ctrl.saveConfig(ConfigData()));
        CHECK_EQUAL("Testing!", msgHandler.lastError);
    }

    TEST_FIXTURE(EWAppControllerFixture, TestDisplay)
    {
        ctrl.displayOptionsDialog();
        CHECK_EQUAL(true, displayCmd.m_Executed);
    }

    TEST_FIXTURE(EWAppControllerFixture, TestDisplayFail)
    {
        displayCmd.m_Throws = true;
        ctrl.displayOptionsDialog();
        CHECK_EQUAL("Testing!", msgHandler.lastError);
    }

    TEST_FIXTURE(EWAppControllerFixture, TestCanCreate)
    {
        CHECK_EQUAL(true, ctrl.canCreateTaskBar());
    }

    TEST_FIXTURE(EWAppControllerFixture, TestCannotCreate)
    {
        CHECK_EQUAL(false, EWAppController(false).canCreateTaskBar());
    }
}
