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
///@todo define strings keys somewhere

#include "ew/AbstractConfigImpl.h"
#include "ew/AbstractUtils.h"
#include "ew/Config.h"

#include <boost/date_time/posix_time/posix_time.hpp>

namespace EW {

Config::Config(AbstractConfigImpl& impl, AbstractUtils& utils) :
    m_Impl(impl), m_Utils(utils),  m_data(getLoadedData()),
    m_HasInvalidData(false)
{
    if (!validateData(m_data))
    {
        m_HasInvalidData = true;
    }
}

Config::~Config()
{
}

const ConfigData& Config::getData() const
{
    return m_data;
}

ConfigData Config::getLoadedData() const
{
    return {
        boost::posix_time::duration_from_string(m_Impl.read("WorkLength",
            boost::posix_time::to_simple_string(ConfigData::default_WorkLength))),
        boost::posix_time::duration_from_string(m_Impl.read("PauseLength",
            boost::posix_time::to_simple_string(ConfigData::default_PauseLength))),
        boost::posix_time::duration_from_string(m_Impl.read("RemFreq",
            boost::posix_time::to_simple_string(ConfigData::default_RemFreq))),
        boost::posix_time::duration_from_string(m_Impl.read("CheckFreq",
            boost::posix_time::to_simple_string(ConfigData::default_CheckFreq))),
        (unsigned int)m_Impl.read("PauseTol", (long)ConfigData::default_PauseTol),
        (unsigned int)m_Impl.read("WorkTol", (long)ConfigData::default_WorkTol),
        m_Impl.read("SoundAlarm", ConfigData::default_SoundAlarm),
        m_Impl.read("PopupAlarm", ConfigData::default_PopupAlarm),
        m_Impl.read("TrayIcon", ConfigData::default_TrayIcon),
        (int)m_Impl.read("WebcamIndex", (long)ConfigData::default_WebcamIndex),
        (unsigned int)m_Impl.read("FaceSizeX", (long)ConfigData::default_FaceSizeX),
        (unsigned int)m_Impl.read("FaceSizeY", (long)ConfigData::default_FaceSizeY),
        m_Impl.read("CascadePath", m_Utils.getDataPath(ConfigData::default_CascadePath)),
        m_Impl.read("SoundPath",  m_Utils.getDataPath(ConfigData::default_SoundPath)),
        boost::posix_time::duration_from_string(m_Impl.read("RunningLateThreshold",
            boost::posix_time::to_simple_string(ConfigData::default_RunningLateThreshold))),
        m_Impl.read("CummulPause", ConfigData::default_CummulPause)
    };
}

void Config::load()
{
    m_data = getLoadedData();
    if (!validateData(m_data))
    {
        m_HasInvalidData = true;
    }
}

void Config::save(const ConfigData& data)
{
    if (validateData(data))
    {
        m_HasInvalidData = false;
        m_data = data;
        write();

        notify(&ConfigObserver::update, m_data);
    }
    else
    {
        throw InvalidConfigDataException();
    }
}

void Config::write()
{
    m_Impl.write("WorkLength", boost::posix_time::to_simple_string(m_data.workLength));
    m_Impl.write("PauseLength", boost::posix_time::to_simple_string(m_data.pauseLength));
    m_Impl.write("RemFreq", boost::posix_time::to_simple_string(m_data.remFreq));
    m_Impl.write("CheckFreq", boost::posix_time::to_simple_string(m_data.checkFreq));
    m_Impl.write("PauseTol", (long)m_data.pauseTol);
    m_Impl.write("WorkTol", (long)m_data.workTol);
    m_Impl.write("SoundAlarm", m_data.soundAlarm);
    m_Impl.write("PopupAlarm", m_data.popupAlarm);
    m_Impl.write("TrayIcon", m_data.trayIcon);
    m_Impl.write("WebcamIndex", (long)m_data.webcamIndex);
    m_Impl.write("FaceSizeX", (long)m_data.faceSizeX);
    m_Impl.write("FaceSizeY", (long)m_data.faceSizeY);
    m_Impl.write("CascadePath", m_data.cascadePath);
    m_Impl.write("SoundPath", m_data.soundPath);
    m_Impl.write("RunningLateThreshold", boost::posix_time::to_simple_string(m_data.runningLateThreshold));
    m_Impl.write("CummulPause", m_data.cummulPause);

    m_Impl.flush();
}

bool Config::hasInvalidData() const
{
    return m_HasInvalidData;
}

/// @todo specific error messages
bool Config::validateData(const ConfigData& data) const
{
    if (data.workLength.is_special() ||
        data.pauseLength.is_special() ||
        data.remFreq.is_special() ||
        data.checkFreq.is_special() ||
        data.workLength.total_seconds() <= 0 ||
        data.pauseLength.total_seconds() <= 0 ||
        data.remFreq.total_seconds() <= 0 ||
        data.checkFreq.total_seconds() <= 0 ||
        data.runningLateThreshold.is_special() ||
        !m_Utils.fileExists(data.cascadePath) ||
        !m_Utils.fileExists(data.soundPath)
        )
    {
        return false;
    }
    return true;
}
}
