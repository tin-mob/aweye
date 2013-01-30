#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

#include <string>
#include <map>
#include "TKState.h"

class AbstractWebcamHandler;
class TKStateHere;
class TKStateAway;
class TKStateOff;
class Config;
class AbstractTimeHandler;

class TimeKeeper
{
    public:
        enum Status { OFF, HERE, AWAY };

        TimeKeeper(Config* config);
        TimeKeeper(Config* config, AbstractTimeHandler* timeHandler, AbstractWebcamHandler* webcamHandler);
        virtual ~TimeKeeper();

        void start();
        void stop();

        void updateStatus();
        int getTimerInterval() const;
        bool isLate() const;

        TimeKeeper::Status getStatus() const;
        int getInterval() const;
        int getTimeLeft() const;
        int getHereStamp() const;
        int getAwayStamp() const;

    protected:
    private:

        friend class TKState;
        friend class TKStateHere;
        friend class TKStateAway;
        friend class TKStateOff;

        void initStates();

        std::map<Status,TKState*> m_States;
        Status m_CurrentState;

        AbstractTimeHandler* m_TimeHandler;
        AbstractWebcamHandler* m_WebcamHandler;
        time_t m_HereStamp;
        time_t m_AwayStamp;
        Config* m_Config;
        unsigned int m_NumTolerated;
};

#endif // TIMEKEEPER_H
