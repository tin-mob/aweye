#include "ConfigData.h"

const boost::posix_time::time_duration ConfigData::default_WorkLength(0,50,0,0);
const boost::posix_time::time_duration ConfigData::default_PauseLength(0,10,0,0);
const boost::posix_time::time_duration ConfigData::default_RemFreq(0,2,0,0);
const boost::posix_time::time_duration ConfigData::default_CheckFreq(0,0,30,0);
const unsigned int ConfigData::default_PauseTol = 1;
const bool ConfigData::default_Startup = false;
const bool ConfigData::default_SoundAlarm = false;
const bool ConfigData::default_PopupAlarm = true;
const bool ConfigData::default_EmailAlarm = false;
const std::string ConfigData::default_EmailAddr = "";
const int ConfigData::default_WebcamIndex = 0;
const unsigned int ConfigData::default_FaceSizeX = 30;
const unsigned int ConfigData::default_FaceSizeY = 30;
const std::string ConfigData::default_CascadePath = "haarcascade_frontalface_alt.xml";

ConfigData::ConfigData(boost::posix_time::time_duration wl,
    boost::posix_time::time_duration pl, boost::posix_time::time_duration rf,
    boost::posix_time::time_duration cf, unsigned int pt, bool s,
    bool sa, bool pa, bool ea, std::string eaddr, int wi,
    unsigned int fx, unsigned int fy, std::string cp
    ):
    workLength(wl), pauseLength(pl), remFreq(rf), checkFreq(cf),
    pauseTol(pt), startup(s), soundAlarm(sa), popupAlarm(pa), emailAlarm(ea),
    emailAddr(eaddr), webcamIndex(wi), faceSizeX(fx), faceSizeY(fy), cascadePath(cp)
{
}
