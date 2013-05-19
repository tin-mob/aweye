#ifndef TIMERSTUB_H
#define TIMERSTUB_H

#include "AbstractTimer.h"

class TimerStub : public AbstractTimer
{
    public:
        TimerStub() : running(false) {}
        virtual ~TimerStub() {}
        virtual bool startTimer(long total_milliseconds, bool oneShot)
        {
            running = true;
            return true;
        }
        virtual void stopTimer()
        {
            running = false;
        }
        void ring()
        {
            notify(&TimerInterface::onTimerRing, this);
        }

        bool running;
    protected:
    private:
};

#endif // TIMERSTUB_H
