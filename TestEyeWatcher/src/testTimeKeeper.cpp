#include <unittest++/UnitTest++.h>
#include "TimeKeeper.h"
#include "ConfigStub.h"
#include "TimeHandlerStub.h"
#include "PresenceHandlerStub.h"
#include "ConfigData.h"

struct TimeKeeperFixture
{
    public:
        TimeKeeperFixture() : keeper(NULL), config(NULL), timeHandler(NULL), presenceHandler(NULL)
        {
            this->data = {boost::posix_time::seconds(5), boost::posix_time::seconds(3), boost::posix_time::seconds(1),
                boost::posix_time::seconds(2), ConfigData::default_PauseTol, ConfigData::default_Startup, ConfigData::default_SoundAlarm,
                ConfigData::default_PopupAlarm, ConfigData::default_EmailAlarm, ConfigData::default_EmailAddr};

            this->config = new ConfigStub(data);
            this->timeHandler = new TimeHandlerStub(boost::posix_time::second_clock::local_time());
            this->presenceHandler = new PresenceHandlerStub();
            this->keeper = new TimeKeeper(this->config, this->timeHandler, this->presenceHandler);
        }
        ~TimeKeeperFixture()
        {
            if (this->keeper != NULL) {delete this->keeper;}
            if (this->config != NULL) {delete this->config;}
            if (this->timeHandler != NULL) {delete this->timeHandler;}
            if (this->presenceHandler != NULL) {delete this->presenceHandler;}
        }

        ConfigData data;
        ConfigStub* config;
        TimeHandlerStub* timeHandler;
        PresenceHandlerStub* presenceHandler;
        TimeKeeper* keeper;

    protected:
    private:
};

SUITE(TestTimeKeeper)
{
    TEST_FIXTURE(TimeKeeperFixture, TestOnOff)
    {
        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(this->keeper->getTimerInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper->getHereStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);

        this->keeper->start();
        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper->getHereStamp(), timeHandler->getTime());
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);


        this->keeper->stop();
        CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::OFF);
        CHECK_EQUAL(this->keeper->getTimerInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), boost::posix_time::seconds(0));
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper->getHereStamp(), boost::posix_time::not_a_date_time);
        CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestSimpleRun)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();

        {
            this->keeper->start();
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), boost::posix_time::seconds(0));
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            CHECK_EQUAL(timeHandler->getTime(), startingTime + this->data.checkFreq);

            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), boost::posix_time::seconds(1));
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(1));
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        }
        {
            this->data.checkFreq = boost::posix_time::seconds(1);
            this->data.remFreq = boost::posix_time::seconds(2);
            this->config->save(this->data);

            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(1));
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseBefore)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::ptime pauseTime = boost::posix_time::not_a_date_time;
        this->keeper->start();

        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            pauseTime = timeHandler->getTime();
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();
            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), boost::posix_time::seconds(1));
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(1));
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            startingTime = timeHandler->getTime();
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseAfter)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::ptime pauseTime = boost::posix_time::not_a_date_time;
        this->keeper->start();

        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(6));
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        }
        {
            pauseTime = timeHandler->getTime();
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.pauseLength);
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            startingTime = timeHandler->getTime();
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestCancelledPause)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::ptime pauseTime = boost::posix_time::not_a_date_time;
        this->keeper->start();

        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(6));
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            pauseTime = timeHandler->getTime();
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(1));
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(1));
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestInterruptedPause)
    {
        boost::posix_time::ptime startingTime = timeHandler->getTime();
        boost::posix_time::ptime pauseTime = boost::posix_time::not_a_date_time;
        this->keeper->start();

        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(6));
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), boost::posix_time::not_a_date_time);
        }
        {
            pauseTime = timeHandler->getTime();
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(1));
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(1));
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), boost::posix_time::seconds(1));
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + boost::posix_time::seconds(1));
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            boost::posix_time::time_duration interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), AbstractTimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
    }
}

