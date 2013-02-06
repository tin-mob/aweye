#ifndef TIMEKEEPERSTUB_H
#define TIMEKEEPERSTUB_H


#include "AbstractTimeKeeper.h"
#include "BaseException.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/date_defs.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>

/// note to self : add stuff only as needed
class TimeKeeperStub : public AbstractTimeKeeper
{
    public:
        TimeKeeperStub() : fail(false), status(AbstractTimeKeeper::OFF),
            hereStamp(boost::posix_time::ptime(boost::gregorian::date(2078,boost::date_time::Jan,10), boost::posix_time::time_duration(10,59,00))),
            awayStamp(boost::posix_time::ptime(boost::gregorian::date(2078,boost::date_time::Jan,10), boost::posix_time::time_duration(11,31,01))){}
        virtual ~TimeKeeperStub() {}

        virtual void start()
        {
            if (fail) { throw BaseException("Testing!"); }
            status = AbstractTimeKeeper::HERE;
        }
        virtual void stop() {status = AbstractTimeKeeper::OFF;}
        virtual void updateStatus()
                {
            if (fail) { throw BaseException("Testing!"); }
            status = AbstractTimeKeeper::AWAY;
        }

        virtual boost::posix_time::time_duration getTimerInterval() const {return boost::posix_time::seconds(1);}
        virtual bool isLate() const {return false;}

        virtual AbstractTimeKeeper::Status getStatus() const {return status;}
        virtual boost::posix_time::time_duration getInterval() const {return boost::posix_time::seconds(2);}
        virtual boost::posix_time::time_duration getTimeLeft() const {return boost::posix_time::seconds(3);}
        virtual boost::posix_time::ptime getHereStamp() const {return hereStamp;}
        virtual boost::posix_time::ptime getAwayStamp() const {return awayStamp;}

        bool fail;
        AbstractTimeKeeper::Status status;
        boost::posix_time::ptime hereStamp;
        boost::posix_time::ptime awayStamp;
    protected:
    private:
};

#endif // TIMEKEEPERSTUB_H
