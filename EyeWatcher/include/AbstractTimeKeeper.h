#ifndef ABSTRACTTIMEKEEPER_H
#define ABSTRACTTIMEKEEPER_H

#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

#include <string>

class AbstractTimeKeeper
{
    public:
        enum Status { OFF, HERE, AWAY };
        static std::string getStatusStr(const Status s)
        {
            switch (s)
            {
                case AbstractTimeKeeper::OFF: return "Off";
                case AbstractTimeKeeper::HERE: return "Here";
                case AbstractTimeKeeper::AWAY: return "Away";
                default: assert(0);
            }
        }
        std::string getStatusStr() const
        {
            return AbstractTimeKeeper::getStatusStr(this->getStatus());
        }

        virtual void start() = 0;
        virtual void stop() = 0;

        virtual void updateStatus() = 0;
        virtual boost::posix_time::time_duration getTimerInterval() const = 0;
        virtual bool isLate() const = 0;

        virtual AbstractTimeKeeper::Status getStatus() const = 0;
        virtual boost::posix_time::time_duration getInterval() const = 0;
        virtual boost::posix_time::time_duration getTimeLeft() const = 0;
        virtual boost::posix_time::ptime getHereStamp() const = 0;
        virtual boost::posix_time::ptime getAwayStamp() const = 0;
    protected:
    private:
};

#endif // ABSTRACTTIMEKEEPER_H