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

SUITE(TestConfig)
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
