/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include <unittest++/UnitTest++.h>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <string>
#include "Config.h"
#include "ConfigImplStub.h"
#include "ConfigStub.h"

struct ConfigFixture
{
    ConfigFixture() {}
    ~ConfigFixture() {}

    ConfigImplStub impl;
};

SUITE(TestConfig)
{
    TEST_FIXTURE(ConfigFixture, TestValidation)
    {
        ConfigData data;
        Config config(&impl);

        CHECK_EQUAL(true, config.validateData(data));

        data.workLength = boost::posix_time::seconds(0);
        CHECK_EQUAL(false, config.validateData(data));
        data.workLength = ConfigData::default_WorkLength;

        data.pauseLength = boost::posix_time::seconds(0);
        CHECK_EQUAL(false, config.validateData(data));
        data.pauseLength = ConfigData::default_PauseLength;

        data.remFreq = boost::posix_time::seconds(0);
        CHECK_EQUAL(false, config.validateData(data));
        data.remFreq = ConfigData::default_RemFreq;

        data.checkFreq = boost::posix_time::seconds(0);
        CHECK_EQUAL(false, config.validateData(data));
        data.checkFreq = ConfigData::default_CheckFreq;

        data.workLength = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, config.validateData(data));
        data.workLength = ConfigData::default_WorkLength;

        data.pauseLength = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, config.validateData(data));
        data.pauseLength = ConfigData::default_PauseLength;

        data.remFreq = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, config.validateData(data));
        data.remFreq = ConfigData::default_RemFreq;

        data.checkFreq = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, config.validateData(data));
        data.checkFreq = ConfigData::default_CheckFreq;

        data.runningLateThreshold = boost::posix_time::not_a_date_time;
        CHECK_EQUAL(false, config.validateData(data));
        data.runningLateThreshold = ConfigData::default_RunningLateThreshold;

        impl.failName = data.cascadePath;
        CHECK_EQUAL(false, config.validateData(data));

        impl.failName = data.soundPath;
        CHECK_EQUAL(false, config.validateData(data));
    }

    TEST_FIXTURE(ConfigFixture, TestEmptyConstruction)
    {
        Config config(&impl);

        ConfigData data = config.getData();
        CHECK_EQUAL(ConfigData(), data);
    }

    TEST_FIXTURE(ConfigFixture, TestSaveLoad)
    {
        ConfigData data;
        ConfigData srcData = ConfigStub::getTestData();

        Config config(&impl);
        Config config2(&impl);
        config.save(srcData);

        config2.load();
        data = config2.getData();

        CHECK_EQUAL(srcData, data);

        Config config3(&impl);
        config3.load();
        data = config3.getData();

        CHECK_EQUAL(srcData, data);
    }


    TEST_FIXTURE(ConfigFixture, TestInvalidSave)
    {
        ConfigData data = {boost::posix_time::neg_infin};
        Config config(&impl);
        CHECK_THROW(config.save(data), InvalidConfigDataException);
    }
}

