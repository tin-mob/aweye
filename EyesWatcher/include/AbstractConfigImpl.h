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


#ifndef ABSTRACTCONFIGIMPL_H
#define ABSTRACTCONFIGIMPL_H

#include <string>
#include "BaseException.h"

class InvalidConfigFileException : public BaseException
{
    public:
          InvalidConfigFileException() :  BaseException("invalid config file.") { }
};

class InvalidConfigDataException : public BaseException
{
    public:
          InvalidConfigDataException() :  BaseException("invalid configuration data.") { }
};

class AbstractConfigImpl
{
    public:
        virtual ~AbstractConfigImpl() {}
        virtual std::string read(std::string key, std::string defaultValue) const = 0;
        virtual long read(std::string key, long defaultValue) const = 0;
        virtual bool read(std::string key, bool defaultValue) const = 0;

        virtual void write(std::string key, std::string value) = 0;
        virtual void write(std::string key, long value) = 0;
        virtual void write(std::string key, bool value) = 0;

        virtual void flush() = 0;

        virtual bool fileExists(std::string name) = 0;
    protected:
    private:
};


#endif // ABSTRACTCONFIGIMPL_H
