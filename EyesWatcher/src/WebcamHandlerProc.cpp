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


#include "WebcamHandlerProc.h"
#include "WebcamHandler.h"
#include "IsHereCmd.h"
#include <wx/stdpaths.h>

WebcamHandlerProc::WebcamHandlerProc(int index, std::string faceCascadeName,
                             int faceSizeX, int faceSizeY) :
    m_index(index), m_FaceCascadeName(faceCascadeName),
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

/// @note IsHereCmd in same path than main executable,
///      m_FaceCascadeName is sanitized via Config

bool WebcamHandlerProc::isHere()
{
    ///@todo test if this works in windows
    wxString cmd = wxT("./IsHereCmd '");

    const wxString cascade(m_FaceCascadeName.c_str(), wxConvUTF8);

    cmd << m_index << "' '" << cascade << "' '" << m_FaceSizeX << "' '" << m_FaceSizeY << "'";
    IsHereCmd::ReturnCodes code = (IsHereCmd::ReturnCodes)wxExecute(cmd, wxEXEC_SYNC);

    switch (code)
    {
        case IsHereCmd::HERE:
            return true;
        case IsHereCmd::AWAY:
            return false;
        case IsHereCmd::INVALID_CAMERA:
            throw InvalidCameraException();
        case IsHereCmd::INVALID_CASCADE:
            throw MissingCascadeFileException();
        case IsHereCmd::INVALID_FACEX:
        case IsHereCmd::INVALID_FACEY:
        case IsHereCmd::INVALID_INDEX:
        case IsHereCmd::INVALID_NB_ARGS:
        case IsHereCmd::OTHER_ERROR:
        default:
            assert(false);
            throw GenericPresenceHandlerException();
    }

    return false;
}
