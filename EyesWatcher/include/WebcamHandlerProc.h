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


#ifndef WEBCAMHANDLERPROC_H
#define WEBCAMHANDLERPROC_H

#include "AbstractPresenceHandler.h"
#include "IsHereCmd.h"
#include <functional>
#include <wx/process.h>

/// @todo becoming big for untestable (without wx) code...
class WebcamHandlerProc : public AbstractPresenceHandler
{
    public:
        WebcamHandlerProc(int index, std::string faceCascadeName,
                      int faceSizeX, int faceSizeY);
        ~WebcamHandlerProc();

        virtual void isHere(std::function<void (bool)> callBack);
        virtual void setCascade(std::string name);
        virtual void setIndex(int index);
        virtual void setFaceSize(unsigned int x, unsigned int y);
    protected:
    private:
        // delete itself after usage
        class WebcamHdlrProcess : public wxProcess
        {
            public:
                static WebcamHdlrProcess* create(std::function<void (bool)> callBack)
                {
                    return new WebcamHdlrProcess(callBack);
                }

                virtual void OnTerminate(int pid, int status)
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
            private:
                WebcamHdlrProcess(std::function<void (bool)> callBack) :
                    m_CallBack(callBack) {}
                virtual ~WebcamHdlrProcess() {}

                std::function<void (bool)> m_CallBack;
        };

        int m_index;
        std::string m_FaceCascadeName;
        int m_FaceSizeX;
        int m_FaceSizeY;
};

#endif // WEBCAMHANDLERPROC_H
