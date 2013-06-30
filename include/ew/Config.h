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


#ifndef CONFIG_H
#define CONFIG_H

#include "ew/AbstractConfig.h"
#include "ew/ConfigData.h"

namespace EW {

class AbstractConfigImpl;
class AbstractUtils;
class Config : public AbstractConfig
{
    public:
        Config(AbstractConfigImpl& impl, AbstractUtils& utils);
        virtual ~Config();

        virtual void load();
        virtual void save(const ConfigData& data);
        virtual const ConfigData& getData() const;
        virtual bool hasInvalidData() const;

        bool validateData(const ConfigData& data) const;
    protected:
    private:
        void write();
        ConfigData getLoadedData() const;

        AbstractConfigImpl& m_Impl;
        AbstractUtils& m_Utils;
        ConfigData m_data;
        bool m_HasInvalidData;
};
}

#endif // CONFIG_H
