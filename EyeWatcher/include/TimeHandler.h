#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include "AbstractTimeHandler.h"
#include "boost/date_time/posix_time/posix_time_types.hpp"

class TimeHandler : public AbstractTimeHandler
{
    public:
        TimeHandler();
        virtual ~TimeHandler();
        virtual boost::posix_time::ptime getTime() const;
    protected:
    private:
};

#endif // TIMEHANDLER_H
