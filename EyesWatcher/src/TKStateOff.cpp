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


#include "TKStateOff.h"
#include "TimeKeeper.h"
#include "boost/date_time/posix_time/posix_time.hpp"

TKStateOff::TKStateOff()
{
}

TKStateOff::~TKStateOff()
{
}


void TKStateOff::updateStatus(TimeKeeper& parent)
{
}

void TKStateOff::initState(TimeKeeper& parent, bool cancelled)
{
    parent.m_HereStamp = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
    parent.m_AwayStamp = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
    parent.m_HereDur = boost::posix_time::seconds(0);
    parent.m_AwayDur = boost::posix_time::seconds(0);
    parent.m_LastUpdate = boost::posix_time::not_a_date_time;
    parent.m_NextCheck = boost::posix_time::not_a_date_time;
}

boost::posix_time::ptime TKStateOff::getNextUpdate(const TimeKeeper&) const
{
    return boost::posix_time::not_a_date_time;
}

bool TKStateOff::isLate(const TimeKeeper&) const
{
    return false;
}

boost::posix_time::time_duration TKStateOff::getInterval(const TimeKeeper&) const
{
    return boost::posix_time::time_duration(0,0,0,0);
}

boost::posix_time::time_duration TKStateOff::getTimeLeft(const TimeKeeper& parent, bool isUpdate) const
{
    return boost::posix_time::time_duration(0,0,0,0);
}

boost::posix_time::time_duration TKStateOff::getWorkTimeLeft(const TimeKeeper& parent) const
{
    return boost::posix_time::not_a_date_time;
}

void TKStateOff::addDuration(TimeKeeper& parent)
{
}
