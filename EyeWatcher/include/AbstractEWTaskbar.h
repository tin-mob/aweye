#ifndef ABSTRACTEWTASKBAR_H
#define ABSTRACTEWTASKBAR_H

#include <string>
#include "Observer.h"

class AbstractEWTaskbar : public Observer
{
    public:
        virtual ~AbstractEWTaskbar() {}
        virtual void setPopupMenu( std::string hideRestoreLabel,
            std::string startStopLabel, std::string pauseResumeLabel,
            std::string onClock, std::string offClock,
            std::string runningClock, std::string leftClock) = 0;
        virtual void setIcon(std::string loc) = 0;
    protected:
    private:
};

#endif // ABSTRACTEWTASKBAR_H
