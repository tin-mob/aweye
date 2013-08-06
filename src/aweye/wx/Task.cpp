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
///@note running this in linux with version < 2.9.5 results in zombie processes
///@todo test if this works in windows

#include "aweye/core/TaskCaller.h"
#include "aweye/core/TaskContext.h"
#include "aweye/wx/Task.h"

#include <memory>

namespace Aweye { namespace WX {

Task::Task( std::shared_ptr<const TaskContext> context) : m_Context(context)
{
}
Task::~Task()
{
}

void Task::run(std::shared_ptr<const TaskContext> context)
{
    Task* task = new Task(context);
    wxExecute(context->m_Command, wxEXEC_ASYNC | wxEXEC_HIDE_CONSOLE, task);
}

void Task::OnTerminate(int pid, int status)
{
    std::shared_ptr<const TaskContext> context = m_Context;

    // cannot use this after this
    delete this;
    context->m_Caller.onTaskEnded(status, context);
}
}}
