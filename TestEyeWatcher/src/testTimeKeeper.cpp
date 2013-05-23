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
#include "TimeKeeper.h"
#include "ConfigStub.h"
#include "TimeHandlerStub.h"
#include "PresenceHandlerStub.h"
#include "ConfigData.h"

/// @todo:implement << + == operators so that tests can be much easier to read

struct TimeKeeperFixture
{
    public:
        TimeKeeperFixture() :
            data({boost::posix_time::seconds(5), boost::posix_time::seconds(3),
                boost::posix_time::seconds(1), boost::posix_time::seconds(2)}),
            timeHandler(TimeHandlerStub()),
            presenceHandler(), keeper(TimeKeeper(&timeHandler, &presenceHandler,
                data.workLength, data.pauseLength, data.remFreq, data.checkFreq, data.pauseTol))
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
        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(this->keeper.getTimerInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper.getTimeLeft(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper.getHereStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), boost::posix_time::not_a_date_time);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStart)
    {
        this->keeper.start();
        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper.getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper.getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper.getHereStamp(), this->timeHandler.getTime());
        CHECK_EQUAL(this->keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStartStop)
    {
        this->keeper.start();
        this->keeper.stop();
        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(this->keeper.getTimerInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper.getTimeLeft(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper.getHereStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), boost::posix_time::not_a_date_time);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestUpdate)
    {
        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;

        this->keeper.start();
        this->timeHandler.setTime(this->timeHandler.getTime() + interval);
        this->presenceHandler.pushResult(true);
        this->keeper.updateStatus();

        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper.getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), interval);
        CHECK_EQUAL(this->keeper.getTimeLeft(), this->data.workLength - interval);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestNearWorkEnd)
    {
        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = this->data.workLength - boost::posix_time::seconds(1);

        this->keeper.start();
        this->timeHandler.setTime(this->timeHandler.getTime() + interval);
        this->presenceHandler.pushResult(true);
        this->keeper.updateStatus();

        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper.getTimerInterval(), boost::posix_time::seconds(1));
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), interval);
        CHECK_EQUAL(this->keeper.getTimeLeft(), this->data.workLength - interval);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkEnd)
    {
        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = this->data.workLength;

        this->keeper.start();
        this->timeHandler.setTime(this->timeHandler.getTime() + interval);
        this->presenceHandler.pushResult(true);
        this->keeper.updateStatus();

        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper.getTimerInterval(), this->data.remFreq);
        CHECK_EQUAL(this->keeper.isLate(), true);
        CHECK_EQUAL(this->keeper.getInterval(), interval);
        CHECK_EQUAL(this->keeper.getTimeLeft(), this->data.workLength - interval);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkEndCheckShortest)
    {
        this->data.checkFreq = boost::posix_time::seconds(1);
        this->data.remFreq = boost::posix_time::seconds(2);
        this->keeper.setCheckFreq(this->data.checkFreq);
        this->keeper.setRemFreq(this->data.remFreq);

        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = this->data.workLength;

        this->keeper.start();
        this->timeHandler.setTime(this->timeHandler.getTime() + interval);
        this->presenceHandler.pushResult(true);
        this->keeper.updateStatus();

        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper.getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper.isLate(), true);
        CHECK_EQUAL(this->keeper.getInterval(), interval);
        CHECK_EQUAL(this->keeper.getTimeLeft(), this->data.workLength - interval);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStartPause)
    {
        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;
        boost::posix_time::ptime pauseTime = startingTime + interval;

        this->keeper.start();

        this->timeHandler.setTime(pauseTime);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();

        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper.getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper.getTimeLeft(), this->data.pauseLength);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength- interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestNearPauseEnd)
    {
        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;
        boost::posix_time::ptime pauseTime = startingTime + interval;
        boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(1);
        boost::posix_time::time_duration pauseInterval = this->data.pauseLength - pauseLeft;

        this->keeper.start();
        this->timeHandler.setTime(pauseTime);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();

        this->timeHandler.setTime(pauseTime + pauseInterval);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();

        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper.getTimerInterval(), pauseLeft);
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), pauseInterval);
        CHECK_EQUAL(this->keeper.getTimeLeft(), pauseLeft);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength- interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseEnd)
    {
        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;
        boost::posix_time::ptime pauseTime = startingTime + interval;
        boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(0);
        boost::posix_time::time_duration pauseInterval = this->data.pauseLength - pauseLeft;

        this->keeper.start();
        this->timeHandler.setTime(pauseTime);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();

        this->timeHandler.setTime(pauseTime + pauseInterval);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();

        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper.getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), pauseInterval);
        CHECK_EQUAL(this->keeper.getTimeLeft(), pauseLeft);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength- interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseWork)
    {
        boost::posix_time::ptime pauseTime = this->timeHandler.getTime() + this->data.checkFreq;

        this->keeper.start();
        this->timeHandler.setTime(pauseTime);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();

        this->timeHandler.setTime(pauseTime + this->data.pauseLength);
        this->presenceHandler.pushResult(true);
        this->keeper.updateStatus();


        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper.getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper.getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper.getHereStamp(), this->timeHandler.getTime());
        CHECK_EQUAL(this->keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseTolerance)
    {
        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;
        boost::posix_time::ptime pauseTime = startingTime + interval;
        boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(1);
        boost::posix_time::time_duration pauseInterval = this->data.pauseLength - pauseLeft;

        this->keeper.start();
        this->timeHandler.setTime(pauseTime);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();

        this->timeHandler.setTime(pauseTime + pauseInterval);
        this->presenceHandler.pushResult(true);
        this->keeper.updateStatus();


        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper.getTimerInterval(), pauseLeft);
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), pauseInterval);
        CHECK_EQUAL(this->keeper.getTimeLeft(), pauseLeft);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength - (pauseTime - startingTime));
    }

    TEST_FIXTURE(TimeKeeperFixture, TestCancelledPause)
    {
        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = boost::posix_time::seconds(1);


        this->keeper.start();
        this->timeHandler.setTime(startingTime + interval);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();

        this->timeHandler.setTime(this->timeHandler.getTime() + interval);
        this->presenceHandler.pushResult(true);
        this->keeper.updateStatus();

        this->timeHandler.setTime(this->timeHandler.getTime() + interval);
        this->presenceHandler.pushResult(true);
        this->keeper.updateStatus();


        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper.getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), interval * 3);
        CHECK_EQUAL(this->keeper.getTimeLeft(), this->data.workLength - interval * 3);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength - interval * 3);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestRestoredPause)
    {
        boost::posix_time::ptime startingTime = this->timeHandler.getTime();
        boost::posix_time::time_duration interval = boost::posix_time::seconds(1);
        boost::posix_time::ptime pauseTime = startingTime + interval;

        this->keeper.start();
        this->timeHandler.setTime(pauseTime);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();

        this->timeHandler.setTime(pauseTime + interval);
        this->presenceHandler.pushResult(true);
        this->keeper.updateStatus();

        this->timeHandler.setTime(this->timeHandler.getTime() + interval);
        this->presenceHandler.pushResult(false);
        this->keeper.updateStatus();


        CHECK_EQUAL(this->keeper.getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper.getTimerInterval(), this->data.pauseLength - interval * 2);
        CHECK_EQUAL(this->keeper.isLate(), false);
        CHECK_EQUAL(this->keeper.getInterval(), interval * 2);
        CHECK_EQUAL(this->keeper.getTimeLeft(), this->data.pauseLength - interval * 2);
        CHECK_EQUAL(this->keeper.getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper.getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper.getWorkTimeLeft(), this->data.workLength - (pauseTime - startingTime));
    }
}


