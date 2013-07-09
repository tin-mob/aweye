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
///@note running this in linux results in zombie processes, probably linked with :
/// https://groups.google.com/forum/#!topic/wx-users/tFXaa5N-yc0
/// http://trac.wxwidgets.org/ticket/10258
/// sigh...
///@todo test if this works in windows

#include "ew/TaskCaller.h"
#include "ew/TaskContext.h"
#include "ew/wx/Task.h"

#include <memory>

namespace EW { namespace WX {

Task::Task( std::shared_ptr<const TaskContext> context) : m_Context(context)
{
}
Task::~Task()
{
}

void Task::run(std::shared_ptr<const TaskContext> context)
{
    Task* task = new Task(context);
    wxExecute(context->m_Command, wxEXEC_ASYNC, task);
}

void Task::OnTerminate(int pid, int status)
{
    std::shared_ptr<const TaskContext> context = m_Context;

    // cannot use this after this
    delete this;
    context->m_Caller.onTaskEnded(status, context);
}
}}
