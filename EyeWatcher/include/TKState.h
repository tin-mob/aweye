#ifndef TKSTATE_H
#define TKSTATE_H

#include <string>

class TimeKeeper;

class TKState
{
    public:
        virtual ~TKState() {}

        virtual void updateStatus(TimeKeeper* parent) = 0;
        virtual int getTimerInterval(const TimeKeeper* parent) const = 0;
        virtual bool isLate(const TimeKeeper* parent) const = 0;
        virtual int getInterval(const TimeKeeper* parent) const = 0;
        virtual int getTimeLeft(const TimeKeeper* parent) const = 0;

    protected:
    private:
};

#endif // TKSTATE_H
