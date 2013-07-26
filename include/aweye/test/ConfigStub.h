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


#ifndef CONFIGSTUB_H
#define CONFIGSTUB_H

#include "aweye/core/AbstractConfig.h"
#include "aweye/core/AbstractConfigImpl.h"
#include "aweye/core/AbstractUtils.h"
#include "aweye/core/BaseException.h"
#include "aweye/core/ConfigData.h"

namespace Aweye
{
class ConfigStub : public AbstractConfig
{
    public:
        ConfigStub(ConfigData data = ConfigData::getDefault()) : m_Impl(nullptr), m_Utils(nullptr), m_Fail(false),
            m_Invalid(false), m_Data(data) {}
        ConfigStub(AbstractConfigImpl& i, AbstractUtils& u, bool invalid = false) :
            m_Impl(&i), m_Utils(&u), m_Fail(false), m_Invalid(invalid), m_Data(ConfigData::getDefault()) {}
        virtual ~ConfigStub() {}
        virtual void load() {}
        virtual void save(const ConfigData& data)
        {
            if (m_Fail) { throw BaseException("Testing!"); }
            m_Data = data;
        }
        virtual const ConfigData& getData() const
        {
            return m_Data;
        }

        virtual bool hasInvalidData() const
        {
            return m_Invalid;
        }

        void notifyUpdate()
        {
            notify(&ConfigObserver::update, m_Data);
        }

        static ConfigData getTestData(std::string path = "")
        {
            return {
                    ConfigData::default_WorkLength + boost::posix_time::seconds(1),
                    ConfigData::default_PauseLength + boost::posix_time::seconds(1),
                    ConfigData::default_RemFreq + boost::posix_time::seconds(1),
                    ConfigData::default_CheckFreq + boost::posix_time::seconds(1),
                    ConfigData::default_PauseTol + 1,
                    ConfigData::default_WorkTol + 1,
                    !ConfigData::default_SoundAlarm,
                    !ConfigData::default_PopupAlarm,
                    !ConfigData::default_TrayIcon,
                    ConfigData::default_WebcamIndex + 1,
                    ConfigData::default_FaceSizeX + 1,
                    ConfigData::default_FaceSizeY + 1,
                    path + "test.cfg",
                    path + "test.wav",
                    ConfigData::default_CheckFreq + boost::posix_time::seconds(1),
                    !ConfigData::default_CummulPause
                };
        }

        AbstractConfigImpl* m_Impl;
        AbstractUtils* m_Utils;
        bool m_Fail;
        bool m_Invalid;
    protected:
    private:
        ConfigData m_Data;
};

class ConfigStubFail : public ConfigStub
{
    public :
        ConfigStubFail(AbstractConfigImpl& i, AbstractUtils& u) : ConfigStub(i, u, true){}
};
}

#endif // CONFIGSTUB_H
