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


#ifndef ISHEREPROCESS_H
#define ISHEREPROCESS_H

#include <functional>
#include <memory>
#include <string>
#include <wx/process.h>

namespace Aweye {

struct TaskContext;

namespace WX {

// delete itself after usage
class Task : public wxProcess
{
    public:
        static void run(std::shared_ptr<const TaskContext> context);
        virtual void OnTerminate(int pid, int status);

    private:
        Task(std::shared_ptr<const TaskContext> context);
        virtual ~Task();

        std::shared_ptr<const TaskContext> m_Context;
};
}}

#endif // ISHEREPROCESS_H
