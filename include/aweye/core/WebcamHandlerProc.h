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
///@todo private inheritance for fields?


#ifndef WEBCAMHANDLERPROC_H
#define WEBCAMHANDLERPROC_H

#include "aweye/core/AbstractPresenceHandler.h"
#include "aweye/core/TaskCaller.h"
#include "aweye/core/TaskContext.h"
#include "aweye/core/Subject.h"

#include <functional>
#include <memory>

namespace Aweye {

class AbstractUtils;
class BaseException;
enum class IsHereCmdRetCode;
class TaskExceptionObserver;
class WebcamHandlerProc : public AbstractPresenceHandler, public TaskCaller,
    public Subject<TaskExceptionObserver, std::shared_ptr<const BaseException>>
{
    public:
        WebcamHandlerProc(AbstractUtils& utils,
            std::function<void (std::shared_ptr<const TaskContext> context)> cmd,
            int index, std::string faceCascadeName, int faceSizeX, int faceSizeY, 
			std::string isHereCmd);
        ~WebcamHandlerProc();

        virtual void isHere(std::function<void (bool)> callBack);
        virtual void onTaskEnded(int status, std::shared_ptr<const TaskContext> context);
        virtual void setCascade(std::string name);
        virtual void setIndex(int index);
        virtual void setFaceSize(unsigned int x, unsigned int y);
    protected:
    private:
        AbstractUtils& m_Utils;
        std::function<void (std::shared_ptr<const TaskContext> context)> m_Cmd;

        int m_index;
        std::string m_FaceCascadeName;
        int m_FaceSizeX;
        int m_FaceSizeY;
		std::string m_IsHereCmd;
};

struct IsHereTaskContext : public TaskContext
{
    IsHereTaskContext(std::string command, TaskCaller& caller,
                      std::function<void (bool)> timeKeeperCallback) :
        TaskContext(command, caller), m_TimeKeeperCallback(timeKeeperCallback)
    {
    }
    virtual ~IsHereTaskContext() {}

    std::function<void (bool)> m_TimeKeeperCallback;
};
}

#endif // WEBCAMHANDLERPROC_H
