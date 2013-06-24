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


#ifndef TIMERSTUB_H
#define TIMERSTUB_H

#include "ew/AbstractTimer.h"

namespace EW
{
class TimerStub : public AbstractTimer
{
    public:
        TimerStub() : m_Running(0) {}
        virtual ~TimerStub() {}
        virtual bool startTimer(long total_milliseconds, bool oneShot)
        {
            m_Running = total_milliseconds;
            return true;
        }
        virtual void stopTimer()
        {
            m_Running = 0;
        }
        void ring()
        {
            notify(&TimerInterface::onTimerRing, this);
        }

        unsigned int m_Running;
    protected:
    private:
};
}

#endif // TIMERSTUB_H
