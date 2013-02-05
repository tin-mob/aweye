#ifndef MOCKUPHANDLERFACTORY_H
#define MOCKUPHANDLERFACTORY_H

#include "AbstractTimeHandler.h"
#include "AbstractPresenceHandler.h"
#include "AbstractMsgHandler.h"
#include "AbstractConfig.h"
#include "ConfigData.h"

#include <vector>
#include <stdexcept>

///@todo: proper files...

class TimeHandlerStub : public AbstractTimeHandler
{
     public:
        TimeHandlerStub(time_t time = time(NULL)) : m_time(time) {}
        virtual ~TimeHandlerStub() {}
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
                throw std::logic_error("Not Opened");
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
        MsgHandlerStub() {}
        virtual ~MsgHandlerStub() {}
        virtual void displayError(std::string msg) {}
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

#endif // MOCKUPHANDLERFACTORY_H
