#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

#include <string>
#include <map>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "TKState.h"
#include "AbstractTimeKeeper.h"

class TKStateHere;
class TKStateAway;
class TKStateOff;
class AbstractConfig;
class AbstractPresenceHandler;
class AbstractTimeHandler;
class HandlerFactory;

class TimeKeeper : public AbstractTimeKeeper
{
    public:
        TimeKeeper(AbstractConfig* config, AbstractTimeHandler* timeHandler, AbstractPresenceHandler* presenceHandler);
        virtual ~TimeKeeper();

        virtual void start();
        virtual void stop();

        virtual void updateStatus();
        virtual boost::posix_time::time_duration getTimerInterval() const;
        virtual bool isLate() const;

        virtual AbstractTimeKeeper::Status getStatus() const;
        virtual boost::posix_time::time_duration getInterval() const;
        virtual boost::posix_time::time_duration getTimeLeft() const;
        virtual boost::posix_time::ptime getHereStamp() const;
        virtual boost::posix_time::ptime getAwayStamp() const;

    protected:
    private:

        friend class TKState;
        friend class TKStateHere;
        friend class TKStateAway;
        friend class TKStateOff;

        void deleteStates();
        void setStatus(Status status);

        std::map<Status,TKState*> m_States;
        Status m_CurrentState;

        AbstractConfig* m_Config;
        AbstractTimeHandler* m_TimeHandler;
        AbstractPresenceHandler* m_PresenceHandler;

        boost::posix_time::ptime m_HereStamp;
        boost::posix_time::ptime m_AwayStamp;
        boost::posix_time::ptime m_LastAwayStamp;
        unsigned int m_NumTolerated;
};

#endif // TIMEKEEPER_H
