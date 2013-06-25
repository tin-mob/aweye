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


#ifndef WXCONFIGIMPL_H
#define WXCONFIGIMPL_H

#include "ew/AbstractConfigImpl.h"

class wxConfigBase;
namespace EW { namespace WX {

class wxConfigImpl : public AbstractConfigImpl
{
    public:
        wxConfigImpl(std::string configPath = "");
        virtual ~wxConfigImpl();

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
