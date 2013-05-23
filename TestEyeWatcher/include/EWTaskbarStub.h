#ifndef EWTASKBARSTUB_H
#define EWTASKBARSTUB_H

#include "AbstractEWTaskbar.h"

class EWTaskbarStub : public AbstractEWTaskbar
{
    public:
        EWTaskbarStub() : hideRestoreLabel(""),
            startStopLabel(""), pauseResumeLabel(""), onClock(""),
            offClock(""), runningClock(""), leftClock(""),
            loc(""), presenter(nullptr){}
        virtual ~EWTaskbarStub() {}

        virtual void setPopupMenuCommands( std::string hrl,
            std::string ssl, std::string prl)
        {
            hideRestoreLabel = hrl;
            startStopLabel = ssl;
            pauseResumeLabel = prl;
        }

        virtual void setPopupMenuTimes( std::string onc, std::string offc,
            std::string rc, std::string lc)
        {
            onClock = onc;
            offClock = offc;
            runningClock = rc;
            leftClock = lc;
        }

        virtual void setIcon(std::string l)
        {
            loc = l;
        }

        std::string hideRestoreLabel;
        std::string startStopLabel;
        std::string pauseResumeLabel;
        std::string onClock;
        std::string offClock;
        std::string runningClock;
        std::string leftClock;
        std::string loc;

        AbstractEWViewPres<AbstractEWTaskbar>* presenter;
    protected:
    private:
};


#endif // EWTASKBARSTUB_H
