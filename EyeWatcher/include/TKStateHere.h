#ifndef TKSTATEHERE_H
#define TKSTATEHERE_H

#include "TKState.h"
#include <string>

class TKStateHere : public TKState
{
    public:
        TKStateHere();
        virtual ~TKStateHere();

        virtual void updateStatus(TimeKeeper* parent);
        virtual void updateTimeStamps(TimeKeeper* parent);
        virtual int getTimerInterval(const TimeKeeper* parent) const;
        virtual bool isLate(const TimeKeeper* parent) const;
        virtual int getInterval(const TimeKeeper* parent) const;
        virtual int getTimeLeft(const TimeKeeper* parent) const;

    protected:
    private:
};

#endif // TKSTATEHERE_H
