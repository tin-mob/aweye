#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <string>
#include "boost/date_time/posix_time/posix_time_types.hpp"

struct ConfigData
{
    ConfigData(boost::posix_time::time_duration wl = default_WorkLength,
        boost::posix_time::time_duration pl = default_PauseLength,
        boost::posix_time::time_duration rf = default_RemFreq,
        boost::posix_time::time_duration cf = default_CheckFreq,
        unsigned int pt = default_PauseTol,
        bool sa = default_SoundAlarm,
        bool pa = default_PopupAlarm,
        bool tr = default_TrayIcon,
        int wi = default_WebcamIndex,
        unsigned int fx = default_FaceSizeX,
        unsigned int fy = default_FaceSizeY,
        std::string cp = default_CascadePath,
        std::string sp = default_SoundPath,
        boost::posix_time::time_duration lt = default_RunningLateThreshold);

    boost::posix_time::time_duration workLength;
    boost::posix_time::time_duration pauseLength;
    boost::posix_time::time_duration remFreq;
    boost::posix_time::time_duration checkFreq;
    unsigned int pauseTol;
    bool soundAlarm;
    bool popupAlarm;
    bool trayIcon;
    int webcamIndex;
    unsigned int faceSizeX;
    unsigned int faceSizeY;
    std::string cascadePath;
    std::string soundPath;
    boost::posix_time::time_duration runningLateThreshold;

    static const boost::posix_time::time_duration default_WorkLength;
    static const boost::posix_time::time_duration default_PauseLength;
    static const boost::posix_time::time_duration default_RemFreq;
    static const boost::posix_time::time_duration default_CheckFreq;
    static const unsigned int default_PauseTol;
    static const bool default_SoundAlarm;
    static const bool default_PopupAlarm;
    static const bool default_TrayIcon;
    static const int default_WebcamIndex;
    static const unsigned int default_FaceSizeX;
    static const unsigned int default_FaceSizeY;
    static const std::string default_CascadePath;
    static const std::string default_SoundPath;
    static const boost::posix_time::time_duration default_RunningLateThreshold;
}
;

#endif // CONFIGDATA_H
