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


#include "CMakeDefines.h"
#include "aweye/wx/Utils.h"

#include <string>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

namespace Aweye { namespace WX {

Utils::Utils()
{
    m_DataDirs.Add(wxT("data/"));

    #ifndef NDEBUG
    #ifdef AWEYE_SRC_BASE
        std::string path = AWEYE_SRC_BASE;
        path += "/data/";
        m_DataDirs.Add(path);
    #endif
    #endif
    #ifdef AWEYE_DATA_DIR
        m_DataDirs.Add(wxT(AWEYE_DATA_DIR));
    #endif
    wxFileName fn(wxStandardPaths::Get().GetExecutablePath());
    m_BinDirs.Add(fn.GetPath());
}

Utils::~Utils()
{
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

std::string Utils::getDataPath(std::string item) const
{
    return std::string(m_DataDirs.FindAbsoluteValidPath(item));
}

std::string Utils::getBinPath(std::string item) const
{
    return std::string(m_BinDirs.FindAbsoluteValidPath(item));
}

}}
