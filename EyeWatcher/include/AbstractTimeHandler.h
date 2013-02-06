#ifndef ABSTRACTTIMEHANDLER_H
#define ABSTRACTTIMEHANDLER_H

#include "boost/date_time/posix_time/posix_time_types.hpp"

class AbstractTimeHandler
{
    public:
        virtual ~AbstractTimeHandler() {};
        virtual boost::posix_time::ptime getTime() const = 0;
    protected:
    private:
};

#endif // ABSTRACTTIMEHANDLER_H
