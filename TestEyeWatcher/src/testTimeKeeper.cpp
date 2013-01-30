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

SUITE(TestWatcherInt)
{
    TEST_FIXTURE(TimeKeeperFixture, TestOnOff)
    {
        MockupTimeHandler* timeHandler = new MockupTimeHandler();
        TimeKeeper keeper(&m_Config, timeHandler, new MockupWebcamHandler());
        CHECK_EQUAL(keeper.getStatus(), TimeKeeper::OFF);
        CHECK_EQUAL(keeper.getTimerInterval(), 0);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), 0);
        CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength);
        CHECK_EQUAL(keeper.getHereStamp(), 0);
        CHECK_EQUAL(keeper.getAwayStamp(), 0);

        keeper.start();
        CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
        CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), 0);
        CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength);
        CHECK_EQUAL(keeper.getHereStamp(), timeHandler->getTime());
        CHECK_EQUAL(keeper.getAwayStamp(), 0);


        keeper.stop();
        CHECK_EQUAL(keeper.getStatus(), TimeKeeper::OFF);
        CHECK_EQUAL(keeper.getTimerInterval(), 0);
        CHECK_EQUAL(keeper.isLate(), false);
        CHECK_EQUAL(keeper.getInterval(), 0);
        CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength);
        CHECK_EQUAL(keeper.getHereStamp(), 0);
        CHECK_EQUAL(keeper.getAwayStamp(), 0);
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
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), 0);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            CHECK_EQUAL(timeHandler->getTime(), startingTime + m_CheckFreq);

            webcamHandler->pushResult(true);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            webcamHandler->pushResult(true);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), 1);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(true);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_RemFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
        }
        {
            m_Config.setCheckFreq(1);
            m_Config.setRemFreq(2);

            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(true);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_Config.getCheckFreq());
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
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
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            pauseTime = timeHandler->getTime();
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            webcamHandler->pushResult(false);
            keeper.updateStatus();
            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), 1);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            startingTime = timeHandler->getTime();
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
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
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_RemFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
        }
        {
            pauseTime = timeHandler->getTime();
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_PauseLength);
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + m_CheckFreq);
            startingTime = timeHandler->getTime();
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), false);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestCancelledPause)
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
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_RemFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
        }
        {
            pauseTime = timeHandler->getTime();
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - startingTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_RemFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
        }
    }

    TEST_FIXTURE(TimeKeeperFixture, TestInterruptedPause)
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
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::HERE);
            CHECK_EQUAL(keeper.getTimerInterval(), m_RemFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_WorkLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), 0);
        }
        {
            pauseTime = timeHandler->getTime();
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(true);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), 1);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
        {
            timeHandler->setTime(timeHandler->getTime() + 1);
            webcamHandler->pushResult(false);
            keeper.updateStatus();

            time_t interval = timeHandler->getTime() - pauseTime;
            CHECK_EQUAL(keeper.getStatus(), TimeKeeper::AWAY);
            CHECK_EQUAL(keeper.getTimerInterval(), m_CheckFreq);
            CHECK_EQUAL(keeper.isLate(), true);
            CHECK_EQUAL(keeper.getInterval(), interval);
            CHECK_EQUAL(keeper.getTimeLeft(), m_PauseLength - interval);
            CHECK_EQUAL(keeper.getHereStamp(), startingTime);
            CHECK_EQUAL(keeper.getAwayStamp(), pauseTime);
        }
    }
}

