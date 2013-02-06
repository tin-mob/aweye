#ifndef MOCKUPHANDLERFACTORY_H
#define MOCKUPHANDLERFACTORY_H

#include "AbstractTimeHandler.h"
#include "AbstractPresenceHandler.h"
#include "AbstractMsgHandler.h"
#include "AbstractConfig.h"
#include "ConfigData.h"
#include "BaseException.h"
#include "AbstractTimeKeeper.h"

#include <vector>
#include <queue>
#include <assert.h>
#include "boost/date_time/posix_time/posix_time.hpp"

///@todo: proper files...

class TimeHandlerStub : public AbstractTimeHandler
{
     public:
        TimeHandlerStub(boost::posix_time::ptime time) : m_time(time) {}
        virtual ~TimeHandlerStub() {}
        virtual boost::posix_time::ptime getTime() const
        {
            return this->m_time;
        }
        virtual void setTime(boost::posix_time::ptime time)
        {
            this->m_time = time;
        }

    protected:
    private:
        boost::posix_time::ptime m_time;
};

class PresenceHandlerStub : public AbstractPresenceHandler
{
    public:
        PresenceHandlerStub() : m_opened(false) {}
        virtual ~PresenceHandlerStub() {}

        virtual void open()
        {
            m_opened = true;
        }

        virtual void release()
        {
            m_opened = false;
        }

        virtual bool isHere()
        {
            if (!m_opened)
            {
                throw BaseException("Not Opened");
            }
            assert (!this->m_results.empty());
            bool result  = this->m_results.front();
            this->m_results.pop();
            return result;
        }

        virtual void pushResult(bool result)
        {
            this->m_results.push(result);
        }

        bool m_opened;

    protected:
    private:
        std::queue<bool> m_results;
};

class MsgHandlerStub : public AbstractMsgHandler
{
    public:
        MsgHandlerStub() : lastError("") {}
        virtual ~MsgHandlerStub() {}
        virtual void displayError(std::string msg) {lastError = msg;}
        std::string lastError;
    protected:
    private:
};

class ConfigStub : public AbstractConfig
{
    public:
        ConfigStub(ConfigData data) : m_data(data) {}
        virtual ~ConfigStub() {}
        virtual void checkLoad() {}
        virtual void save(const ConfigData& data)
        {
            m_data = data;
        }
        virtual const ConfigData& getData() const
        {
            return m_data;
        }
    protected:
    private:
        ConfigData m_data;
};

/// note to self : add stuff only as needed
class TimeKeeperStub : public AbstractTimeKeeper
{
    public:
        TimeKeeperStub() {}
        virtual ~TimeKeeperStub() {}

        virtual void start() {}
        virtual void stop() {}

        virtual void updateStatus() {}
        virtual boost::posix_time::time_duration getTimerInterval() const {return boost::posix_time::seconds(0);}
        virtual bool isLate() const {return false;}

        virtual AbstractTimeKeeper::Status getStatus() const {return AbstractTimeKeeper::OFF;}
        virtual boost::posix_time::time_duration getInterval() const {return boost::posix_time::seconds(0);}
        virtual boost::posix_time::time_duration getTimeLeft() const {return boost::posix_time::seconds(0);}
        virtual boost::posix_time::ptime getHereStamp() const {return boost::posix_time::second_clock::local_time();}
        virtual boost::posix_time::ptime getAwayStamp() const {return boost::posix_time::second_clock::local_time();}
    protected:
    private:
};

#endif // MOCKUPHANDLERFACTORY_H
