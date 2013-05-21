#include "ConfigData.h"
#include <iostream>

const boost::posix_time::time_duration ConfigData::default_WorkLength(0,50,0,0);
const boost::posix_time::time_duration ConfigData::default_PauseLength(0,10,0,0);
const boost::posix_time::time_duration ConfigData::default_RemFreq(0,2,0,0);
const boost::posix_time::time_duration ConfigData::default_CheckFreq(0,0,30,0);
const unsigned int ConfigData::default_PauseTol = 1;
const bool ConfigData::default_SoundAlarm = false;
const bool ConfigData::default_PopupAlarm = true;
const bool ConfigData::default_TrayIcon = true;
const int ConfigData::default_WebcamIndex = 0;
const unsigned int ConfigData::default_FaceSizeX = 100;
const unsigned int ConfigData::default_FaceSizeY = 100;
const std::string ConfigData::default_CascadePath = "haarcascade_frontalface_alt.xml";
const std::string ConfigData::default_SoundPath = "BEEPPURE.WAV";
const boost::posix_time::time_duration ConfigData::default_RunningLateThreshold(0,4,0,0);

ConfigData::ConfigData(boost::posix_time::time_duration wl,
                       boost::posix_time::time_duration pl,
                       boost::posix_time::time_duration rf,
                       boost::posix_time::time_duration cf,
                       unsigned int pt, bool sa, bool pa, bool tr, int wi,
                       unsigned int fx, unsigned int fy, std::string cp,
                       std::string sp, boost::posix_time::time_duration lt):
    workLength(wl), pauseLength(pl), remFreq(rf), checkFreq(cf),
    pauseTol(pt), soundAlarm(sa), popupAlarm(pa), trayIcon(tr),
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
       << cd.checkFreq << "; " << cd.pauseTol << "; " << cd.soundAlarm << "; "
       << cd.popupAlarm << "; " << cd.trayIcon << "; " << cd.webcamIndex << "; "
       << cd.faceSizeX << "; " << cd.faceSizeY << "; " << cd.cascadePath << "; "
       << cd.soundPath << "; " << cd.runningLateThreshold;
    return os;
}

