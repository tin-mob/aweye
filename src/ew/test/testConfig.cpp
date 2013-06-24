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


#include "ew/Config.h"
#include "ew/test/ConfigImplStub.h"
#include "ew/test/ConfigStub.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <unittest++/UnitTest++.h>

namespace EW
{
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
        const Config config(impl);

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

        impl.m_FailName = data.cascadePath;
        CHECK_EQUAL(false, config.validateData(data));

        impl.m_FailName = data.soundPath;
        CHECK_EQUAL(false, config.validateData(data));
    }

    TEST_FIXTURE(ConfigFixture, TestEmptyConstruction)
    {
        const Config config(impl);

        ConfigData data = config.getData();
        CHECK_EQUAL(ConfigData(), data);
    }

    TEST_FIXTURE(ConfigFixture, TestSaveLoad)
    {
        ConfigData data;
        const ConfigData srcData = ConfigStub::getTestData();

        Config config(impl);
        Config config2(impl);
        config.save(srcData);

        config2.load();
        data = config2.getData();

        CHECK_EQUAL(srcData, data);

        Config config3(impl);
        config3.load();
        data = config3.getData();

        CHECK_EQUAL(srcData, data);
    }


    TEST_FIXTURE(ConfigFixture, TestInvalidSave)
    {
        const ConfigData data = {boost::posix_time::neg_infin};
        Config config(impl);
        CHECK_THROW(config.save(data), InvalidConfigDataException);
    }

    TEST_FIXTURE(ConfigFixture, TestInvalidLoad)
    {
        Config config(impl);
        config.save({});
        CHECK_EQUAL(false, config.hasInvalidData());

        impl.m_FailName = impl.read(std::string("CascadePath"), std::string("ShouldNotBeUsed"));
        Config config2(impl);
        CHECK_EQUAL(true, config2.hasInvalidData());
    }
}
}
