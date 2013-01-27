#include <unittest++/UnitTest++.h>
#include <queue>
#include <assert.h>
#include <boost/filesystem.hpp>

class MockupWebcamHandler
{
    public:
        MockupWebcamHandler(std::queue<bool> results) : m_results(results) {}
        virtual ~MockupWebcamHandler() {}
        virtual bool isHere()
        {
            assert (!this->m_results.empty());
            bool result  = this->m_results.front();
            this->m_results.pop();
            return result;
        }
    protected:
    private:
        std::queue<bool> m_results;
};

struct WatcherIntFixture
{
    public:
        WatcherIntFixture() : configPath("/tmp/test.cfg")
        {
//            boost::filesystem::remove(configPath);
//            Config* config = Config::Instance();
//            config->init(configPath);
//            config->setCheckFreq(2);
//            config->setPauseLength(3);
//            config->setRemFreq(1);
//            config->setWorkLength(5);
//            config->save();
        }
        ~WatcherIntFixture() {boost::filesystem::remove(configPath);}

    protected:
    private:
        const std::string configPath;
};

SUITE(TestWatcherInt)
{
    TEST_FIXTURE(WatcherIntFixture, TestOff)
    {
//        EyeWatcherInt* watcher = EyeWatcherInt::Instance();
//
//        CHECK_EQUAL(watcher->getStatus(), std::string("Off"));
    }
}

