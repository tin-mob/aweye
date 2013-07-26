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
///@todo namespace test or something like that?


#ifndef CONFIGIMPLSTUB_H
#define CONFIGIMPLSTUB_H

#include "aweye/core/AbstractConfigImpl.h"

#include <map>
#include <string>

namespace Aweye
{
class ConfigImplStub : public AbstractConfigImpl
{
    public:
        ConfigImplStub(std::string path = "") : m_Path(path) {}
        virtual ~ConfigImplStub() {}

        virtual std::string read(std::string key, std::string defaultValue) const
        {
                std::map<std::string,std::string>::const_iterator itr = m_StringData.find(key);
                if (itr == m_StringData.end())
                {
                    return defaultValue;
                }
                return itr->second;
        }

        virtual long read(std::string key, long defaultValue) const
        {
                std::map<std::string,long >::const_iterator itr = m_LongData.find(key);
                if (itr == m_LongData.end())
                {
                    return defaultValue;
                }
                return itr->second;
        }

        virtual bool read(std::string key, bool defaultValue) const
        {
                std::map<std::string,bool>::const_iterator itr = m_BoolData.find(key);
                if (itr == m_BoolData.end())
                {
                    return defaultValue;
                }
                return itr->second;
        }

        virtual void write(std::string key, std::string value) {m_StringData[key] = value;}
        virtual void write(std::string key, long value) {m_LongData[key] = value;}
        virtual void write(std::string key, bool value) {m_BoolData[key] = value;}

        virtual void flush() {m_Flushed = true;}

        bool getFlushed() {bool t = m_Flushed; m_Flushed = false; return t;}

        std::map<std::string,std::string> m_StringData;
        std::map<std::string,long> m_LongData;
        std::map<std::string,bool> m_BoolData;

        std::string m_Path;

    protected:
    private:
        bool m_Flushed;
};
}

#endif // CONFIGIMPLSTUB_H
