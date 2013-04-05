#ifndef ABSTRACTTIMERHANDLER_H
#define ABSTRACTTIMERHANDLER_H


class AbstractTimerHandler
{
    public:
        AbstractTimerHandler() {}
        virtual bool Start(int milliseconds = -1, bool oneShot = false) = 0;
        virtual void Stop() = 0;
    protected:
    private:
};

#endif // ABSTRACTTIMERHANDLER_H
