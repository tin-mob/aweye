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
#include "aweye/OptionsDialogPres.h"
#include "aweye/test/ConfigStub.h"
#include "aweye/test/MsgHandlerStub.h"
#include "aweye/test/OptionsDialogStub.h"

#include <unittest++/UnitTest++.h>

namespace Aweye
{
struct OptionsDialogPresFixture
{
    OptionsDialogPresFixture()
    {
    }
    ~OptionsDialogPresFixture() {}

    MsgHandlerStub msgHandler;
    ConfigStub config;
};

SUITE(TestBuilderOptionsDialogPres)
{
    TEST_FIXTURE(OptionsDialogPresFixture, TestSave)
    {
        OptionsDialogPres pres(msgHandler, config, true);
        const ConfigData newData = ConfigStub::getTestData();

        CHECK_EQUAL(true, pres.saveData(newData));
        CHECK_EQUAL(newData, config.getData());
    }

    TEST_FIXTURE(OptionsDialogPresFixture, TestSaveFail)
    {
        OptionsDialogPres pres(msgHandler, config, true);
        config.m_Fail = true;
        CHECK_EQUAL(false, pres.saveData(ConfigStub::getTestData()));
        CHECK_EQUAL("Testing!", msgHandler.m_LastError);
    }

    TEST_FIXTURE(OptionsDialogPresFixture, TestInit)
    {
        OptionsDialogPres pres(msgHandler, config, true);
        OptionsDialogStub dialog;

        config.save(ConfigData::getDefault("", boost::posix_time::not_a_date_time));
        pres.init(dialog);
        CHECK_EQUAL(config.getData(), dialog.getData());
        CHECK_EQUAL(false, dialog.m_Disabled);
    }

    TEST_FIXTURE(OptionsDialogPresFixture, TestInitNoTray)
    {
        OptionsDialogPres pres(msgHandler, config, false);
        OptionsDialogStub dialog;

        config.save(ConfigData::getDefault("", boost::posix_time::not_a_date_time));
        pres.init(dialog);
        CHECK_EQUAL(config.getData(), dialog.getData());
        CHECK_EQUAL(true, dialog.m_Disabled);
    }
}
}
