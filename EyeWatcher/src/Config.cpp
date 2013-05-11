#include "Config.h"
#include "AbstractConfigImpl.h"
#include "boost/date_time/posix_time/posix_time.hpp"

///@todo: unnecessary level? merge this with presenter?
Config::Config(AbstractConfigImpl* impl) : m_Impl(impl)
{
    //ctor
    this->load();
}

Config::~Config()
{
    //dtor
}

const ConfigData& Config::getData() const
{
    return this->m_data;
}

void Config::load()
{
    ConfigData tempData =
    {
        boost::posix_time::duration_from_string(this->m_Impl->read("WorkLength",
            boost::posix_time::to_simple_string(ConfigData::default_WorkLength))),
        boost::posix_time::duration_from_string(this->m_Impl->read("PauseLength",
            boost::posix_time::to_simple_string(ConfigData::default_PauseLength))),
        boost::posix_time::duration_from_string(this->m_Impl->read("RemFreq",
            boost::posix_time::to_simple_string(ConfigData::default_RemFreq))),
        boost::posix_time::duration_from_string(this->m_Impl->read("CheckFreq",
            boost::posix_time::to_simple_string(ConfigData::default_CheckFreq))),
        (unsigned int)this->m_Impl->read("PauseTol", (long)ConfigData::default_PauseTol),
        this->m_Impl->read("Startup", ConfigData::default_Startup),
        this->m_Impl->read("SoundAlarm", ConfigData::default_SoundAlarm),
        this->m_Impl->read("PopupAlarm", ConfigData::default_PopupAlarm),
        this->m_Impl->read("EmailAlarm", ConfigData::default_EmailAlarm),
        this->m_Impl->read("EmailAddr", ConfigData::default_EmailAddr),
        (int)this->m_Impl->read("WebcamIndex", (long)ConfigData::default_WebcamIndex),
        (unsigned int)this->m_Impl->read("FaceSizeX", (long)ConfigData::default_FaceSizeX),
        (unsigned int)this->m_Impl->read("FaceSizeY", (long)ConfigData::default_FaceSizeY),
        this->m_Impl->read("CascadePath", ConfigData::default_CascadePath),
        this->m_Impl->read("SoundPath", ConfigData::default_SoundPath)
    };

    if (Config::validateData(tempData))
    {
        this->m_data = tempData;
    }
    else
    {
        throw InvalidConfigFileException();
    }
}

void Config::save(const ConfigData& data)
{
    if (Config::validateData(data))
    {
        this->m_data = data;
        this->write();
    }
    else
    {
        throw InvalidConfigDataException();
    }
}

void Config::write()
{
    this->m_Impl->write("Startup", this->m_data.startup);
    this->m_Impl->write("WorkLength", boost::posix_time::to_simple_string(this->m_data.workLength));
    this->m_Impl->write("PauseLength", boost::posix_time::to_simple_string(this->m_data.pauseLength));
    this->m_Impl->write("RemFreq", boost::posix_time::to_simple_string(this->m_data.remFreq));
    this->m_Impl->write("CheckFreq", boost::posix_time::to_simple_string(this->m_data.checkFreq));
    this->m_Impl->write("PauseTol", (long)this->m_data.pauseTol);
    this->m_Impl->write("SoundAlarm", this->m_data.soundAlarm);
    this->m_Impl->write("PopupAlarm", this->m_data.popupAlarm);
    this->m_Impl->write("EmailAlarm", this->m_data.emailAlarm);
    this->m_Impl->write("EmailAddr", this->m_data.emailAddr);
    this->m_Impl->write("WebcamIndex", (long)this->m_data.webcamIndex);
    this->m_Impl->write("FaceSizeX", (long)this->m_data.faceSizeX);
    this->m_Impl->write("FaceSizeY", (long)this->m_data.faceSizeY);
    this->m_Impl->write("CascadePath", this->m_data.cascadePath);
    this->m_Impl->write("SoundPath", this->m_data.soundPath);

    this->m_Impl->flush();
}

/// @todo: more specific errors?, correct cascadePath?
bool Config::validateData(const ConfigData& data)
{
    if (data.workLength.is_special() ||
        data.pauseLength.is_special() ||
        data.remFreq.is_special() ||
        data.checkFreq.is_special() ||
        data.workLength.total_seconds() <= 0 ||
        data.pauseLength.total_seconds() <= 0 ||
        data.remFreq.total_seconds() <= 0 ||
        data.checkFreq.total_seconds() <= 0 ||
        data.pauseTol < 0)
    {
        return false;
    }
    return true;
}
