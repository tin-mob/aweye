/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "WebcamHandlerProc.h"
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
    this->m_FaceCascadeName = name;
}

void WebcamHandlerProc::setIndex(int index)
{
    this->m_index = index;
}

void WebcamHandlerProc::setFaceSize(unsigned int x, unsigned int y)
{
    this->m_FaceSizeX = x;
    this->m_FaceSizeY = y;
}

// IsHereCmd in same path than main executable...
bool WebcamHandlerProc::isHere()
{
    ///@todo: test if this works in windows
    wxString cmd = wxT("./IsHereCmd '");
    wxString cascade(this->m_FaceCascadeName.c_str(), wxConvUTF8);

    cmd << this->m_index << "' '" << cascade << "' '" << this->m_FaceSizeX << "' '" << this->m_FaceSizeY << "'";
    long ret = wxExecute(cmd, wxEXEC_SYNC);

    assert(ret != -1);
    return ret == 1;
}
