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


#ifndef CONFIGSTUB_H
#define CONFIGSTUB_H

#include "AbstractConfig.h"
#include "ConfigData.h"
#include "BaseException.h"
#include "AbstractConfigImpl.h"

class ConfigStub : public AbstractConfig
{
    public:
        ConfigStub(ConfigData data = ConfigData()) : fail(false), impl(nullptr), m_data(data) {}
        ConfigStub(AbstractConfigImpl* i) : fail(false), impl(i) {}
        virtual ~ConfigStub() {}
        virtual void load() {}
        virtual void save(const ConfigData& data)
        {
            if (fail) { throw BaseException("Testing!"); }
            m_data = data;
        }
        virtual const ConfigData& getData() const
        {
            return m_data;
        }
        bool fail;

        static ConfigData getTestData()
        {
            return {
                    ConfigData::default_WorkLength + boost::posix_time::seconds(1),
                    ConfigData::default_PauseLength + boost::posix_time::seconds(1),
                    ConfigData::default_RemFreq + boost::posix_time::seconds(1),
                    ConfigData::default_CheckFreq + boost::posix_time::seconds(1),
                    ConfigData::default_PauseTol + 1,
                    !ConfigData::default_SoundAlarm,
                    !ConfigData::default_PopupAlarm,
                    !ConfigData::default_TrayIcon,
                    ConfigData::default_WebcamIndex + 1,
                    ConfigData::default_FaceSizeX + 1,
                    ConfigData::default_FaceSizeY + 1,
                    "test.cfg",
                    "test.wav",
                    ConfigData::default_CheckFreq + boost::posix_time::seconds(1)
                };
        }

        AbstractConfigImpl* impl;
    protected:
    private:
        ConfigData m_data;
};


#endif // CONFIGSTUB_H
