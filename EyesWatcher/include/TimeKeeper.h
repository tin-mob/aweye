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
#include <memory>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "TKState.h"
#include "AbstractTimeKeeper.h"

namespace EW
{
class TKStateHere;
class TKStateAway;
class TKStateOff;
class AbstractPresenceHandler;
class AbstractTimeHandler;

class TimeKeeper : public AbstractTimeKeeper
{
    public:
        TimeKeeper(AbstractTimeHandler& timeHandler,
                   AbstractPresenceHandler& presenceHandler,
                   boost::posix_time::time_duration workLength,
                   boost::posix_time::time_duration pauseLength,
                   boost::posix_time::time_duration remFreq,
                   boost::posix_time::time_duration checkFreq,
                   unsigned int pauseTol,
                   unsigned int workTol,
                   bool cummulPause);
        virtual ~TimeKeeper();

        TimeKeeper(const TimeKeeper&) = delete;
        TimeKeeper& operator=(const TimeKeeper&) = delete;

        virtual void start();
        virtual void stop();

        virtual bool checkUpdate();
        void updateCallback(bool isHere);
        virtual bool isLate() const;
        virtual bool isTolerating() const;

        virtual AbstractTimeKeeper::Status getStatus() const;
        virtual boost::posix_time::time_duration getInterval() const;
        virtual boost::posix_time::time_duration getTimeLeft() const;
        virtual boost::posix_time::ptime getHereStamp() const;
        virtual boost::posix_time::ptime getAwayStamp() const;
        virtual boost::posix_time::time_duration getWorkTimeLeft() const;
        virtual boost::posix_time::time_duration getRemFreq() const;

        virtual void setWorkLength(boost::posix_time::time_duration workLength);
        virtual void setPauseLength(boost::posix_time::time_duration pauseLength);
        virtual void setRemFreq(boost::posix_time::time_duration remFreq);
        virtual void setCheckFreq(boost::posix_time::time_duration checkFreq);
        virtual void setPauseTol(unsigned int pauseTol);
        virtual void setWorkTol(unsigned int workTol);
        virtual void setCummulPause(bool cummulPause);

    protected:
    private:

        friend class TKState;
        friend class TKStateHere;
        friend class TKStateAway;
        friend class TKStateOff;

        void notifyHibernated();
        void updateStatus();
        void setNextUpdate();
        void setStatus(Status status, bool cancelled = false);
        boost::posix_time::time_duration getUpdateOffset() const;

        std::map<Status,std::unique_ptr<TKState>> m_States;
        Status m_CurrentState;

        AbstractTimeHandler& m_TimeHandler;
        AbstractPresenceHandler& m_PresenceHandler;

        boost::posix_time::time_duration m_HereDur;
        boost::posix_time::time_duration m_AwayDur;
        boost::posix_time::ptime m_LastUpdate;
        boost::posix_time::ptime m_NextCheck;
        boost::posix_time::ptime m_StartTimeUpdate;
        boost::posix_time::ptime m_TolerationTime;
        unsigned int m_NumTolerated;
        bool m_StartedCheck;
        bool m_CompletedCheck;

        boost::posix_time::ptime m_HereStamp;
        boost::posix_time::ptime m_AwayStamp;
        boost::posix_time::ptime m_LastAwayStamp;

        boost::posix_time::time_duration m_WorkLength;
        boost::posix_time::time_duration m_PauseLength;
        boost::posix_time::time_duration m_RemFreq;
        boost::posix_time::time_duration m_CheckFreq;
        unsigned int m_PauseTol;
        unsigned int m_WorkTol;
        bool m_CummulPause;
};
}

#endif // TIMEKEEPER_H
