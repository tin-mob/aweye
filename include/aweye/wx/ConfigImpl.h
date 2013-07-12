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


#ifndef WXCONFIGIMPL_H
#define WXCONFIGIMPL_H

#include "aweye/AbstractConfigImpl.h"

class wxConfigBase;
namespace Aweye { namespace WX {

class ConfigImpl : public AbstractConfigImpl
{
    public:
        ConfigImpl(std::string configPath = "");
        virtual ~ConfigImpl();

        virtual std::string read(std::string key, std::string defaultValue) const;
        virtual long read(std::string key, long defaultValue) const;
        virtual bool read(std::string key, bool defaultValue) const;

        virtual void write(std::string key, std::string value);
        virtual void write(std::string key, long value);
        virtual void write(std::string key, bool value);

        virtual void flush();
    protected:
    private:
        wxConfigBase* m_Config;
};
}}

#endif // WXCONFIGIMPL_H
