#ifndef ABSTRACTTIMEHANDLER_H
#define ABSTRACTTIMEHANDLER_H

#include <time.h>

class AbstractTimeHandler
{
    public:
        virtual ~AbstractTimeHandler() {};
        virtual time_t getTime() const = 0;
    protected:
    private:
};

#endif // ABSTRACTTIMEHANDLER_H
