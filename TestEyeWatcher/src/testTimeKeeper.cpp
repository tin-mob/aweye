#include <unittest++/UnitTest++.h>
#include <queue>
#include <assert.h>
#include <boost/filesystem.hpp>

#include "Config.h"
#include "TimeKeeper.h"
#include "AbstractTimeHandler.h"
#include "AbstractWebcamHandler.h"

/// @todo: look at google mockup
class MockupTimeHandler : public AbstractTimeHandler
{
     public:
        MockupTimeHandler(time_t time = time(NULL)) : m_time(time) {}
        virtual ~MockupTimeHandler() {}
        virtual time_t getTime() const
        {
            return this->m_time;
        }
        virtual void setTime(time_t time)
        {
            this->m_time = time;
        }

    protected:
    private:
        time_t m_time;
};

class MockupWebcamHandler : public AbstractWebcamHandler
{
    public:
        MockupWebcamHandler() {}
        virtual ~MockupWebcamHandler() {}
        virtual bool isHere()
        {
            assert (!this->m_results.empty());
            bool result  = this->m_results.front();
            this->m_results.pop();
            return result;
        }
        virtual void pushResult(bool result)
        {
            this->m_results.push(result);
        }

    protected:
    private:
        std::queue<bool> m_results;
};

struct TimeKeeperFixture
{
    public:
        TimeKeeperFixture() : m_Config("/tmp/test.cfg"), m_CheckFreq(2), m_PauseLength(3), m_RemFreq(1), m_WorkLength(5)
        {
            boost::filesystem::remove(m_ConfigPath);
            m_Config.setCheckFreq(m_CheckFreq);
            m_Config.setPauseLength(m_PauseLength);
            m_Config.setRemFreq(m_RemFreq);
            m_Config.setWorkLength(m_WorkLength);
            m_Config.save();
        }
        ~TimeKeeperFixture()
        {
            boost::filesystem::remove(m_ConfigPath);
        }

        Config m_Config;
        const int m_CheckFreq;
        const int m_PauseLength;
        const int m_RemFreq;
        const int m_WorkLength;

    protected:
    private:
        const std::string m_ConfigPath;
};

void checkTimeKeeper(TimeKeeper& keeper, TimeKeeper::Status status, int timerInterval, bool late, int interval, int timeLeft, unsigned int hereStamp, unsigned int awayStamp)
{
    CHECK_EQUAL(keeper.getStatus(), status);
    CHECK_EQUAL(keeper.getTimerInterval(), timerInterval);
    CHECK_EQUAL(keeper.isLate(), late);
    CHECK_EQUAL(keeper.getInterval(), interval);
    CHECK_EQUAL(keeper.getTimeLeft(), timeLeft);
    CHECK_EQUAL(keeper.getHereStamp(), hereStamp);
    CHECK_EQUAL(keeper.getAwayStamp(), awayStamp);
}

