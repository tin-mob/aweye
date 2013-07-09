/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef TASKCONTEXT_H
#define TASKCONTEXT_H

#include <string>

namespace EW {

class TaskCaller;

// inherit to add your stuff
struct TaskContext
{
    TaskContext(std::string command, TaskCaller& caller) :
        m_Command(command), m_Caller(caller) {}

    virtual ~TaskContext() {}

    std::string m_Command;
    TaskCaller& m_Caller;
};
}

#endif // TASKCONTEXT_H
