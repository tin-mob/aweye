/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef TKSTATEHERE_H
#define TKSTATEHERE_H

#include "aweye/core/TKState.h"

namespace Aweye {

class TKStateHere : public TKState
{
    public:
        TKStateHere();
        virtual ~TKStateHere();

        virtual void updateStatus(TimeKeeper& parent, bool isHere);
        virtual void initState(TimeKeeper& parent, bool cancelled);
        virtual boost::posix_time::ptime getNextUpdate(const TimeKeeper& parent) const;
        virtual bool isLate(const TimeKeeper& parent) const;
        virtual boost::posix_time::time_duration getInterval(const TimeKeeper& parent) const;
        virtual boost::posix_time::time_duration getTimeLeft(const TimeKeeper& parent,
                boost::posix_time::ptime now = boost::posix_time::not_a_date_time) const;
        virtual boost::posix_time::time_duration getWorkTimeLeft(const TimeKeeper& parent) const;
        virtual void addDuration(TimeKeeper& parent);
    protected:
    private:
};
}

#endif // TKSTATEHERE_H
