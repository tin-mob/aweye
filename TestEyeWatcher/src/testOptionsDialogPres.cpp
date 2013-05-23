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
#include "OptionsDialogPres.h"
#include "EWAppControllerStub.h"

struct OptionsDialogPresFixture
{
    OptionsDialogPresFixture() : ctrl(), pres(&ctrl){}
    ~OptionsDialogPresFixture() {}

    EWAppControllerStub ctrl;
    OptionsDialogPres pres;
};

SUITE(TestOptionsDialogPres)
{
    TEST_FIXTURE(OptionsDialogPresFixture, TestGet)
    {
        ctrl.data = {boost::posix_time::not_a_date_time};
        ConfigData newData = pres.getData();
        CHECK_EQUAL(ctrl.data, newData);
    }

    TEST_FIXTURE(OptionsDialogPresFixture, TestSave)
    {
        ConfigData newData = {boost::posix_time::not_a_date_time};
        pres.saveData(newData);
        CHECK_EQUAL(ctrl.data, newData);
    }
}
