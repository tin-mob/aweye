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
#include "ew/WebcamHandlerProc.h"

#include <functional>
#include <sstream>

namespace EW {

WebcamHandlerProc::WebcamHandlerProc(AbstractUtils& utils,
    std::function<void (std::function<void (bool)>, std::string)> cmd,
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
///@todo test if this works in windows
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

    m_Cmd(callBack, s.str());
}
}
