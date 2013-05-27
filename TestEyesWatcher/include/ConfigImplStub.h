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


#ifndef CONFIGIMPLSTUB_H
#define CONFIGIMPLSTUB_H

#include <map>
#include <string>
#include "AbstractConfigImpl.h"

class ConfigImplStub : public AbstractConfigImpl
{
    public:
        ConfigImplStub(std::string p = "") : path(p), failName("") {}
        virtual ~ConfigImplStub() {}

        virtual std::string read(std::string key, std::string defaultValue) const
        {
                std::map<std::string,std::string>::const_iterator itr = stringData.find(key);
                if (itr == stringData.end())
                {
                    return defaultValue;
                }
                return itr->second;
        }

        virtual long read(std::string key, long defaultValue) const
        {
                std::map<std::string,long >::const_iterator itr = longData.find(key);
                if (itr == longData.end())
                {
                    return defaultValue;
                }
                return itr->second;
        }

        virtual bool read(std::string key, bool defaultValue) const
        {
                std::map<std::string,bool>::const_iterator itr = boolData.find(key);
                if (itr == boolData.end())
                {
                    return defaultValue;
                }
                return itr->second;
        }

        virtual void write(std::string key, std::string value) {stringData[key] = value;}
        virtual void write(std::string key, long value) {longData[key] = value;}
        virtual void write(std::string key, bool value) {boolData[key] = value;}

        virtual void flush() {flushed = true;}

        bool getFlushed() {bool t = flushed; flushed = false; return t;}

        virtual bool fileExists(std::string name)
        {
            if (name == failName)
            {
                return false;
            }
            return true;
        }

        std::map<std::string,std::string> stringData;
        std::map<std::string,long> longData;
        std::map<std::string,bool> boolData;

        std::string path;
        std::string failName;

    protected:
    private:
        bool flushed;
};

#endif // CONFIGIMPLSTUB_H
