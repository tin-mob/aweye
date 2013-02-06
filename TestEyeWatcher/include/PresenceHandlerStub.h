#ifndef PRESENCEHANDLERSTUB_H
#define PRESENCEHANDLERSTUB_H

#include "AbstractPresenceHandler.h"
#include "BaseException.h"

#include <queue>
#include <assert.h>

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

#endif // PRESENCEHANDLERSTUB_H
