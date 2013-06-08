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

void TKStateHere::updateStatus(TimeKeeper* parent)
{
    if (!parent->m_PresenceHandler->isHere())
    {
        if (this->getTimeLeft(parent) > boost::posix_time::time_duration(0,0,0,0) ||
            parent->m_NumTolerated != 0)
        {
            if (parent->m_NumTolerated == 0)
            {
                parent->m_TolerationTime = parent->m_LastUpdate;
            }

            if (parent->m_NumTolerated < parent->m_PauseTol)
            {
                ++parent->m_NumTolerated;
            }
            else
            {
                parent->setStatus(AbstractTimeKeeper::AWAY, true);
            }
        }
        else
        {
            parent->setStatus(AbstractTimeKeeper::AWAY);
        }
    }
    else
    {
        parent->m_NumTolerated = 0;
    }
}

void TKStateHere::initState(TimeKeeper* parent, bool cancelled)
{
    if (!cancelled)
    {
        parent->m_HereStamp = parent->m_TolerationTime.is_special() ?
            parent->m_StartTimeUpdate : parent->m_TolerationTime;
    }
    if (!parent->m_CummulPause)
    {
        if (cancelled)
        {
            parent->m_AwayStamp = parent->m_LastAwayStamp;
            parent->m_HereDur += parent->m_AwayDur;
        }
        parent->m_AwayDur = boost::posix_time::seconds(0);
    }
    else
    {
        if (cancelled)
        {
            if (!parent->m_TolerationTime.is_special())
            {
                boost::posix_time::time_duration interval =
                    parent->m_TimeHandler->getTime() - parent->m_TolerationTime;
                parent->m_HereDur += interval;
                parent->m_AwayDur -= interval;
            }
        }
        parent->m_AwayDur = boost::posix_time::seconds(0);
    }

    parent->m_NumTolerated = 0;
}

boost::posix_time::time_duration TKStateHere::getTimerInterval(const TimeKeeper* parent) const
{
    boost::posix_time::time_duration timerInterval = parent->m_CheckFreq;
    boost::posix_time::time_duration remaining = this->getTimeLeft(parent);

    if (remaining <= boost::posix_time::seconds(0))
    {
        if (parent->m_CheckFreq > parent->m_RemFreq)
        {
            timerInterval = parent->m_RemFreq;
        }
        else
        {
            timerInterval = parent->m_CheckFreq;
        }
    }
    else if (remaining < parent->m_CheckFreq)
    {
        timerInterval =  remaining;
    }

    boost::posix_time::time_duration offset =
        parent->m_TimeHandler->getTime() - parent->m_StartTimeUpdate;

    return timerInterval - offset;
}

bool TKStateHere::isLate(const TimeKeeper* parent) const
{
    return parent->m_WorkLength <= parent->m_HereDur + (parent->m_TimeHandler->getTime() - parent->m_LastUpdate);
}

boost::posix_time::time_duration TKStateHere::getInterval(const TimeKeeper* parent) const
{
    return parent->m_HereDur + (parent->m_TimeHandler->getTime() - parent->m_LastUpdate);
}

boost::posix_time::time_duration TKStateHere::getTimeLeft(const TimeKeeper* parent) const
{
    return parent->m_WorkLength - parent->m_HereDur - (parent->m_TimeHandler->getTime() - parent->m_LastUpdate);
}

boost::posix_time::time_duration TKStateHere::getWorkTimeLeft(const TimeKeeper* parent) const
{
    return this->getTimeLeft(parent);
}

void TKStateHere::addDuration(TimeKeeper* parent)
{
    parent->m_HereDur += (parent->m_TimeHandler->getTime() - parent->m_LastUpdate);
}
