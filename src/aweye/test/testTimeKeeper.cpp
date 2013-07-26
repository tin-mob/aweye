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
#include "aweye/core/TimeKeeper.h"
#include "aweye/test/ConfigStub.h"
#include "aweye/test/PresenceHandlerStub.h"
#include "aweye/test/TimeHandlerStub.h"

#include <unittest++/UnitTest++.h>

namespace Aweye
{
struct TimeKeeperFixture
{
    public:
        TimeKeeperFixture() :
            data(ConfigData::getDefault()), timeHandler(TimeHandlerStub()),
            presenceHandler(), keeper(timeHandler, presenceHandler,
                data.workLength, data.pauseLength, data.remFreq, data.checkFreq,
                data.pauseTol, data.workTol, data.cummulPause)
        {
        }

        ~TimeKeeperFixture()
        {
        }

        ConfigData data;
        TimeHandlerStub timeHandler;
        PresenceHandlerStub presenceHandler;
        TimeKeeper keeper;
    protected:
    private:
};

SUITE(TestTimeKeeper)
{
    TEST_FIXTURE(TimeKeeperFixture, TestInit)
    {
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getHereStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), boost::posix_time::not_a_date_time);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStart)
    {
        keeper.start();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength);
        CHECK_EQUAL(keeper.getHereStamp(), timeHandler.getTime());
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStartStop)
    {
        keeper.start();
        keeper.stop();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getHereStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), boost::posix_time::not_a_date_time);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestUpdate)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWork)
    {
        data.checkFreq = boost::posix_time::seconds(2);
        data.workLength = boost::posix_time::seconds(3);
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkSmallSteps)
    {
        data.checkFreq = boost::posix_time::seconds(2);
        data.workLength = boost::posix_time::seconds(3);
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(timeHandler.getTime() + data.checkFreq/2);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(false, keeper.checkUpdate());
        timeHandler.setTime(timeHandler.getTime() + data.checkFreq/2);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkEnd)
    {
        data.workLength = boost::posix_time::seconds(2);
        data.checkFreq = boost::posix_time::seconds(2);
        data.remFreq = boost::posix_time::seconds(1);
        keeper.setRemFreq(data.remFreq);
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), true);
        CHECK_EQUAL(keeper.getInterval(), data.workLength);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq);

        timeHandler.setTime(timeHandler.getTime() + data.remFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkEndCheckShortest)
    {
        data.workLength = boost::posix_time::seconds(1);
        data.checkFreq = boost::posix_time::seconds(1);
        data.remFreq = boost::posix_time::seconds(2);
        keeper.setRemFreq(data.remFreq);
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), true);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq);

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkTolerance)
    {
        data.checkFreq = boost::posix_time::seconds(2);
        data.workLength = boost::posix_time::seconds(3);
        data.workTol = 1;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setWorkTol(data.workTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStartPause)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(4);
        data.pauseLength = boost::posix_time::seconds(3);
        data.workTol = 1;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 2);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength- data.checkFreq * 2);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestNearPauseEnd)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(4);
        data.pauseLength = boost::posix_time::seconds(2);
        data.workTol = 0;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - data.checkFreq);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseEnd)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(4);
        data.pauseLength = boost::posix_time::seconds(1);
        data.workTol = 0;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - data.checkFreq);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseWork)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(4);
        data.pauseLength = boost::posix_time::seconds(1);
        data.workTol = 0;
        data.pauseTol = 1;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);
        keeper.setPauseTol(data.pauseTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 2);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq * 2);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime + data.checkFreq * 2);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq * 2);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestLatePauseWorkWithTol)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(3);
        data.pauseLength = boost::posix_time::seconds(2);
        data.workTol = 1;
        data.pauseTol = 1;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);
        keeper.setPauseTol(data.pauseTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());
        CHECK_EQUAL(keeper.isLate(), true);

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 2);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq * 2);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime + data.checkFreq * 5);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq * 3);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq * 2);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseTolerance)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(4);
        data.pauseLength = boost::posix_time::seconds(3);
        data.workTol = 0;
        data.pauseTol = 1;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);
        keeper.setPauseTol(data.pauseTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 2);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - data.checkFreq * 2);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestCancelledPause)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(5);
        data.pauseLength = boost::posix_time::seconds(4);
        data.workTol = 0;
        data.pauseTol = 1;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);
        keeper.setPauseTol(data.pauseTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 4);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq * 4);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq * 4);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestCancelledPauseCummul)
    {
        keeper.setCummulPause(true);

        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(5);
        data.pauseLength = boost::posix_time::seconds(4);
        data.workTol = 0;
        data.pauseTol = 1;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);
        keeper.setPauseTol(data.pauseTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 3);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq * 3);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq * 3);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestRestoredPause)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(5);
        data.pauseLength = boost::posix_time::seconds(4);
        data.workTol = 0;
        data.pauseTol = 1;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);
        keeper.setPauseTol(data.pauseTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 3);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - data.checkFreq * 3);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestSmallHibernation)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(5);
        data.pauseLength = boost::posix_time::seconds(4);
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq * 3);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 3);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - data.checkFreq * 3);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq);

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());
    }

    TEST_FIXTURE(TimeKeeperFixture, TestLongHibernation)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(5);
        data.pauseLength = boost::posix_time::seconds(4);
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq * 4);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 4);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - data.checkFreq * 4);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());
    }

    TEST_FIXTURE(TimeKeeperFixture, TestTolAndHibernate)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(5);
        data.pauseLength = boost::posix_time::seconds(4);
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq * 3);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 4);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - data.checkFreq * 4);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + data.checkFreq);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());
    }

    TEST_FIXTURE(TimeKeeperFixture, TestIntolerantCancelledPause)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(5);
        data.pauseLength = boost::posix_time::seconds(4);
        data.workTol = 0;
        data.pauseTol = 0;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);
        keeper.setPauseTol(data.pauseTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 3);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - data.checkFreq * 3);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - data.checkFreq * 3);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestTolStopStart)
    {
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        keeper.stop();
        keeper.start();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength);
        CHECK_EQUAL(keeper.getHereStamp(), timeHandler.getTime());
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestAwayTolStopStart)
    {
        data.workTol = 0;
        data.pauseTol = 1;

        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        keeper.stop();
        keeper.start();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength);
        CHECK_EQUAL(keeper.getHereStamp(), timeHandler.getTime());
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestAwayHereLimitCummul)
    {
        keeper.setCummulPause(true);
        data.checkFreq = boost::posix_time::seconds(1);
        data.workLength = boost::posix_time::seconds(3);
        data.pauseLength = boost::posix_time::seconds(3);
        data.workTol = 1;
        data.pauseTol = 1;
        keeper.setCheckFreq(data.checkFreq);
        keeper.setWorkLength(data.workLength);
        keeper.setPauseLength(data.pauseLength);
        keeper.setWorkTol(data.workTol);
        keeper.setPauseTol(data.pauseTol);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        keeper.start();

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(false);
        CHECK_EQUAL(true, keeper.checkUpdate());

        timeHandler.setTime(timeHandler.getTime() + data.checkFreq);
        presenceHandler.pushResult(true);
        CHECK_EQUAL(true, keeper.checkUpdate());

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), data.checkFreq * 3);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - data.checkFreq * 3);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }
}
}
