#ifndef TKSTATE_H
#define TKSTATE_H

#include <string>
#include "boost/date_time/posix_time/posix_time_types.hpp"

class TimeKeeper;

class TKState
{
    public:
        virtual ~TKState() {}

        virtual void updateStatus(TimeKeeper* parent) = 0;
        virtual void updateTimeStamps(TimeKeeper* parent) = 0;
        virtual boost::posix_time::time_duration getTimerInterval(const TimeKeeper* parent) const = 0;
        virtual bool isLate(const TimeKeeper* parent) const = 0;
        virtual boost::posix_time::time_duration getInterval(const TimeKeeper* parent) const = 0;
        virtual boost::posix_time::time_duration getTimeLeft(const TimeKeeper* parent) const = 0;

    protected:
    private:
};

#endif // TKSTATE_H
