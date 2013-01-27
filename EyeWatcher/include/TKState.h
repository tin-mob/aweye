#ifndef TKSTATE_H
#define TKSTATE_H

#include <string>

class TimeKeeper;

class TKState
{
    public:
        virtual ~TKState() {}

        virtual void updateStatus(TimeKeeper* parent, int lastInterval) = 0;
        virtual int getTimerInterval(TimeKeeper* parent) = 0;
        virtual int getInterval(TimeKeeper* parent) = 0;
        virtual int getTimeLeft(TimeKeeper* parent) = 0;
        virtual std::string getName() = 0;

    protected:
    private:
};

#endif // TKSTATE_H
