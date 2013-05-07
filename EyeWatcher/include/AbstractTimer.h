#ifndef ABSTRACTTIMER_H
#define ABSTRACTTIMER_H

#include "Observer.h"
class AbstractTimer : public Observable
{
    public:
        virtual ~AbstractTimer() {}
        virtual bool startTimer(long total_milliseconds, bool oneShot) = 0;
        virtual void stopTimer() = 0;
    protected:
    private:
};

#endif // ABSTRACTTIMER_H
