#ifndef TKSTATEAWAY_H
#define TKSTATEAWAY_H

#include "TKState.h"

class TKStateAway : public TKState
{
    public:
        TKStateAway();
        virtual ~TKStateAway();

        virtual void updateStatus(TimeKeeper* parent);
        virtual void updateTimeStamps(TimeKeeper* parent);
        virtual boost::posix_time::time_duration getTimerInterval(const TimeKeeper* parent) const;
        virtual bool isLate(const TimeKeeper* parent) const;
        virtual boost::posix_time::time_duration getInterval(const TimeKeeper* parent) const;
        virtual boost::posix_time::time_duration getTimeLeft(const TimeKeeper* parent) const;

    protected:
    private:
};

#endif // TKSTATEAWAY_H
