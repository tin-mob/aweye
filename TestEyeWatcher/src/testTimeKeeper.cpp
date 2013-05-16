#include <unittest++/UnitTest++.h>
#include "TimeKeeper.h"
#include "ConfigStub.h"
#include "TimeHandlerStub.h"
#include "PresenceHandlerStub.h"
#include "ConfigData.h"

struct TimeKeeperFixture
{
    public:
        TimeKeeperFixture() : keeper(NULL), timeHandler(NULL), presenceHandler(NULL)
        {
            this->data = {boost::posix_time::seconds(5), boost::posix_time::seconds(3),
                boost::posix_time::seconds(1), boost::posix_time::seconds(2)};

            try
            {
                this->timeHandler = new TimeHandlerStub(boost::posix_time::second_clock::local_time());
                this->presenceHandler = new PresenceHandlerStub();
                this->keeper = new TimeKeeper(this->timeHandler, this->presenceHandler,
                    data.workLength, data.pauseLength, data.remFreq, data.checkFreq, data.pauseTol);
            }
            catch (...)
            {
                this->deleteFixture();
                throw;
            }
        }
        ~TimeKeeperFixture()
        {
            deleteFixture();
        }

        ConfigData data;
        TimeKeeper* keeper;
        TimeHandlerStub* timeHandler;
        PresenceHandlerStub* presenceHandler;

    protected:
    private:

        void deleteFixture()
        {
            if (this->keeper != NULL) {delete this->keeper;}
            if (this->timeHandler != NULL) {delete this->timeHandler;}
            if (this->presenceHandler != NULL) {delete this->presenceHandler;}
        }

};

