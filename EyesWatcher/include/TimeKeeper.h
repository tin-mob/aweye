/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

#include <map>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "TKState.h"
#include "AbstractTimeKeeper.h"

class TKStateHere;
class TKStateAway;
class TKStateOff;
class AbstractPresenceHandler;
class AbstractTimeHandler;

///@todo: cummulative pause alternative
class TimeKeeper : public AbstractTimeKeeper
{
    public:
        TimeKeeper(AbstractTimeHandler* timeHandler,
                   AbstractPresenceHandler* presenceHandler,
                   boost::posix_time::time_duration workLength,
                   boost::posix_time::time_duration pauseLength,
                   boost::posix_time::time_duration remFreq,
                   boost::posix_time::time_duration checkFreq,
                   unsigned int pauseTol,
                   unsigned int workTol);
        virtual ~TimeKeeper();

        virtual void start();
        virtual void stop();
        virtual void notifyHibernated(boost::posix_time::time_duration length);

        virtual void updateStatus();
        virtual boost::posix_time::time_duration getTimerInterval() const;
        virtual bool isLate() const;

        virtual AbstractTimeKeeper::Status getStatus() const;
        virtual boost::posix_time::time_duration getInterval() const;
        virtual boost::posix_time::time_duration getTimeLeft() const;
        virtual boost::posix_time::ptime getHereStamp() const;
        virtual boost::posix_time::ptime getAwayStamp() const;
        virtual boost::posix_time::time_duration getWorkTimeLeft() const;

        virtual void setWorkLength(boost::posix_time::time_duration workLength);
        virtual void setPauseLength(boost::posix_time::time_duration pauseLength);
        virtual void setRemFreq(boost::posix_time::time_duration remFreq);
        virtual void setCheckFreq(boost::posix_time::time_duration checkFreq);
        virtual void setPauseTol(unsigned int pauseTol);
        virtual void setWorkTol(unsigned int workTol);

    protected:
    private:

        friend class TKState;
        friend class TKStateHere;
        friend class TKStateAway;
        friend class TKStateOff;

        void deleteStates();
        void setStatus(Status status, bool cancelled = false);

        std::map<Status,TKState*> m_States;
        Status m_CurrentState;

        AbstractTimeHandler* m_TimeHandler;
        AbstractPresenceHandler* m_PresenceHandler;

        boost::posix_time::time_duration m_HereDur;
        boost::posix_time::time_duration m_AwayDur;
        boost::posix_time::ptime m_LastUpdate;
        boost::posix_time::ptime m_StartTimeUpdate;
        boost::posix_time::ptime m_TolerationTime;
        unsigned int m_NumTolerated;

        boost::posix_time::ptime m_HereStamp;
        boost::posix_time::ptime m_AwayStamp;
        boost::posix_time::ptime m_LastAwayStamp;

        boost::posix_time::time_duration m_WorkLength;
        boost::posix_time::time_duration m_PauseLength;
        boost::posix_time::time_duration m_RemFreq;
        boost::posix_time::time_duration m_CheckFreq;
        unsigned int m_PauseTol;
        unsigned int m_WorkTol;
};

#endif // TIMEKEEPER_H
