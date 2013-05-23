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


#ifndef CONFIG_H
#define CONFIG_H

#include "BaseException.h"

#include "ConfigData.h"
#include "AbstractConfig.h"

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

class AbstractConfigImpl;
class Config : public AbstractConfig
{
    public:
        /// @todo: check config path...
        Config(AbstractConfigImpl* impl);
        virtual ~Config();

        const ConfigData& getData() const;

        void load();
        void save(const ConfigData& data);

        static bool validateData(const ConfigData& data);

    protected:
    private:
        void write();

        AbstractConfigImpl* m_Impl;
        ConfigData m_data;
};

#endif // CONFIG_H
