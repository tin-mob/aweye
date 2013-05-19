#ifndef ABSTRACTTIMER_H
#define ABSTRACTTIMER_H

#include "Subject.h"

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

#endif // ABSTRACTTIMER_H
