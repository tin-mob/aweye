#ifndef TKSTATEOFF_H
#define TKSTATEOFF_H

#include "TKState.h"
#include <string>

class TKStateOff : public TKState
{
    public:
        static TKStateOff* Instance();
        virtual ~TKStateOff();

        virtual void updateStatus(TimeKeeper* parent, int lastInterval);
        virtual int getTimerInterval(TimeKeeper* parent);
        virtual int getInterval(TimeKeeper* parent);
        virtual int getTimeLeft(TimeKeeper* parent);
        virtual std::string getName();

    protected:
        TKStateOff();
    private:
        static TKStateOff* m_Instance;
};

#endif // TKSTATEOFF_H
