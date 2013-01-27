#ifndef TKSTATEHERE_H
#define TKSTATEHERE_H

#include "TKState.h"
#include <string>

class TKStateHere : public TKState
{
    public:
        static TKStateHere* Instance();
        virtual ~TKStateHere();

        virtual void updateStatus(TimeKeeper* parent, int lastInterval);
        virtual int getTimerInterval(TimeKeeper* parent);
        virtual int getInterval(TimeKeeper* parent);
        virtual int getTimeLeft(TimeKeeper* parent);
        virtual std::string getName();

    protected:
        TKStateHere();
    private:
        static TKStateHere* m_Instance;
};

#endif // TKSTATEHERE_H
