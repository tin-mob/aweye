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


#include "aweye/Config.h"
#include "aweye/test/ConfigImplStub.h"
#include "aweye/test/ConfigStub.h"
#include "aweye/test/UtilsStub.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <unittest++/UnitTest++.h>

namespace Aweye
{
struct ConfigFixture
{
    ConfigFixture()
    {
        utils.m_Dir = "path/";
    }
    ~ConfigFixture() {}

    ConfigImplStub impl;
    UtilsStub utils;
};

SUITE(TestConfig)
{
    TEST_FIXTURE(ConfigFixture, TestValidation)
    {
        ConfigData data(ConfigData::getDefault());
        const Config config(impl, utils);

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

        utils.m_FailName = data.cascadePath;
        CHECK_EQUAL(false, config.validateData(data));

        utils.m_FailName = data.soundPath;
        CHECK_EQUAL(false, config.validateData(data));
    }

    TEST_FIXTURE(ConfigFixture, TestEmptyConstruction)
    {
        const Config config(impl, utils);

        ConfigData data = config.getData();
        CHECK_EQUAL(ConfigData::getDefault(utils.m_Dir), data);
    }

    TEST_FIXTURE(ConfigFixture, TestSaveLoad)
    {
        ConfigData data(ConfigData::getDefault(utils.m_Dir));
        const ConfigData srcData = ConfigStub::getTestData(utils.m_Dir);

        Config config(impl, utils);
        Config config2(impl, utils);
        config.save(srcData);

        config2.load();
        data = config2.getData();

        CHECK_EQUAL(srcData, data);

        Config config3(impl, utils);
        config3.load();
        data = config3.getData();

        CHECK_EQUAL(srcData, data);
    }


    TEST_FIXTURE(ConfigFixture, TestInvalidSave)
    {
        const ConfigData data(ConfigData::getDefault(utils.m_Dir, boost::posix_time::neg_infin));
        Config config(impl, utils);
        CHECK_THROW(config.save(data), InvalidConfigDataException);
    }

    TEST_FIXTURE(ConfigFixture, TestInvalidLoad)
    {
        Config config(impl, utils);
        config.save(ConfigData::getDefault(utils.m_Dir));
        CHECK_EQUAL(false, config.hasInvalidData());

        utils.m_FailName = impl.read(std::string("CascadePath"), std::string("ShouldNotBeUsed"));
        Config config2(impl, utils);
        CHECK_EQUAL(true, config2.hasInvalidData());
    }
}
}
