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
///@todo clean wx dependancy and test

#include "ew/IsHereCmd.h"
#include "ew/WebcamHandlerProc.h"
#include "ew/wx/IsHereProcess.h"

#include <functional>
#include <wx/filename.h>
#include <wx/stdpaths.h>

namespace EW {

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

///@todo copy pasted from wxConfigImpl
bool fileExists(wxString name)
{
    const wxFileName fileName(name);
    if(fileName.IsOk())
    {
        return wxFileName::FileExists(fileName. GetFullPath());
    }
    return false;
}

///@note IsHereCmd in same path than main executable,
///@todo test if this works in windows
void WebcamHandlerProc::isHere(std::function<void (bool)> callBack)
{
    // validate m_FaceCascadeName (and prevent injection)
    const wxString cascade(m_FaceCascadeName.c_str(), wxConvUTF8);
    if (!fileExists(cascade))
    {
        assert(false);
        throw MissingCascadeFileException();
    }
    wxString cmd = wxT("./IsHereCmd '");
    cmd << m_index << "' '" << cascade << "' '" << m_FaceSizeX << "' '" << m_FaceSizeY << "'";

    WX::IsHereProcess::run(callBack, cmd);
}
}
