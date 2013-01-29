#ifndef TKSTATEOFF_H
#define TKSTATEOFF_H

#include "TKState.h"
#include <string>

class TKStateOff : public TKState
{
    public:
        TKStateOff();
        virtual ~TKStateOff();

        virtual void updateStatus(TimeKeeper* parent);
        virtual int getTimerInterval(const TimeKeeper* parent) const;
        virtual bool isLate(const TimeKeeper* parent) const;
        virtual int getInterval(const TimeKeeper* parent) const;
        virtual int getTimeLeft(const TimeKeeper* parent) const;

    protected:
    private:
};

#endif // TKSTATEOFF_H
