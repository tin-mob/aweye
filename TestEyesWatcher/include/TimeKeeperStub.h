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


#ifndef TIMEKEEPERSTUB_H
#define TIMEKEEPERSTUB_H


#include "AbstractTimeKeeper.h"
#include "BaseException.h"
#include "AbstractTimeHandler.h"
#include "AbstractPresenceHandler.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/date_defs.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>

class TimeKeeperStub : public AbstractTimeKeeper
{
    public:
        TimeKeeperStub(AbstractTimeHandler* th = nullptr,
                   AbstractPresenceHandler* ph = nullptr,
                   boost::posix_time::time_duration wl = boost::posix_time::time_duration(00,00,00),
                   boost::posix_time::time_duration pl = boost::posix_time::time_duration(00,00,01),
                   boost::posix_time::time_duration rf = boost::posix_time::time_duration(00,00,10),
                   boost::posix_time::time_duration cf = boost::posix_time::time_duration(00,00,11),
                   unsigned int pt = 1000,
                   unsigned int wt = 1000,
                   bool cup = false) :
            m_Fail(false), m_Late(false), m_Updated(false), m_Status(AbstractTimeKeeper::OFF),
            m_HereStamp(boost::posix_time::ptime(boost::gregorian::date(2078,boost::date_time::Jan,10), boost::posix_time::time_duration(10,59,00))),
            m_AwayStamp(boost::posix_time::ptime(boost::gregorian::date(2078,boost::date_time::Jan,10), boost::posix_time::time_duration(11,31,01))),
            m_Interval(boost::posix_time::seconds(2)), m_Left(boost::posix_time::minutes(3)),
            m_WorkLeft(boost::posix_time::minutes(1)),
            m_WorkLength(wl), m_PauseLength(pl), m_RemFreq(rf), m_CheckFreq(cf), m_PauseTol(pt),
            m_WorkTol(wt), m_CummulPause(cup), m_TimeHandler(th), m_PresenceHandler(ph)
            {}
        TimeKeeperStub(AbstractTimeHandler& th,
                   AbstractPresenceHandler& ph,
                   boost::posix_time::time_duration wl = boost::posix_time::time_duration(00,00,00),
                   boost::posix_time::time_duration pl = boost::posix_time::time_duration(00,00,01),
                   boost::posix_time::time_duration rf = boost::posix_time::time_duration(00,00,10),
                   boost::posix_time::time_duration cf = boost::posix_time::time_duration(00,00,11),
                   unsigned int pt = 1000,
                   unsigned int wt = 1000,
                   bool cup = false) :
            m_Fail(false), m_Late(false), m_Updated(false), m_Status(AbstractTimeKeeper::OFF),
            m_HereStamp(boost::posix_time::ptime(boost::gregorian::date(2078,boost::date_time::Jan,10), boost::posix_time::time_duration(10,59,00))),
            m_AwayStamp(boost::posix_time::ptime(boost::gregorian::date(2078,boost::date_time::Jan,10), boost::posix_time::time_duration(11,31,01))),
            m_Interval(boost::posix_time::seconds(2)), m_Left(boost::posix_time::minutes(3)),
            m_WorkLeft(boost::posix_time::minutes(1)),
            m_WorkLength(wl), m_PauseLength(pl), m_RemFreq(rf), m_CheckFreq(cf), m_PauseTol(pt),
            m_WorkTol(wt), m_CummulPause(cup), m_TimeHandler(&th), m_PresenceHandler(&ph)
            {}
        virtual ~TimeKeeperStub() {}

        virtual void start()
        {
            if (m_Fail) { throw BaseException("Testing!"); }
            m_Status = AbstractTimeKeeper::HERE;
        }
        virtual void stop() {m_Status = AbstractTimeKeeper::OFF;}

        virtual bool checkUpdate()
        {
            if (m_Fail) { throw BaseException("Testing!"); }
            return m_Updated;
        }

        virtual boost::posix_time::time_duration getTimerInterval() const {return boost::posix_time::seconds(1);}
        virtual bool isLate() const {return m_Late;}

        virtual AbstractTimeKeeper::Status getStatus() const {return m_Status;}
        virtual boost::posix_time::time_duration getInterval() const {return m_Interval;}
        virtual boost::posix_time::time_duration getTimeLeft() const {return m_Left;}
        virtual boost::posix_time::ptime getHereStamp() const {return m_HereStamp;}
        virtual boost::posix_time::ptime getAwayStamp() const {return m_AwayStamp;}
        virtual boost::posix_time::time_duration getWorkTimeLeft() const {return m_WorkLeft;};

        virtual void setWorkLength(boost::posix_time::time_duration wl) {m_WorkLength = wl;}
        virtual void setPauseLength(boost::posix_time::time_duration pl) {m_PauseLength = pl;}
        virtual void setRemFreq(boost::posix_time::time_duration rf) {m_RemFreq = rf;}
        virtual void setCheckFreq(boost::posix_time::time_duration cf) {m_CheckFreq = cf;}
        virtual void setPauseTol(unsigned int pt) {m_PauseTol = pt;}
        virtual void setWorkTol(unsigned int wt) {m_WorkTol = wt;}
        virtual void setCummulPause(bool cup) {m_CummulPause = cup;}

        bool m_Fail;
        bool m_Late;
        bool m_Updated;
        AbstractTimeKeeper::Status m_Status;
        boost::posix_time::ptime m_HereStamp;
        boost::posix_time::ptime m_AwayStamp;
        boost::posix_time::time_duration m_Interval;
        boost::posix_time::time_duration m_Left;
        boost::posix_time::time_duration m_WorkLeft;

        boost::posix_time::time_duration m_WorkLength;
        boost::posix_time::time_duration m_PauseLength;
        boost::posix_time::time_duration m_RemFreq;
        boost::posix_time::time_duration m_CheckFreq;
        unsigned int m_PauseTol;
        unsigned int m_WorkTol;
        bool m_CummulPause;

        AbstractTimeHandler* m_TimeHandler;
        AbstractPresenceHandler* m_PresenceHandler;

    protected:
    private:
};

#endif // TIMEKEEPERSTUB_H
