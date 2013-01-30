#ifndef TKSTATEAWAY_H
#define TKSTATEAWAY_H

#include "TKState.h"
#include <string>

class TKStateAway : public TKState
{
    public:
        TKStateAway();
        virtual ~TKStateAway();

        virtual void updateStatus(TimeKeeper* parent);
        virtual void updateTimeStamps(TimeKeeper* parent);
        virtual int getTimerInterval(const TimeKeeper* parent) const;
        virtual bool isLate(const TimeKeeper* parent) const;
        virtual int getInterval(const TimeKeeper* parent) const;
        virtual int getTimeLeft(const TimeKeeper* parent) const;

    protected:
    private:
};

#endif // TKSTATEAWAY_H
