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


#include "aweye/core/ConfigData.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <UnitTest++.h>

namespace Aweye
{
struct ConfigDataFixture
{
    ConfigDataFixture() {}
    ~ConfigDataFixture() {}
};

SUITE(TestConfigData)
{
    TEST_FIXTURE(ConfigDataFixture, TestComparison)
    {
        const ConfigData src(ConfigData::getDefault());
        CHECK_EQUAL(src, src);

        ConfigData mod(ConfigData::getDefault());
        mod.workLength = ConfigData::default_WorkLength + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.pauseLength = ConfigData::default_PauseLength + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.remFreq = ConfigData::default_RemFreq + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.checkFreq = ConfigData::default_CheckFreq + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.pauseTol = ConfigData::default_PauseTol + 1;
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.workTol = ConfigData::default_WorkTol + 1;
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.soundAlarm = !ConfigData::default_SoundAlarm;
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.popupAlarm = !ConfigData::default_PopupAlarm;
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.trayIcon = !ConfigData::default_TrayIcon;
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.webcamIndex = ConfigData::default_WebcamIndex + 1;
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.faceSizeX = ConfigData::default_FaceSizeX + 1;
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.faceSizeY = ConfigData::default_FaceSizeY + 1;
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.cascadePath = "test.cfg";
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.soundPath = "test.wav";
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.runningLateThreshold = ConfigData::default_CheckFreq + boost::posix_time::seconds(1);
        CHECK_EQUAL(false, mod == src);

        mod = ConfigData::getDefault();
        mod.cummulPause = !ConfigData::default_CummulPause;
        CHECK_EQUAL(false, mod == src);
    }
}
}