SUITE(TestWatcherInt)
{
    TEST_FIXTURE(TimeKeeperFixture, TestOnOff)
    {
        MockupTimeHandler* timeHandler = new MockupTimeHandler();
        TimeKeeper keeper(&m_Config, timeHandler, new MockupWebcamHandler());
        checkTimeKeeper(keeper, TimeKeeper::OFF, 0, false, 0, m_WorkLength, 0, 0);

        keeper.start();
        checkTimeKeeper(keeper, TimeKeeper::HERE, m_CheckFreq, false, 0, m_WorkLength, timeHandler->getTime(), 0);

        keeper.stop();
        checkTimeKeeper(keeper, TimeKeeper::OFF, 0, false, 0, m_WorkLength, 0, 0);
    }

    TEST_FIXTURE(TimeKeeperFixture, TestSimpleRun)
    {
        std::queue<bool> results;

        MockupTimeHandler* timeHandler = new MockupTimeHandler();
        MockupWebcamHandler* webcamHandler = new MockupWebcamHandler();
        TimeKeeper keeper(&m_Config, timeHandler, webcamHandler);
        CHECK_EQUAL(keeper.getStatus(), TimeKeeper::OFF);

        time_t startingTime = timeHandler->getTime();

        {
            keeper.start();
            checkTimeKeeper(keeper, TimeKeeper::HERE, m_CheckFreq, false, 0, m_WorkLength, startingTime, 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            CHECK_EQUAL(timeHandler->getTime(), startingTime + m_CheckFreq);

            webcamHandler->pushResult(true);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            checkTimeKeeper(keeper, TimeKeeper::HERE, m_CheckFreq, false, interval, m_WorkLength - interval, startingTime, 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            webcamHandler->pushResult(true);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            checkTimeKeeper(keeper, TimeKeeper::HERE, 1, false, interval, m_WorkLength - interval, startingTime, 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(true);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            checkTimeKeeper(keeper, TimeKeeper::HERE, m_RemFreq, true, interval, m_WorkLength - interval, startingTime, 0);
        }
        {
            m_Config.setCheckFreq(1);
            m_Config.setRemFreq(2);

            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(true);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            checkTimeKeeper(keeper, TimeKeeper::HERE, m_Config.getCheckFreq(), true, interval, m_WorkLength - interval, startingTime, 0);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseBefore)
    {
        MockupTimeHandler* timeHandler = new MockupTimeHandler();
        MockupWebcamHandler* webcamHandler = new MockupWebcamHandler();
        TimeKeeper keeper(&m_Config, timeHandler, webcamHandler);

        time_t startingTime = timeHandler->getTime();
        time_t pauseTime = 0;
        keeper.start();

        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            webcamHandler->pushResult(true);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            checkTimeKeeper(keeper, TimeKeeper::HERE, m_CheckFreq, false, interval, m_WorkLength - interval, startingTime, 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            pauseTime = timeHandler->getTime();
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            checkTimeKeeper(keeper, TimeKeeper::AWAY, m_CheckFreq, false, interval, m_PauseLength - interval, startingTime, pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            webcamHandler->pushResult(false);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - pauseTime;
            checkTimeKeeper(keeper, TimeKeeper::AWAY, 1, false, interval, m_PauseLength - interval, startingTime, pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            checkTimeKeeper(keeper, TimeKeeper::AWAY, m_CheckFreq, false, interval, m_PauseLength - interval, startingTime, pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            checkTimeKeeper(keeper, TimeKeeper::AWAY, m_CheckFreq, false, interval, m_PauseLength - interval, startingTime, pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            startingTime = timeHandler->getTime();
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            checkTimeKeeper(keeper, TimeKeeper::HERE, m_CheckFreq, false, interval, m_WorkLength - interval, startingTime, pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            checkTimeKeeper(keeper, TimeKeeper::HERE, m_CheckFreq, false, interval, m_WorkLength - interval, startingTime, pauseTime);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestPauseAfter)
    {
        MockupTimeHandler* timeHandler = new MockupTimeHandler();
        MockupWebcamHandler* webcamHandler = new MockupWebcamHandler();
        TimeKeeper keeper(&m_Config, timeHandler, webcamHandler);

        time_t startingTime = timeHandler->getTime();
        time_t pauseTime = 0;
        keeper.start();

        {
            timeHandler->setTime(timeHandler->getTime() + 6);
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            checkTimeKeeper(keeper, TimeKeeper::HERE, m_RemFreq, true, interval, m_WorkLength - interval, startingTime, 0);
        }
        {
            pauseTime = timeHandler->getTime();
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            checkTimeKeeper(keeper, TimeKeeper::AWAY, m_CheckFreq, true, interval, m_PauseLength - interval, startingTime, pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_PauseLength);
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            checkTimeKeeper(keeper, TimeKeeper::AWAY, m_CheckFreq, true, interval, m_PauseLength - interval, startingTime, pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            startingTime = timeHandler->getTime();
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            checkTimeKeeper(keeper, TimeKeeper::HERE, m_CheckFreq, false, interval, m_WorkLength - interval, startingTime, pauseTime);
        }
    }
}

