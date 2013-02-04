#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <string>

struct ConfigData
{
    unsigned int workLength;
    unsigned int pauseLength;
    unsigned int remFreq;
    unsigned int checkFreq;
    unsigned int pauseTol;
    bool startup;
    bool soundAlarm;
    bool popupAlarm;
    bool emailAlarm;
    std::string emailAddr;

    static const unsigned int default_WorkLength;
    static const unsigned int default_PauseLength;
    static const unsigned int default_RemFreq;
    static const unsigned int default_CheckFreq;
    static const unsigned int default_PauseTol;
    static const bool default_Startup;
    static const bool default_SoundAlarm;
    static const bool default_PopupAlarm;
    static const bool default_EmailAlarm;
    static const std::string default_EmailAddr;
};

#endif // CONFIGDATA_H
