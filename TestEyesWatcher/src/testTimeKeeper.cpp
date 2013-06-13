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
#include "TimeKeeper.h"
#include "ConfigStub.h"
#include "TimeHandlerStub.h"
#include "PresenceHandlerStub.h"
#include "ConfigData.h"

struct TimeKeeperFixture
{
    public:
        TimeKeeperFixture() :
            data({boost::posix_time::seconds(5), boost::posix_time::seconds(7),
                boost::posix_time::seconds(1), boost::posix_time::seconds(2),1,1}),
            timeHandler(TimeHandlerStub()),
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
        CHECK_EQUAL(keeper.getTimerInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getHereStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), boost::posix_time::not_a_date_time);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStart)
    {
        presenceHandler.pushResult(true);
        keeper.start();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength);
        CHECK_EQUAL(keeper.getHereStamp(), timeHandler.getTime());
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStartStop)
    {
        presenceHandler.pushResult(true);
        keeper.start();
        keeper.stop();
        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(keeper.getTimerInterval(), boost::posix_time::seconds(0));
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
        const boost::posix_time::time_duration interval = data.checkFreq;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), interval);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - interval);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestNearWorkEnd)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = data.workLength - boost::posix_time::seconds(1);

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), boost::posix_time::seconds(1));
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), interval);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - interval);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkEnd)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = data.workLength;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), data.remFreq);
        CHECK_EQUAL(keeper.isLate(), true);
        CHECK_EQUAL(keeper.getInterval(), interval);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - interval);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkEndCheckShortest)
    {
        data.checkFreq = boost::posix_time::seconds(1);
        data.remFreq = boost::posix_time::seconds(2);
        keeper.setCheckFreq(data.checkFreq);
        keeper.setRemFreq(data.remFreq);

        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = data.workLength;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), true);
        CHECK_EQUAL(keeper.getInterval(), interval);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - interval);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkTolerance)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();

        presenceHandler.pushResult(true);
        keeper.start();

        presenceHandler.pushResult(false);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStartPause)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();

        presenceHandler.pushResult(true);
        keeper.start();

        presenceHandler.pushResult(false);
        presenceHandler.pushResult(false);
        keeper.updateStatus();
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestNearPauseEnd)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = data.checkFreq;
        const boost::posix_time::ptime pauseTime = startingTime + interval;
        const boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(1);
        const boost::posix_time::time_duration pauseInterval = data.pauseLength - pauseLeft;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(pauseTime);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(pauseTime + pauseInterval);
        presenceHandler.pushResult(false);
        presenceHandler.pushResult(false);
        keeper.updateStatus();
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.getTimerInterval(), pauseLeft);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), pauseInterval);
        CHECK_EQUAL(keeper.getTimeLeft(), pauseLeft);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseEnd)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = data.checkFreq;
        const boost::posix_time::ptime pauseTime = startingTime + interval;
        const boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(0);
        const boost::posix_time::time_duration pauseInterval = data.pauseLength - pauseLeft;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(pauseTime);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(pauseTime + pauseInterval);
        presenceHandler.pushResult(false);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), pauseInterval);
        CHECK_EQUAL(keeper.getTimeLeft(), pauseLeft);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseWork)
    {
        const boost::posix_time::ptime pauseTime = timeHandler.getTime() + data.checkFreq;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(pauseTime);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(pauseTime + data.pauseLength);
        presenceHandler.pushResult(false);
        presenceHandler.pushResult(false);
        keeper.updateStatus();
        keeper.updateStatus();

        presenceHandler.pushResult(true);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength);
        CHECK_EQUAL(keeper.getHereStamp(), timeHandler.getTime());
        CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseTolerance)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = data.checkFreq;
        const boost::posix_time::ptime pauseTime = startingTime + interval;
        const boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(1);
        const boost::posix_time::time_duration pauseInterval = data.pauseLength - pauseLeft;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(pauseTime);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(pauseTime + pauseInterval);
        presenceHandler.pushResult(false);
        presenceHandler.pushResult(false);
        keeper.updateStatus();
        keeper.updateStatus();

        presenceHandler.pushResult(true);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.getTimerInterval(), pauseLeft);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), pauseInterval);
        CHECK_EQUAL(keeper.getTimeLeft(), pauseLeft);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestCancelledPause)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = boost::posix_time::seconds(1);

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(startingTime + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        presenceHandler.pushResult(false);
        presenceHandler.pushResult(false);
        keeper.updateStatus();
        keeper.updateStatus();

        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();


        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), interval * 3);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - interval * 3);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval * 3);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestCancelledPauseCummul)
    {
        keeper.setCummulPause(true);
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = boost::posix_time::seconds(1);

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(startingTime + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(false);
        keeper.updateStatus();

        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(false);
        keeper.updateStatus();

        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();


        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), interval * 3);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - interval * 3);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime + interval);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval * 3);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestRestoredPause)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = boost::posix_time::seconds(1);
        const boost::posix_time::ptime pauseTime = startingTime + interval;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(pauseTime);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        presenceHandler.pushResult(false);
        presenceHandler.pushResult(false);
        keeper.updateStatus();
        keeper.updateStatus();

        timeHandler.setTime(pauseTime + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(false);
        keeper.updateStatus();


        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), interval * 2);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - interval * 2);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - (pauseTime - startingTime));
    }

    TEST_FIXTURE(TimeKeeperFixture, TestSmallHibernation)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = data.checkFreq;
        const boost::posix_time::ptime pauseTime = startingTime + interval;
        const boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(2);
        const boost::posix_time::time_duration pauseInterval = data.pauseLength - pauseLeft;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(pauseTime);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(pauseTime + pauseInterval);
        presenceHandler.pushResult(true);
        keeper.notifyHibernated();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), pauseInterval);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - pauseInterval);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - (pauseTime - startingTime));
    }

    TEST_FIXTURE(TimeKeeperFixture, TestLongHibernation)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = data.checkFreq;
        const boost::posix_time::ptime pauseTime = startingTime + interval;
        const boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(0);
        const boost::posix_time::time_duration pauseInterval = data.pauseLength - pauseLeft;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(pauseTime);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(pauseTime + pauseInterval);
        presenceHandler.pushResult(true);
        keeper.notifyHibernated();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), pauseInterval);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - pauseInterval);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestTolAndHibernate)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = boost::posix_time::seconds(1);
        const boost::posix_time::ptime pauseTime = startingTime + interval;

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(pauseTime);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        timeHandler.setTime(pauseTime + interval);
        presenceHandler.pushResult(false);
        keeper.updateStatus();

        timeHandler.setTime(pauseTime + interval * 2);
        presenceHandler.pushResult(true);
        keeper.notifyHibernated();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), interval * 2);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - interval * 2);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestIntolerantPause)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = data.checkFreq;
        const boost::posix_time::ptime pauseTime = startingTime + interval;
        keeper.setWorkTol(0);

        presenceHandler.pushResult(true);
        keeper.start();
        timeHandler.setTime(pauseTime);
        presenceHandler.pushResult(false);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), interval);
        CHECK_EQUAL(keeper.getTimeLeft(), data.pauseLength - interval);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), startingTime);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestIntolerantCancelledPause)
    {
        const boost::posix_time::ptime startingTime = timeHandler.getTime();
        const boost::posix_time::time_duration interval = boost::posix_time::seconds(1);
        keeper.setPauseTol(0);

        presenceHandler.pushResult(true);
        keeper.start();

        timeHandler.setTime(startingTime + interval);
        presenceHandler.pushResult(false);
        presenceHandler.pushResult(false);
        keeper.updateStatus();
        keeper.updateStatus();

        timeHandler.setTime(timeHandler.getTime() + interval);
        presenceHandler.pushResult(true);
        keeper.updateStatus();

        CHECK_EQUAL(keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), data.checkFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), interval * 2);
        CHECK_EQUAL(keeper.getTimeLeft(), data.workLength - interval * 2);
        CHECK_EQUAL(keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(keeper.getWorkTimeLeft(), data.workLength - interval * 2);
    }
}


