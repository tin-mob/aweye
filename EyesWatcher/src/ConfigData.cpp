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


#include "ConfigData.h"
#include <iostream>

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
const std::string ConfigData::default_CascadePath = "haarcascade_frontalface_alt2.xml";
const std::string ConfigData::default_SoundPath = "beep-1.wav";
const boost::posix_time::time_duration ConfigData::default_RunningLateThreshold(0,4,0,0);

ConfigData::ConfigData(boost::posix_time::time_duration wl,
                       boost::posix_time::time_duration pl,
                       boost::posix_time::time_duration rf,
                       boost::posix_time::time_duration cf,
                       unsigned int pt, unsigned int wt,
                       bool sa, bool pa, bool tr, int wi,
                       unsigned int fx, unsigned int fy, std::string cp,
                       std::string sp, boost::posix_time::time_duration lt):
    workLength(wl), pauseLength(pl), remFreq(rf), checkFreq(cf),
    pauseTol(pt), workTol(wt), soundAlarm(sa), popupAlarm(pa), trayIcon(tr),
    webcamIndex(wi), faceSizeX(fx), faceSizeY(fy), cascadePath(cp),
    soundPath(sp), runningLateThreshold(lt)
{
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
            runningLateThreshold == other.runningLateThreshold
            );
}

std::ostream& operator<<(std::ostream& os, const ConfigData& cd)
{
    os << cd.workLength << "; " << cd.pauseLength << "; " << cd.remFreq << "; "
       << cd.checkFreq << "; " << cd.pauseTol << "; " << cd.workTol << "; "
       << cd.soundAlarm << "; " << cd.popupAlarm << "; " << cd.trayIcon << "; "
       << cd.webcamIndex << "; " << cd.faceSizeX << "; " << cd.faceSizeY << "; "
       << cd.cascadePath << "; " << cd.soundPath << "; " << cd.runningLateThreshold;
    return os;
}

