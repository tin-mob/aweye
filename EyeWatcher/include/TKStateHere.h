#ifndef TKSTATEHERE_H
#define TKSTATEHERE_H

#include "TKState.h"

class TKStateHere : public TKState
{
    public:
        TKStateHere();
        virtual ~TKStateHere();

        virtual void updateStatus(TimeKeeper* parent);
        virtual void updateTimeStamps(TimeKeeper* parent);
        virtual boost::posix_time::time_duration getTimerInterval(const TimeKeeper* parent) const;
        virtual bool isLate(const TimeKeeper* parent) const;
        virtual boost::posix_time::time_duration getInterval(const TimeKeeper* parent) const;
        virtual boost::posix_time::time_duration getTimeLeft(const TimeKeeper* parent) const;

    protected:
    private:
};

#endif // TKSTATEHERE_H
