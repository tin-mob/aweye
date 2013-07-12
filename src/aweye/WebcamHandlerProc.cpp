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


#include "aweye/AbstractUtils.h"
#include "aweye/IsHereCmd.h"
#include "aweye/TaskContext.h"
#include "aweye/TaskExceptionObserver.h"
#include "aweye/WebcamHandlerProc.h"

#include <assert.h>
#include <functional>
#include <memory>
#include <sstream>

namespace Aweye {

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
                notify(&TaskExceptionObserver::onException, std::make_exception_ptr(GenericPresenceHandlerException()));
                break;
            default:
                assert(false);
                break;
        }
    }
}
}
