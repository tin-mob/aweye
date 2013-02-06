#ifndef TKSTATEOFF_H
#define TKSTATEOFF_H

#include "TKState.h"

class TKStateOff : public TKState
{
    public:
        TKStateOff();
        virtual ~TKStateOff();

        virtual void updateStatus(TimeKeeper* parent);
        virtual void updateTimeStamps(TimeKeeper* parent);
        virtual boost::posix_time::time_duration getTimerInterval(const TimeKeeper* parent) const;
        virtual bool isLate(const TimeKeeper* parent) const;
        virtual boost::posix_time::time_duration getInterval(const TimeKeeper* parent) const;
        virtual boost::posix_time::time_duration getTimeLeft(const TimeKeeper* parent) const;

    protected:
    private:
};

#endif // TKSTATEOFF_H
