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

#include "ew/AbstractPresenceHandler.h"
#include "ew/IsHereCmd.h"
#include "ew/wx/IsHereProcess.h"

namespace EW { namespace WX {

IsHereProcess::IsHereProcess(std::function<void (bool)> callBack) :
    m_CallBack(callBack)
{

}
IsHereProcess::~IsHereProcess()
{

}

void IsHereProcess::run(std::function<void (bool)> callBack, std::string cmd)
{
    IsHereProcess* process = new IsHereProcess(callBack);
    wxExecute(cmd, wxEXEC_ASYNC, process);
}

void IsHereProcess::OnTerminate(int pid, int status)
{
    auto callBack = m_CallBack;

    // cannot use this after this
    delete this;

    IsHereCmdRetCode code = (IsHereCmdRetCode)status;
    switch (code)
    {
        case IsHereCmdRetCode::INVALID_CAMERA:
            throw InvalidCameraException();
        case IsHereCmdRetCode::INVALID_CASCADE:
            throw MissingCascadeFileException();
        case IsHereCmdRetCode::INVALID_FACEX:
        case IsHereCmdRetCode::INVALID_FACEY:
        case IsHereCmdRetCode::INVALID_INDEX:
        case IsHereCmdRetCode::INVALID_NB_ARGS:
        case IsHereCmdRetCode::OTHER_ERROR:
            assert(false);
            throw GenericPresenceHandlerException();
        default:
            break;
    }

    callBack(code == IsHereCmdRetCode::HERE);
}
}}
