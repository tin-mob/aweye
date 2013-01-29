#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include "AbstractTimeHandler.h"

class TimeHandler : public AbstractTimeHandler
{
    public:
        TimeHandler();
        virtual ~TimeHandler();
        virtual time_t getTime() const;
    protected:
    private:
};

#endif // TIMEHANDLER_H
