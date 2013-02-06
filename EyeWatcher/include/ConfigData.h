#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <string>
#include "boost/date_time/posix_time/posix_time_types.hpp"

struct ConfigData
{
    boost::posix_time::time_duration workLength;
    boost::posix_time::time_duration pauseLength;
    boost::posix_time::time_duration remFreq;
    boost::posix_time::time_duration checkFreq;
    unsigned int pauseTol;
    bool startup;
    bool soundAlarm;
    bool popupAlarm;
    bool emailAlarm;
    std::string emailAddr;

    static const boost::posix_time::time_duration default_WorkLength;
    static const boost::posix_time::time_duration default_PauseLength;
    static const boost::posix_time::time_duration default_RemFreq;
    static const boost::posix_time::time_duration default_CheckFreq;
    static const unsigned int default_PauseTol;
    static const bool default_Startup;
    static const bool default_SoundAlarm;
    static const bool default_PopupAlarm;
    static const bool default_EmailAlarm;
    static const std::string default_EmailAddr;
};

#endif // CONFIGDATA_H
