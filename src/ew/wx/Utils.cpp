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

#include "ew/wx/Utils.h"

#include <string>
#include <wx/filename.h>
#include <wx/stdpaths.h>

namespace EW { namespace WX {

Utils::Utils(std::string dataDir) : m_DataDir(dataDir)
{
    //ctor
}

Utils::~Utils()
{
    //dtor
}

bool Utils::fileExists(std::string name) const
{
    const wxFileName fileName(name);
    if(fileName.IsOk())
    {
        return wxFileName::FileExists(fileName.GetFullPath());
    }
    return false;
}

std::string Utils::getDataDir() const
{
    if (m_DataDir == "")
        return std::string(wxStandardPaths::Get().GetDataDir());
    else
        return m_DataDir;
}

}}
