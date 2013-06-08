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
            fail(false), late(false), status(AbstractTimeKeeper::OFF),
            hereStamp(boost::posix_time::ptime(boost::gregorian::date(2078,boost::date_time::Jan,10), boost::posix_time::time_duration(10,59,00))),
            awayStamp(boost::posix_time::ptime(boost::gregorian::date(2078,boost::date_time::Jan,10), boost::posix_time::time_duration(11,31,01))),
            interval(boost::posix_time::seconds(2)), left(boost::posix_time::minutes(3)),
            workLeft(boost::posix_time::minutes(1)),
            workLength(wl), pauseLength(pl), remFreq(rf), checkFreq(cf), pauseTol(pt),
            workTol(wt), cummulPause(cup), timeHandler(th), presenceHandler(ph)
            {}
        virtual ~TimeKeeperStub() {}

        virtual void start()
        {
            if (fail) { throw BaseException("Testing!"); }
            status = AbstractTimeKeeper::HERE;
        }
        virtual void stop() {status = AbstractTimeKeeper::OFF;}

        virtual void notifyHibernated(boost::posix_time::time_duration length) {}

        virtual void updateStatus()
                {
            if (fail) { throw BaseException("Testing!"); }
            status = AbstractTimeKeeper::HERE;
        }

        virtual boost::posix_time::time_duration getTimerInterval() const {return boost::posix_time::seconds(1);}
        virtual bool isLate() const {return late;}

        virtual AbstractTimeKeeper::Status getStatus() const {return status;}
        virtual boost::posix_time::time_duration getInterval() const {return interval;}
        virtual boost::posix_time::time_duration getTimeLeft() const {return left;}
        virtual boost::posix_time::ptime getHereStamp() const {return hereStamp;}
        virtual boost::posix_time::ptime getAwayStamp() const {return awayStamp;}
        virtual boost::posix_time::time_duration getWorkTimeLeft() const {return workLeft;};

        virtual void setWorkLength(boost::posix_time::time_duration wl) {workLength = wl;}
        virtual void setPauseLength(boost::posix_time::time_duration pl) {pauseLength = pl;}
        virtual void setRemFreq(boost::posix_time::time_duration rf) {remFreq = rf;}
        virtual void setCheckFreq(boost::posix_time::time_duration cf) {checkFreq = cf;}
        virtual void setPauseTol(unsigned int pt) {pauseTol = pt;}
        virtual void setWorkTol(unsigned int wt) {workTol = wt;}
        virtual void setCummulPause(bool cup) {cummulPause = cup;}

        bool fail;
        bool late;
        AbstractTimeKeeper::Status status;
        boost::posix_time::ptime hereStamp;
        boost::posix_time::ptime awayStamp;
        boost::posix_time::time_duration interval;
        boost::posix_time::time_duration left;
        boost::posix_time::time_duration workLeft;

        boost::posix_time::time_duration workLength;
        boost::posix_time::time_duration pauseLength;
        boost::posix_time::time_duration remFreq;
        boost::posix_time::time_duration checkFreq;
        unsigned int pauseTol;
        unsigned int workTol;
        bool cummulPause;

        AbstractTimeHandler* timeHandler;
        AbstractPresenceHandler* presenceHandler;

    protected:
    private:
};

#endif // TIMEKEEPERSTUB_H
