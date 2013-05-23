#ifndef TIMEHANDLERSTUB_H
#define TIMEHANDLERSTUB_H

#include "AbstractTimeHandler.h"
#include "boost/date_time/posix_time/posix_time.hpp"

class TimeHandlerStub : public AbstractTimeHandler
{
     public:
        TimeHandlerStub(boost::posix_time::ptime time =
                        boost::posix_time::second_clock::local_time()) : m_time(time) {}
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

#endif // TIMEHANDLERSTUB_H
