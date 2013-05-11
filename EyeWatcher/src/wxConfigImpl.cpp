#include "wxConfigImpl.h"
#include <wx/config.h>

wxConfigImpl::wxConfigImpl() :m_Config(wxConfigBase::Get())
{
    //ctor
    wxString path = this->m_Config->GetPath();
}

wxConfigImpl::~wxConfigImpl()
{
    //dtor
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
