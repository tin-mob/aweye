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
#include "OptionsDialogPres.h"
#include "EWAppControllerStub.h"
#include "OptionsDialogStub.h"

struct OptionsDialogPresFixture
{
    OptionsDialogPresFixture() : ctrl(true), pres(&ctrl){}
    ~OptionsDialogPresFixture() {}

    EWAppControllerStub ctrl;
    OptionsDialogPres pres;
};

SUITE(TestOptionsDialogPres)
{
    TEST_FIXTURE(OptionsDialogPresFixture, TestSave)
    {
        ConfigData newData = {boost::posix_time::not_a_date_time};
        pres.saveData(newData);
        CHECK_EQUAL(ctrl.data, newData);
    }

    TEST_FIXTURE(OptionsDialogPresFixture, TestInit)
    {
        OptionsDialogStub dialog;
        ctrl.data = {boost::posix_time::not_a_date_time};
        pres.init(&dialog);
        CHECK_EQUAL(ctrl.data, dialog.getData());
        CHECK_EQUAL(false, dialog.disabled);
    }

    TEST_FIXTURE(OptionsDialogPresFixture, TestInitNoTray)
    {
        EWAppControllerStub ctrl2(false);
        OptionsDialogPres pres2(&ctrl2);
        OptionsDialogStub dialog;

        ctrl2.data = {boost::posix_time::not_a_date_time};
        pres2.init(&dialog);
        CHECK_EQUAL(ctrl2.data, dialog.getData());
        CHECK_EQUAL(true, dialog.disabled);
    }
}
