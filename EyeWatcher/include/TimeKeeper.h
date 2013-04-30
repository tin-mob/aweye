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
        TimeKeeper(AbstractTimeHandler* timeHandler,
                   AbstractPresenceHandler* presenceHandler,
                   boost::posix_time::time_duration workLength,
                   boost::posix_time::time_duration pauseLength,
                   boost::posix_time::time_duration remFreq,
                   boost::posix_time::time_duration checkFreq,
                   unsigned int pauseTol);
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

        virtual void setWorkLength(boost::posix_time::time_duration workLength);
        virtual void setPauseLength(boost::posix_time::time_duration pauseLength);
        virtual void setRemFreq(boost::posix_time::time_duration remFreq);
        virtual void setCheckFreq(boost::posix_time::time_duration checkFreq);
        virtual void setPauseTol(unsigned int pauseTol);

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

        AbstractTimeHandler* m_TimeHandler;
        AbstractPresenceHandler* m_PresenceHandler;

        boost::posix_time::ptime m_HereStamp;
        boost::posix_time::ptime m_AwayStamp;
        boost::posix_time::ptime m_LastAwayStamp;
        unsigned int m_NumTolerated;

        boost::posix_time::time_duration m_WorkLength;
        boost::posix_time::time_duration m_PauseLength;
        boost::posix_time::time_duration m_RemFreq;
        boost::posix_time::time_duration m_CheckFreq;
        unsigned int m_PauseTol;
};

#endif // TIMEKEEPER_H
