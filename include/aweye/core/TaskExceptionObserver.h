/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef TASKEXCEPTIONOBSERVER_H
#define TASKEXCEPTIONOBSERVER_H

#include <memory>

namespace Aweye {

class BaseException;
class TaskExceptionObserver
{
    public:
        virtual ~TaskExceptionObserver() {}
        virtual void onException(std::shared_ptr<const BaseException> exception) = 0;
    private:
};
}

#endif // TASKEXCEPTIONOBSERVER_H
