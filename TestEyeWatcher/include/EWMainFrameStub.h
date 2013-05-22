#ifndef EWMAINFRAMESTUB_H
#define EWMAINFRAMESTUB_H

#include "AbstractEWMainFrame.h"

class EWMainFrameStub : public AbstractEWMainFrame
{
    public:
        EWMainFrameStub() : closed(false), shown(false), status(""),
            onClock(""), runningClock(""), leftClock(""),
            pauseLabel(""), startLabel("") {}
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

        virtual void show(bool show = true) {shown = show;}

        bool closed;
        bool shown;
        std::string status;
        std::string onClock;
        std::string offClock;
        std::string runningClock;
        std::string leftClock;
        std::string pauseLabel;
        std::string startLabel;

        virtual void setPauseButtonLabel(std::string label) {pauseLabel = label;}
        virtual void setStartButtonLabel(std::string label) {startLabel = label;}
        virtual void close() {closed = true;}

    protected:
    private:
};

#endif // EWMAINFRAMESTUB_H
