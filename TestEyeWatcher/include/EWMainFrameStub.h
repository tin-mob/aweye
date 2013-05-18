#ifndef EWMAINFRAMESTUB_H
#define EWMAINFRAMESTUB_H

#include "AbstractEWMainFrame.h"

class EWMainFrameStub : public AbstractEWMainFrame
{
    public:
        EWMainFrameStub() : running(false), lastTotal(-1), status(""), onClock(""),
                            runningClock(""), leftClock("") {}
        virtual ~EWMainFrameStub() {}

        virtual void setValues( std::string s, std::string onC,
                               std::string offC, std::string r,
                               std::string l)
        {
            status = s;
            onClock = onC;
            offClock = offC;
            runningClock = r;
            leftClock = l;
        }

        virtual void startTimer(long total_milliseconds)
        {
            running = true;
            lastTotal = total_milliseconds;
        }

        virtual void stopTimer()
        {
            running = false;
        }

        virtual void show() {}

        bool running;
        long lastTotal;
        std::string status;
        std::string onClock;
        std::string offClock;
        std::string runningClock;
        std::string leftClock;

    protected:
    private:
};

#endif // EWMAINFRAMESTUB_H
