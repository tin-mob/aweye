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


#include "TKStateHere.h"
#include "TimeKeeper.h"
#include "AbstractPresenceHandler.h"
#include "AbstractTimeHandler.h"
#include "boost/date_time/posix_time/posix_time.hpp"

TKStateHere::TKStateHere()
{
}

TKStateHere::~TKStateHere()
{
}

void TKStateHere::updateStatus(TimeKeeper& parent, bool isHere)
{
    if (!isHere)
    {
        if (parent.m_NumTolerated++ == 0)
        {
            parent.m_TolerationTime = parent.m_LastUpdate;
        }
        if (parent.m_NumTolerated > parent.m_WorkTol)
        {
            parent.setStatus(AbstractTimeKeeper::AWAY,
                getTimeLeft(parent, parent.m_TolerationTime) > boost::posix_time::time_duration(0,0,0,0));
        }
    }
    else
    {
        parent.m_NumTolerated = 0;
    }
}

void TKStateHere::initState(TimeKeeper& parent, bool cancelled)
{
    if (!cancelled)
    {
        if (!parent.m_TolerationTime.is_special())
        {
            parent.m_HereStamp = parent.m_TolerationTime;
            parent.m_HereDur = parent.m_LastUpdate - parent.m_TolerationTime;
        }
        else
        {
            parent.m_HereStamp = parent.m_LastUpdate;
            parent.m_HereDur = boost::posix_time::seconds(0);
        }
    }
    if (!parent.m_CummulPause)
    {
        if (cancelled)
        {
            parent.m_AwayStamp = parent.m_LastAwayStamp;
            parent.m_HereDur += parent.m_AwayDur;
        }
        parent.m_AwayDur = boost::posix_time::seconds(0);
    }
    else
    {
        if (cancelled)
        {
            if (!parent.m_TolerationTime.is_special())
            {
                const boost::posix_time::time_duration interval =
                    parent.m_LastUpdate - parent.m_TolerationTime;
                parent.m_HereDur += interval;
                parent.m_AwayDur -= interval;
            }
        }
        else
        {
            parent.m_AwayDur = boost::posix_time::seconds(0);
        }
    }

    parent.m_NumTolerated = 0;
}

boost::posix_time::ptime TKStateHere::getNextUpdate(const TimeKeeper& parent) const
{
    boost::posix_time::time_duration timerInterval = parent.m_CheckFreq;
    const boost::posix_time::time_duration remaining = getTimeLeft(parent, parent.m_StartTimeUpdate);

    if (remaining <= boost::posix_time::seconds(0))
    {
        if (parent.m_CheckFreq > parent.m_RemFreq)
        {
            timerInterval = parent.m_RemFreq;
        }
        else
        {
            timerInterval = parent.m_CheckFreq;
        }
    }
    else if (remaining < parent.m_CheckFreq)
    {
        timerInterval =  remaining;
    }
    return parent.m_HereStamp + parent.m_HereDur + parent.m_AwayDur + timerInterval;
}

bool TKStateHere::isLate(const TimeKeeper& parent) const
{
    return parent.m_WorkLength <= parent.m_HereDur + (parent.m_TimeHandler.getTime() - parent.m_LastUpdate);
}

boost::posix_time::time_duration TKStateHere::getInterval(const TimeKeeper& parent) const
{
    return parent.m_HereDur + (parent.m_TimeHandler.getTime() - parent.m_LastUpdate);
}

boost::posix_time::time_duration TKStateHere::getTimeLeft(const TimeKeeper& parent,
                boost::posix_time::ptime now) const
{
    if (now.is_special())
    {
        now = parent.m_TimeHandler.getTime();
    }
    return parent.m_WorkLength - parent.m_HereDur - (now - parent.m_LastUpdate);
}

boost::posix_time::time_duration TKStateHere::getWorkTimeLeft(const TimeKeeper& parent) const
{
    if (parent.m_AwayDur < parent.m_PauseLength)
    {
        return getTimeLeft(parent);
    }
    else
    {
        return parent.m_WorkLength;
    }
}

void TKStateHere::addDuration(TimeKeeper& parent)
{
    parent.m_HereDur += (parent.m_StartTimeUpdate - parent.m_LastUpdate);
}
