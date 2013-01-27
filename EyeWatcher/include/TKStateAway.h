#ifndef TKSTATEAWAY_H
#define TKSTATEAWAY_H

#include "TKState.h"

class TKStateAway : public TKState
{
    public:
        static TKStateAway* Instance();
        virtual ~TKStateAway();

        virtual void updateStatus(TimeKeeper* parent, int lastInterval);
        virtual int getTimerInterval(TimeKeeper* parent);
        virtual int getInterval(TimeKeeper* parent);
        virtual int getTimeLeft(TimeKeeper* parent);
        virtual std::string getName();

    protected:
        TKStateAway();
    private:
        static TKStateAway* m_Instance;
};

#endif // TKSTATEAWAY_H
