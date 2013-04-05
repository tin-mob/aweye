#ifndef WXTIMERHANDLER_H
#define WXTIMERHANDLER_H

#include "AbstractTimerHandler.h"

class wxTimer;
class wxTimerHandler : public AbstractTimerHandler
{
    public:
        wxTimerHandler(wxTimer* timer);
        virtual ~wxTimerHandler();
        virtual bool Start(int milliseconds = -1, bool oneShot = false);
        virtual void Stop();
    protected:
    private:
        wxTimer* m_timer;
};

#endif // WXTIMERHANDLER_H
