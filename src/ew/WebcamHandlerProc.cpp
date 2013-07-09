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


#include "ew/AbstractUtils.h"
#include "ew/IsHereCmd.h"
#include "ew/TaskContext.h"
#include "ew/TaskExceptionObserver.h"
#include "ew/WebcamHandlerProc.h"

#include <assert.h>
#include <functional>
#include <memory>
#include <sstream>

namespace EW {

WebcamHandlerProc::WebcamHandlerProc(AbstractUtils& utils,
    std::function<void (std::shared_ptr<const TaskContext> context)> cmd,
    int index, std::string faceCascadeName, int faceSizeX, int faceSizeY) :
    m_Utils(utils), m_Cmd(cmd), m_index(index), m_FaceCascadeName(faceCascadeName),
    m_FaceSizeX(faceSizeX), m_FaceSizeY(faceSizeY)
{
    //ctor
}

WebcamHandlerProc::~WebcamHandlerProc()
{
    //dtor
}

void WebcamHandlerProc::setCascade(std::string name)
{
    m_FaceCascadeName = name;
}

void WebcamHandlerProc::setIndex(int index)
{
    m_index = index;
}

void WebcamHandlerProc::setFaceSize(unsigned int x, unsigned int y)
{
    m_FaceSizeX = x;
    m_FaceSizeY = y;
}

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

///@note IsHereCmd in same path than main executable,
void WebcamHandlerProc::isHere(std::function<void (bool)> callBack)
{
    // validate m_FaceCascadeName (and prevent injection)
    if (!m_Utils.fileExists(m_FaceCascadeName))
    {
        throw MissingCascadeFileException();
    }
    std::ostringstream s;
    s  << "./IsHereCmd '" << m_index << "' '" << m_FaceCascadeName << "' '"
        << m_FaceSizeX << "' '" << m_FaceSizeY << "'";

    std::shared_ptr<const TaskContext> contextPtr(new IsHereTaskContext(s.str(), *this, callBack));
    m_Cmd(contextPtr);
}

void WebcamHandlerProc::onTaskEnded(int status, std::shared_ptr<const TaskContext> context)
{
    const IsHereTaskContext* isHereContext = dynamic_cast<const IsHereTaskContext*>(&*context);
    if (isHereContext == nullptr)
    {
        assert(false);
        notify(&TaskExceptionObserver::onException, std::make_exception_ptr(GenericPresenceHandlerException()));
    }
    else
    {
        IsHereCmdRetCode code = (IsHereCmdRetCode)status;
        switch (code)
        {
            case IsHereCmdRetCode::HERE:
                isHereContext->m_TimeKeeperCallback(true);
                break;
            case IsHereCmdRetCode::AWAY:
                isHereContext->m_TimeKeeperCallback(false);
                break;
            case IsHereCmdRetCode::INVALID_CAMERA:
                notify(&TaskExceptionObserver::onException, std::make_exception_ptr(InvalidCameraException()));
                break;
            case IsHereCmdRetCode::INVALID_CASCADE:
                notify(&TaskExceptionObserver::onException, std::make_exception_ptr(MissingCascadeFileException()));
                break;
            case IsHereCmdRetCode::INVALID_FACEX:
            case IsHereCmdRetCode::INVALID_FACEY:
            case IsHereCmdRetCode::INVALID_INDEX:
            case IsHereCmdRetCode::INVALID_NB_ARGS:
            case IsHereCmdRetCode::OTHER_ERROR:
                assert(false);
                notify(&TaskExceptionObserver::onException, std::make_exception_ptr(GenericPresenceHandlerException()));
                break;
            default:
                assert(false);
                break;
        }
    }
}
}
