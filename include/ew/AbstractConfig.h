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


#ifndef ABSTRACTCONFIG_H
#define ABSTRACTCONFIG_H

#include "ew/Subject.h"

namespace EW {

struct ConfigData;
class ConfigObserver;
class AbstractConfig : public Subject<ConfigObserver, const ConfigData&>
{
    public:
        virtual ~AbstractConfig() {}
        virtual void load() = 0;
        virtual void save(const ConfigData& data) = 0;
        virtual const ConfigData& getData() const = 0;
        virtual bool hasInvalidData() const = 0;

    protected:
    private:
};

class ConfigObserver
{
    public:
        ConfigObserver(AbstractConfig& config) : m_Config(config)
        {
            m_Config.attach(this);
        }
        virtual ~ConfigObserver()
        {
            m_Config.detach(this);
        }

        virtual void update(const ConfigData& data) = 0;
    private:
        AbstractConfig& m_Config;
};
}

#endif // ABSTRACTCONFIG_H
