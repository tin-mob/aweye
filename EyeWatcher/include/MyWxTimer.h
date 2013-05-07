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
