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


#ifndef ABSTRACTTIMER_H
#define ABSTRACTTIMER_H

#include "Subject.h"

namespace EW
{
class AbstractTimer;
class TimerInterface
{
    public:
        virtual ~TimerInterface() {}
        virtual void onTimerRing(AbstractTimer* timer) = 0;
};

class AbstractTimer : public Subject<TimerInterface, AbstractTimer*>
{
    public:
        virtual ~AbstractTimer() {}
        virtual bool startTimer(long total_milliseconds, bool oneShot) = 0;
        virtual void stopTimer() = 0;
    protected:
    private:
};
}

#endif // ABSTRACTTIMER_H