SUITE(TestTimeKeeper)
{
    TEST_FIXTURE(TimeKeeperFixture, TestInit)
    {
        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(this->keeper->getTimerInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getTimeLeft(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getHereStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), boost::posix_time::not_a_date_time);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStart)
    {
        this->keeper->start();
        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper->getHereStamp(), timeHandler->getTime());
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStartStop)
    {
        this->keeper->start();
        this->keeper->stop();
        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(this->keeper->getTimerInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getTimeLeft(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getHereStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), boost::posix_time::not_a_date_time);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestUpdate)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;

        this->keeper->start();
        timeHandler->setTime(timeHandler->getTime() + interval);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();

        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), interval);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestNearWorkEnd)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = this->data.workLength - boost::posix_time::seconds(1);

        this->keeper->start();
        timeHandler->setTime(timeHandler->getTime() + interval);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();

        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), boost::posix_time::seconds(1));
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), interval);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkEnd)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = this->data.workLength;

        this->keeper->start();
        timeHandler->setTime(timeHandler->getTime() + interval);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();

        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
        CHECK_EQUAL(this->keeper->isLate(), true);
        CHECK_EQUAL(this->keeper->getInterval(), interval);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestWorkEndCheckShortest)
    {
        this->data.checkFreq = boost::posix_time::seconds(1);
        this->data.remFreq = boost::posix_time::seconds(2);
        this->keeper->setCheckFreq(this->data.checkFreq);
        this->keeper->setRemFreq(this->data.remFreq);

        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = this->data.workLength;

        this->keeper->start();
        timeHandler->setTime(timeHandler->getTime() + interval);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();

        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), true);
        CHECK_EQUAL(this->keeper->getInterval(), interval);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength - interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestStartPause)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;
        boost::posix_time::ptime pauseTime = startingTime + interval;

        this->keeper->start();

        timeHandler->setTime(pauseTime);
        presenceHandler->pushResult(false);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength- interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestFalsePause)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;
        boost::posix_time::ptime pauseTime = startingTime + interval;

        this->keeper->start();

        timeHandler->setTime(pauseTime);
        presenceHandler->pushResult(false);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();

        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), interval);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength- interval);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength- interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestNearPauseEnd)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;
        boost::posix_time::ptime pauseTime = startingTime + interval;
        boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(1);
        boost::posix_time::time_duration pauseInterval = this->data.pauseLength - pauseLeft;

        this->keeper->start();
        timeHandler->setTime(pauseTime);
        presenceHandler->pushResult(false);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        timeHandler->setTime(pauseTime + pauseInterval);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper->getTimerInterval(), pauseLeft);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), pauseInterval);
        CHECK_EQUAL(this->keeper->getTimeLeft(), pauseLeft);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength- interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseEnd)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;
        boost::posix_time::ptime pauseTime = startingTime + interval;
        boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(0);
        boost::posix_time::time_duration pauseInterval = this->data.pauseLength - pauseLeft;

        this->keeper->start();
        timeHandler->setTime(pauseTime);
        presenceHandler->pushResult(false);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        timeHandler->setTime(pauseTime + pauseInterval);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), pauseInterval);
        CHECK_EQUAL(this->keeper->getTimeLeft(), pauseLeft);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength- interval);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseWork)
    {
        boost::posix_time::ptime pauseTime = timeHandler->getTime() + this->data.checkFreq;

        this->keeper->start();
        timeHandler->setTime(pauseTime);
        presenceHandler->pushResult(false);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        timeHandler->setTime(pauseTime + this->data.pauseLength);
        presenceHandler->pushResult(true);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();


        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper->getHereStamp(), timeHandler->getTime());
        CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseFalseWork)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::ptime pauseTime = startingTime + this->data.checkFreq;

        this->keeper->start();
        timeHandler->setTime(pauseTime);
        presenceHandler->pushResult(false);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        timeHandler->setTime(pauseTime + this->data.pauseLength);
        presenceHandler->pushResult(true);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();


        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), this->data.pauseLength);
        CHECK_EQUAL(this->keeper->getTimeLeft(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength - (pauseTime - startingTime));
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseTolerance)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = this->data.checkFreq;
        boost::posix_time::ptime pauseTime = startingTime + interval;
        boost::posix_time::time_duration pauseLeft = boost::posix_time::seconds(1);
        boost::posix_time::time_duration pauseInterval = this->data.pauseLength - pauseLeft;

        this->keeper->start();
        timeHandler->setTime(pauseTime);
        presenceHandler->pushResult(false);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        timeHandler->setTime(pauseTime + pauseInterval);
        presenceHandler->pushResult(true);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();


        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper->getTimerInterval(), pauseLeft);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), pauseInterval);
        CHECK_EQUAL(this->keeper->getTimeLeft(), pauseLeft);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength - (pauseTime - startingTime));
    }

    TEST_FIXTURE(TimeKeeperFixture, TestCancelledPause)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = boost::posix_time::seconds(1);


        this->keeper->start();
        timeHandler->setTime(startingTime + interval);
        presenceHandler->pushResult(false);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        timeHandler->setTime(timeHandler->getTime() + interval);
        presenceHandler->pushResult(true);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();

        timeHandler->setTime(timeHandler->getTime() + interval);
        presenceHandler->pushResult(true);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();


        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), interval * 3);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval * 3);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength - interval * 3);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestRestoredPause)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::time_duration interval = boost::posix_time::seconds(1);
        boost::posix_time::ptime pauseTime = startingTime + interval;

        this->keeper->start();
        timeHandler->setTime(pauseTime);
        presenceHandler->pushResult(false);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();

        timeHandler->setTime(pauseTime + interval);
        presenceHandler->pushResult(true);
        presenceHandler->pushResult(true);
        this->keeper->updateStatus();

        timeHandler->setTime(timeHandler->getTime() + interval);
        presenceHandler->pushResult(false);
        this->keeper->updateStatus();


        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.pauseLength - interval * 2);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), interval * 2);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval * 2);
        CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
        CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        CHECK_EQUAL(this->keeper->getWorkTimeLeft(), this->data.workLength - (pauseTime - startingTime));
    }
}

