#ifndef ABSTRACTEWTASKBAR_H
#define ABSTRACTEWTASKBAR_H

#include <string>
#include "Observer.h"

class AbstractEWTaskbar : public Observer
{
    public:
        virtual ~AbstractEWTaskbar() {}
        virtual void setPopupMenu( bool running, bool snoozed,
            std::string onClock, std::string offClock,
            std::string runningClock, std::string leftClock) = 0;
        virtual void reloadIcon() = 0;

    protected:
    private:
};

#endif // ABSTRACTEWTASKBAR_H
