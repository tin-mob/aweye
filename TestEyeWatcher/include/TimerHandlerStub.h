#ifndef TIMERHANDLERSTUB_H
#define TIMERHANDLERSTUB_H

#include "AbstractTimerHandler.h"

class TimerHandlerStub : public AbstractTimerHandler
{
    public:
        TimerHandlerStub() : running(false) {}
        virtual ~TimerHandlerStub() {}
        virtual bool Start(int, bool) {return running = true;}
        virtual void Stop() {running = false;}
        bool running;
    protected:
    private:
};

#endif // TIMERHANDLERSTUB_H
