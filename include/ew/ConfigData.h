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


#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <iostream>
#include <string>

namespace EW {

struct ConfigData
{
    ConfigData(boost::posix_time::time_duration wl = default_WorkLength,
        boost::posix_time::time_duration pl = default_PauseLength,
        boost::posix_time::time_duration rf = default_RemFreq,
        boost::posix_time::time_duration cf = default_CheckFreq,
        unsigned int pt = default_PauseTol,
        unsigned int wt = default_WorkTol,
        bool sa = default_SoundAlarm,
        bool pa = default_PopupAlarm,
        bool tr = default_TrayIcon,
        int wi = default_WebcamIndex,
        unsigned int fx = default_FaceSizeX,
        unsigned int fy = default_FaceSizeY,
        std::string cp = default_CascadePath,
        std::string sp = default_SoundPath,
        boost::posix_time::time_duration lt = default_RunningLateThreshold,
        bool cup = default_CummulPause);

    bool operator==(const ConfigData& other) const;
    friend std::ostream& operator<<(std::ostream& os, const ConfigData& cd);

    boost::posix_time::time_duration workLength;
    boost::posix_time::time_duration pauseLength;
    boost::posix_time::time_duration remFreq;
    boost::posix_time::time_duration checkFreq;
    unsigned int pauseTol;
    unsigned int workTol;
    bool soundAlarm;
    bool popupAlarm;
    bool trayIcon;
    int webcamIndex;
    unsigned int faceSizeX;
    unsigned int faceSizeY;
    std::string cascadePath;
    std::string soundPath;
    boost::posix_time::time_duration runningLateThreshold;
    bool cummulPause;

    static const boost::posix_time::time_duration default_WorkLength;
    static const boost::posix_time::time_duration default_PauseLength;
    static const boost::posix_time::time_duration default_RemFreq;
    static const boost::posix_time::time_duration default_CheckFreq;
    static const unsigned int default_PauseTol;
    static const unsigned int default_WorkTol;
    static const bool default_SoundAlarm;
    static const bool default_PopupAlarm;
    static const bool default_TrayIcon;
    static const int default_WebcamIndex;
    static const unsigned int default_FaceSizeX;
    static const unsigned int default_FaceSizeY;
    static const std::string default_CascadePath;
    static const std::string default_SoundPath;
    static const boost::posix_time::time_duration default_RunningLateThreshold;
    static const bool default_CummulPause;
};
}

#endif // CONFIGDATA_H
