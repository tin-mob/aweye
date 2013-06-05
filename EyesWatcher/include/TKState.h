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


#ifndef TKSTATE_H
#define TKSTATE_H

#include "boost/date_time/posix_time/posix_time_types.hpp"

class TimeKeeper;
class TKState
{
    public:
        virtual ~TKState() {}

        virtual void updateStatus(TimeKeeper* parent) = 0;
        virtual void initState(TimeKeeper* parent, bool cancelled) = 0;
        virtual boost::posix_time::time_duration getTimerInterval(const TimeKeeper* parent) const = 0;
        virtual bool isLate(const TimeKeeper* parent) const = 0;
        virtual boost::posix_time::time_duration getInterval(const TimeKeeper* parent) const = 0;
        virtual boost::posix_time::time_duration getTimeLeft(const TimeKeeper* parent) const = 0;
        virtual boost::posix_time::time_duration getWorkTimeLeft(const TimeKeeper* parent) const = 0;
        virtual void addDuration(TimeKeeper* parent) = 0;
    protected:
    private:
};

#endif // TKSTATE_H
