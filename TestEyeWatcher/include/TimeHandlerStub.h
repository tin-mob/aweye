/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef TIMEHANDLERSTUB_H
#define TIMEHANDLERSTUB_H

#include "AbstractTimeHandler.h"
#include "boost/date_time/posix_time/posix_time.hpp"

class TimeHandlerStub : public AbstractTimeHandler
{
     public:
        TimeHandlerStub(boost::posix_time::ptime time =
                        boost::posix_time::second_clock::local_time()) : m_time(time) {}
        virtual ~TimeHandlerStub() {}
        virtual boost::posix_time::ptime getTime() const
        {
            return this->m_time;
        }
        virtual void setTime(boost::posix_time::ptime time)
        {
            this->m_time = time;
        }

    protected:
    private:
        boost::posix_time::ptime m_time;
};

#endif // TIMEHANDLERSTUB_H
