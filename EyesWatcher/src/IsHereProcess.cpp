#include "AbstractPresenceHandler.h"
#include "IsHereCmd.h"
#include "IsHereProcess.h"

IsHereProcess::IsHereProcess(std::function<void (bool)> callBack) :
    m_CallBack(callBack)
{

}
IsHereProcess::~IsHereProcess()
{

}

void IsHereProcess::run(std::function<void (bool)> callBack, wxString cmd)
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
