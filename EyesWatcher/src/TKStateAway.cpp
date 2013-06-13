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


#include "TKStateAway.h"
#include "TimeKeeper.h"
#include "AbstractPresenceHandler.h"
#include "AbstractTimeHandler.h"
#include "boost/date_time/posix_time/posix_time.hpp"

TKStateAway::TKStateAway()
{
}

TKStateAway::~TKStateAway()
{
}

void TKStateAway::updateStatus(TimeKeeper& parent)
{
    if (parent.m_PresenceHandler.isHere())
    {
        if (parent.m_NumTolerated != 0 ||
            getTimeLeft(parent, true) > boost::posix_time::time_duration(0,0,0,0))
        {
            if (parent.m_PauseTol > 0)
            {
                if (parent.m_NumTolerated++ == 0)
                {
                    parent.m_TolerationTime = parent.m_LastUpdate;
                }
            }
            if (parent.m_PauseTol == 0 || parent.m_NumTolerated > parent.m_PauseTol)
            {
                parent.setStatus(AbstractTimeKeeper::HERE, true);
            }
        }
        else
        {
            parent.setStatus(AbstractTimeKeeper::HERE);
        }
    }
    else
    {
        parent.m_NumTolerated = 0;
    }
}

void TKStateAway::initState(TimeKeeper& parent, bool cancelled)
{
    parent.m_NumTolerated = 0;
    parent.m_LastAwayStamp = parent.m_AwayStamp;

    if (cancelled)
    {
        if (!parent.m_TolerationTime.is_special())
        {
            const boost::posix_time::time_duration interval =
                parent.m_StartTimeUpdate - parent.m_TolerationTime;
            parent.m_AwayDur += interval;
            parent.m_HereDur -= interval;
            parent.m_AwayStamp = parent.m_TolerationTime;
        }
        else
        {
            parent.m_AwayStamp = parent.m_LastUpdate;
        }
    }
    else
    {
        parent.m_AwayDur = boost::posix_time::seconds(0);
        parent.m_AwayStamp = parent.m_LastUpdate;
    }
}

boost::posix_time::time_duration TKStateAway::getTimerInterval(const TimeKeeper& parent) const
{
    boost::posix_time::time_duration timerInterval = parent.m_CheckFreq;
    const boost::posix_time::time_duration remaining = getTimeLeft(parent);

    if (remaining <= boost::posix_time::seconds(0))
    {
        timerInterval = parent.m_CheckFreq;
    }
    else if (remaining < parent.m_CheckFreq)
    {
        timerInterval = remaining;
    }
    return timerInterval - parent.getUpdateOffset();
}

bool TKStateAway::isLate(const TimeKeeper& parent) const
{
    return parent.m_WorkLength <= parent.m_HereDur &&
        parent.m_AwayDur < parent.m_PauseLength;
}

boost::posix_time::time_duration TKStateAway::getInterval(const TimeKeeper& parent) const
{
    return parent.m_AwayDur + (parent.m_TimeHandler.getTime() - parent.m_LastUpdate);
}

boost::posix_time::time_duration TKStateAway::getTimeLeft(const TimeKeeper& parent, bool isUpdate) const
{
    return parent.m_PauseLength - parent.m_AwayDur -
        ((isUpdate ? parent.m_StartTimeUpdate : parent.m_TimeHandler.getTime()) - parent.m_LastUpdate);
}

boost::posix_time::time_duration TKStateAway::getWorkTimeLeft(const TimeKeeper& parent) const
{
    if (parent.m_AwayDur < parent.m_PauseLength)
    {
        return parent.m_WorkLength - parent.m_HereDur;
    }
    else
    {
        return parent.m_WorkLength;
    }
}

void TKStateAway::addDuration(TimeKeeper& parent)
{
    parent.m_AwayDur += (parent.m_StartTimeUpdate - parent.m_LastUpdate);
}
