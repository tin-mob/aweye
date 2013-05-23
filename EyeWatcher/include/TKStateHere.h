/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef TKSTATEHERE_H
#define TKSTATEHERE_H

#include "TKState.h"

class TKStateHere : public TKState
{
    public:
        TKStateHere();
        virtual ~TKStateHere();

        virtual void updateStatus(TimeKeeper* parent);
        virtual void updateTimeStamps(TimeKeeper* parent);
        virtual boost::posix_time::time_duration getTimerInterval(const TimeKeeper* parent) const;
        virtual bool isLate(const TimeKeeper* parent) const;
        virtual boost::posix_time::time_duration getInterval(const TimeKeeper* parent) const;
        virtual boost::posix_time::time_duration getTimeLeft(const TimeKeeper* parent) const;
        virtual boost::posix_time::time_duration getWorkTimeLeft(const TimeKeeper* parent) const;
    protected:
    private:
};

#endif // TKSTATEHERE_H
