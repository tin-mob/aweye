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


#include "wxConfigImpl.h"
#include <wx/config.h>
#include <wx/filename.h>

wxConfigImpl::wxConfigImpl(std::string configPath)
{
    if (configPath != "")
    {
        wxFileName fileName(wxString(configPath.c_str(), wxConvUTF8));
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

wxConfigImpl::~wxConfigImpl()
{
    // m_Config is managed by wx
}

std::string wxConfigImpl::read(std::string key, std::string defaultValue) const
{
    return std::string(this->m_Config->Read(wxString(key.c_str(), wxConvUTF8),
                                wxString(defaultValue.c_str(), wxConvUTF8)).mb_str());
}

long wxConfigImpl::read(std::string key, long defaultValue) const
{
    return this->m_Config->Read(wxString(key.c_str(), wxConvUTF8), defaultValue);
}

bool wxConfigImpl::read(std::string key, bool defaultValue) const
{
    this->m_Config->Read(wxString(key.c_str(), wxConvUTF8),&defaultValue);
    return defaultValue;
}

void wxConfigImpl::write(std::string key, std::string value)
{
    this->m_Config->Write(wxString(key.c_str(), wxConvUTF8),
                          wxString(value.c_str(), wxConvUTF8));
}

void wxConfigImpl::write(std::string key, long value)
{
    this->m_Config->Write(wxString(key.c_str(), wxConvUTF8), value);
}

void wxConfigImpl::write(std::string key, bool value)
{
    this->m_Config->Write(wxString(key.c_str(), wxConvUTF8), value);
}

void wxConfigImpl::flush()
{
    this->m_Config->Flush();
}

bool wxConfigImpl::fileExists(std::string name)
{
    wxFileName fileName(wxString(name.c_str(), wxConvUTF8));
    if(fileName.IsOk())
    {
        return wxFileName::FileExists(fileName. GetFullPath());
    }
    return false;
}
