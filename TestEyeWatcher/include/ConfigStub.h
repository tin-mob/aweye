#ifndef CONFIGSTUB_H
#define CONFIGSTUB_H

#include "AbstractConfig.h"
#include "ConfigData.h"
#include "BaseException.h"

class ConfigStub : public AbstractConfig
{
    public:
        ConfigStub(ConfigData data) : fail(false), m_data(data) {}
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
    protected:
    private:
        ConfigData m_data;
};


#endif // CONFIGSTUB_H
