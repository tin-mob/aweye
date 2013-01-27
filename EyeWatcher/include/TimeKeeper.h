#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

#include <time.h>
#include <string>
#include <map>
#include "TKState.h"

class AbstractWebcamHandler;
class TKStateHere;
class TKStateAway;
class TKStateOff;
class Config;

class TimeKeeper
{
    public:
        TimeKeeper(Config* config);
        virtual ~TimeKeeper();

        void start();
        void stop();

        void updateStatus(int lastInterval);
        int getTimerInterval();
        std::string getAlarmMsg();

        std::string getStatus();
        int getInterval();
        int getTimeLeft();
        int getHereStamp();
        int getAwayStamp();

    protected:
    private:

        friend class TKState;
        friend class TKStateHere;
        friend class TKStateAway;
        friend class TKStateOff;

        enum WatcherStateEnum { OFF, HERE, AWAY };
        std::map<WatcherStateEnum,TKState*> m_states;

        WatcherStateEnum m_CurrentState;

        AbstractWebcamHandler* m_WebcamHandler;
        time_t m_HereStamp;
        time_t m_AwayStamp;
        std::string m_Msg;
        Config* m_Config;
};

#endif // TIMEKEEPER_H
