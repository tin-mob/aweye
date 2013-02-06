#ifndef TIMEKEEPERSTUB_H
#define TIMEKEEPERSTUB_H


#include "AbstractTimeKeeper.h"
#include "BaseException.h"

#include "boost/date_time/posix_time/posix_time.hpp"

/// note to self : add stuff only as needed
class TimeKeeperStub : public AbstractTimeKeeper
{
    public:
        TimeKeeperStub() : fail(false){}
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

        bool fail;
    protected:
    private:
};

#endif // TIMEKEEPERSTUB_H
