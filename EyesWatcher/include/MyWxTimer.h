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


#ifndef MYWXTIMER_H
#define MYWXTIMER_H

#include "AbstractTimer.h"
#include <wx/timer.h>

class MyWxTimer : public AbstractTimer, public wxTimer
{
    public:
        MyWxTimer();
        virtual ~MyWxTimer();
        virtual bool startTimer(long total_milliseconds, bool oneShot);
        virtual void stopTimer();
    protected:
    private:
        void Notify();
};

#endif // MYWXTIMER_H
