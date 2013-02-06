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
