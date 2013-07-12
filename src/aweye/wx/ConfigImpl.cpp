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


#include "aweye/wx/ConfigImpl.h"

#include <wx/config.h>
#include <wx/filename.h>

namespace Aweye { namespace WX {

ConfigImpl::ConfigImpl(std::string configPath)
{
    if (configPath != "")
    {
        const wxFileName fileName(wxString(configPath.c_str(), wxConvUTF8));
        if(fileName.IsOk())
        {
            wxConfigBase::Set( new wxFileConfig(wxEmptyString, wxEmptyString,
                wxString(configPath.c_str(), wxConvUTF8), wxEmptyString,
                wxCONFIG_USE_LOCAL_FILE| wxCONFIG_USE_RELATIVE_PATH));
        }
        else
        {
            throw InvalidConfigFileException();
        }
    }
    m_Config = wxConfigBase::Get();
}

ConfigImpl::~ConfigImpl()
{
    // m_Config is managed by wx
}

std::string ConfigImpl::read(std::string key, std::string defaultValue) const
{
    return std::string(m_Config->Read(wxString(key.c_str(), wxConvUTF8),
                                wxString(defaultValue.c_str(), wxConvUTF8)).mb_str());
}

long ConfigImpl::read(std::string key, long defaultValue) const
{
    return m_Config->Read(wxString(key.c_str(), wxConvUTF8), defaultValue);
}

bool ConfigImpl::read(std::string key, bool defaultValue) const
{
    m_Config->Read(wxString(key.c_str(), wxConvUTF8),&defaultValue);
    return defaultValue;
}

void ConfigImpl::write(std::string key, std::string value)
{
    m_Config->Write(wxString(key.c_str(), wxConvUTF8),
                          wxString(value.c_str(), wxConvUTF8));
}

void ConfigImpl::write(std::string key, long value)
{
    m_Config->Write(wxString(key.c_str(), wxConvUTF8), value);
}

void ConfigImpl::write(std::string key, bool value)
{
    m_Config->Write(wxString(key.c_str(), wxConvUTF8), value);
}

void ConfigImpl::flush()
{
    m_Config->Flush();
}
}}
