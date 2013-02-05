#include <unittest++/UnitTest++.h>
#include <queue>
#include <assert.h>
#include <boost/filesystem.hpp>

#include "Config.h"
#include "TimeKeeper.h"
#include "MockupHandlerFactory.h"

struct TimeKeeperFixture
{
    public:
        TimeKeeperFixture()
        {
            this->data = {5, 3, 1, 2, ConfigData::default_PauseTol, ConfigData::default_Startup, ConfigData::default_SoundAlarm,
                ConfigData::default_PopupAlarm, ConfigData::default_EmailAlarm, ConfigData::default_EmailAddr};

            this->config = new ConfigStub(data);
            this->timeHandler = new TimeHandlerStub();
            this->presenceHandler = new PresenceHandlerStub();
            this->keeper = new TimeKeeper(this->config, this->timeHandler, this->presenceHandler);
        }
        ~TimeKeeperFixture()
        {
            delete this->keeper;
            delete this->config;
            delete this->timeHandler;
            delete this->presenceHandler;
        }

        ConfigData data;
        ConfigStub* config;
        TimeHandlerStub* timeHandler;
        PresenceHandlerStub* presenceHandler;
        TimeKeeper* keeper;

    protected:
    private:
};

SUITE(TestWatcherInt)
{
    TEST_FIXTURE(TimeKeeperFixture, TestOnOff)
    {
        CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::OFF);
        CHECK_EQUAL(this->keeper->getTimerInterval(), 0);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), 0);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper->getHereStamp(), 0);
        CHECK_EQUAL(this->keeper->getAwayStamp(), 0);

        this->keeper->start();
        CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
        CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), 0);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper->getHereStamp(), timeHandler->getTime());
        CHECK_EQUAL(this->keeper->getAwayStamp(), 0);


        this->keeper->stop();
        CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::OFF);
        CHECK_EQUAL(this->keeper->getTimerInterval(), 0);
        CHECK_EQUAL(this->keeper->isLate(), false);
        CHECK_EQUAL(this->keeper->getInterval(), 0);
        CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
        CHECK_EQUAL(this->keeper->getHereStamp(), 0);
        CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestSimpleRun)
    {
        time_t startingTime = timeHandler->getTime();

        {
            this->keeper->start();
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), 0);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            CHECK_EQUAL(timeHandler->getTime(), startingTime + this->data.checkFreq);

            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), 1);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
        {
            this->data.checkFreq = 1;
            this->data.remFreq = 2;
            this->config->save(this->data);

            timeHandler->setTime(timeHandler->getTime() + 1);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseBefore)
    {
        time_t startingTime = timeHandler->getTime();
        time_t pauseTime = 0;
        this->keeper->start();

        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + this->data.checkFreq);
            pauseTime = timeHandler->getTime();
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
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
            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), 1);
            CHECK_EQUAL(this->keeper->isLate(), false);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
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

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
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

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
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

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
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
        time_t startingTime = timeHandler->getTime();
        time_t pauseTime = 0;
        this->keeper->start();

        {
            timeHandler->setTime(timeHandler->getTime() + 6);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
        {
            pauseTime = timeHandler->getTime();
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
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

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
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

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
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
        time_t startingTime = timeHandler->getTime();
        time_t pauseTime = 0;
        this->keeper->start();

        {
            timeHandler->setTime(timeHandler->getTime() + 6);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
        {
            pauseTime = timeHandler->getTime();
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestInterruptedPause)
    {
        time_t startingTime = timeHandler->getTime();
        time_t pauseTime = 0;
        this->keeper->start();

        {
            timeHandler->setTime(timeHandler->getTime() + 6);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.remFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.workLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), 0);
        }
        {
            pauseTime = timeHandler->getTime();
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            presenceHandler->pushResult(true);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), 1);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            presenceHandler->pushResult(false);
            this->keeper->updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(this->keeper->getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(this->keeper->getTimerInterval(), this->data.checkFreq);
            CHECK_EQUAL(this->keeper->isLate(), true);
            CHECK_EQUAL(this->keeper->getInterval(), interval);
            CHECK_EQUAL(this->keeper->getTimeLeft(), this->data.pauseLength - interval);
            CHECK_EQUAL(this->keeper->getHereStamp(), startingTime);
            CHECK_EQUAL(this->keeper->getAwayStamp(), pauseTime);
        }
    }
}

