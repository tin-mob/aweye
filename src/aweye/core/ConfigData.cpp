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


#include "aweye/core/ConfigData.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

namespace Aweye {

const boost::posix_time::time_duration ConfigData::default_WorkLength(0,50,0,0);
const boost::posix_time::time_duration ConfigData::default_PauseLength(0,10,0,0);
const boost::posix_time::time_duration ConfigData::default_RemFreq(0,2,0,0);
const boost::posix_time::time_duration ConfigData::default_CheckFreq(0,0,30,0);
const unsigned int ConfigData::default_PauseTol = 1;
const unsigned int ConfigData::default_WorkTol = 2;
const bool ConfigData::default_SoundAlarm = false;
const bool ConfigData::default_PopupAlarm = true;
const bool ConfigData::default_TrayIcon = true;
const int ConfigData::default_WebcamIndex = 0;
const unsigned int ConfigData::default_FaceSizeX = 100;
const unsigned int ConfigData::default_FaceSizeY = 100;
const boost::posix_time::time_duration ConfigData::default_RunningLateThreshold(0,4,0,0);
const bool ConfigData::default_CummulPause = false;

// beware! you must append the data directory to it.
const std::string ConfigData::default_CascadePath = "cascades/haarcascade_frontalface_alt2.xml";
const std::string ConfigData::default_SoundPath = "beep-1.wav";

ConfigData::ConfigData(boost::posix_time::time_duration wl,
    boost::posix_time::time_duration pl, boost::posix_time::time_duration rf,
    boost::posix_time::time_duration cf, unsigned int pt, unsigned int wt,
    bool sa, bool pa, bool tr, int wi, unsigned int fx, unsigned int fy,
    std::string cp, std::string sp, boost::posix_time::time_duration lt, bool cup):
    workLength(wl), pauseLength(pl), remFreq(rf), checkFreq(cf),
    pauseTol(pt), workTol(wt), soundAlarm(sa), popupAlarm(pa), trayIcon(tr),
    webcamIndex(wi), faceSizeX(fx), faceSizeY(fy), cascadePath(cp),
    soundPath(sp), runningLateThreshold(lt), cummulPause(cup)
{
}

///@todo more robust path joining (+ path is already included in cp or sp)
ConfigData ConfigData::getDefault(std::string path, boost::posix_time::time_duration wl,
    boost::posix_time::time_duration pl, boost::posix_time::time_duration rf,
    boost::posix_time::time_duration cf, unsigned int pt, unsigned int wt,
    bool sa, bool pa, bool tr, int wi, unsigned int fx, unsigned int fy,
    std::string cp, std::string sp, boost::posix_time::time_duration lt, bool cup)
{
    return ConfigData(wl, pl, rf, cf, pt, wt, sa, pa, tr, wi, fx, fy, path + cp, path + sp, lt, cup);
}

bool ConfigData::operator==(const ConfigData& other) const
{
    return (workLength == other.workLength &&
            pauseLength == other.pauseLength &&
            remFreq == other.remFreq &&
            checkFreq == other.checkFreq &&
            pauseTol == other.pauseTol &&
            workTol == other.workTol &&
            soundAlarm == other.soundAlarm &&
            popupAlarm == other.popupAlarm &&
            trayIcon == other.trayIcon &&
            webcamIndex == other.webcamIndex &&
            faceSizeX == other.faceSizeX &&
            faceSizeY == other.faceSizeY &&
            cascadePath == other.cascadePath &&
            soundPath == other.soundPath &&
            runningLateThreshold == other.runningLateThreshold &&
            cummulPause == other.cummulPause
            );
}

std::ostream& operator<<(std::ostream& os, const ConfigData& cd)
{
    os << cd.workLength << "; " << cd.pauseLength << "; " << cd.remFreq << "; "
       << cd.checkFreq << "; " << cd.pauseTol << "; " << cd.workTol << "; "
       << cd.soundAlarm << "; " << cd.popupAlarm << "; " << cd.trayIcon << "; "
       << cd.webcamIndex << "; " << cd.faceSizeX << "; " << cd.faceSizeY << "; "
       << cd.cascadePath << "; " << cd.soundPath << "; "
       << cd.runningLateThreshold << "; " << cd.cummulPause;
    return os;
}
}
