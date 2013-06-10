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


#ifndef ABSTRACTTIMEKEEPER_H
#define ABSTRACTTIMEKEEPER_H

#include "boost/date_time/posix_time/posix_time_types.hpp"
#include <string>

class AbstractTimeKeeper
{
    public:
        enum Status { OFF, HERE, AWAY };
        static std::string getStatusStr(const Status s)
        {
            switch (s)
            {
                case AbstractTimeKeeper::OFF: return "Off";
                case AbstractTimeKeeper::HERE: return "Here";
                case AbstractTimeKeeper::AWAY: return "Away";
                default: assert(0); return "";
            }
        }
        std::string getStatusStr() const
        {
            return AbstractTimeKeeper::getStatusStr(this->getStatus());
        }

        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void notifyHibernated() = 0;

        virtual void updateStatus() = 0;
        virtual boost::posix_time::time_duration getTimerInterval() const = 0;
        virtual bool isLate() const = 0;

        virtual AbstractTimeKeeper::Status getStatus() const = 0;
        virtual boost::posix_time::time_duration getInterval() const = 0;
        virtual boost::posix_time::time_duration getTimeLeft() const = 0;
        virtual boost::posix_time::ptime getHereStamp() const = 0;
        virtual boost::posix_time::ptime getAwayStamp() const = 0;
        virtual boost::posix_time::time_duration getWorkTimeLeft() const = 0;

        virtual void setWorkLength(boost::posix_time::time_duration workLength) = 0;
        virtual void setPauseLength(boost::posix_time::time_duration pauseLength) = 0;
        virtual void setRemFreq(boost::posix_time::time_duration remFreq) = 0;
        virtual void setCheckFreq(boost::posix_time::time_duration checkFreq) = 0;
        virtual void setPauseTol(unsigned int pauseTol) = 0;
        virtual void setWorkTol(unsigned int workTol) = 0;
        virtual void setCummulPause(bool cummulPause) = 0;
    protected:
    private:
};

#endif // ABSTRACTTIMEKEEPER_H
