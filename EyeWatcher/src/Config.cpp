#include "Config.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

const unsigned int Config::default_WorkLength = 50*60;
const unsigned int Config::default_PauseLength = 10*60;
const unsigned int Config::default_RemFreq = 2*60;
const bool Config::default_Startup = false;
const bool Config::default_SoundAlarm = false;
const bool Config::default_PopupAlarm = true;
const bool Config::default_EmailAlarm = false;
const unsigned int Config::default_CheckFreq = 30;
const std::string Config::default_EmailAddr = "";

/// @todo:handle everywhere for more robustness, throw in function declaration?
Config::Config(std::string filename)
{
    //ctor
    if (filename != "")
    {
        this->m_filename = filename;
        this->checkLoad();
    }
    else
    {
        throw InvalidConfigFileException();
    }
}

Config::~Config()
{
    //dtor
}

void Config::checkLoad()
{
    std::ifstream fin(this->m_filename.c_str());
    if (fin) {
        // file exists
        fin.close();
        this->load();
    } else {
        // file doesn't exist
        using boost::property_tree::ptree;
        ptree pt;
        this->generate(pt);
        this->save();
    }
}

void Config::load()
{
    // Create an empty property tree object
    using boost::property_tree::ptree;
    ptree pt;

    // Load the XML file into the property tree. If reading fails
    // (cannot open file, parse error), an exception is thrown.
    try {
        read_json(this->m_filename, pt);
    }
    catch (boost::property_tree::json_parser_error) {
        /// @todo: manage invalid file
    }
    this->generate(pt);
}

// Loads Config structure from the specified XML file
void Config::generate(boost::property_tree::ptree &pt)
{
    this->m_WorkLength = pt.get("WorkLength", Config::default_WorkLength);
    this->m_PauseLength = pt.get("PauseLength", Config::default_PauseLength);
    this->m_RemFreq = pt.get("RemFreq", Config::default_RemFreq);
    this->m_Startup = pt.get("Startup", Config::default_Startup);
    this->m_SoundAlarm = pt.get("SoundAlarm", Config::default_SoundAlarm);
    this->m_PopupAlarm = pt.get("PopupAlarm", Config::default_PopupAlarm);
    this->m_EmailAlarm = pt.get("EmailAlarm", Config::default_EmailAlarm);
    this->m_CheckFreq = pt.get("CheckFreq", Config::default_CheckFreq);
    this->m_EmailAddr = pt.get("EmailAddr", Config::default_EmailAddr);
}

void Config::save()
{
   // Create an empty property tree object
   using boost::property_tree::ptree;
   ptree pt;

   // Put log filename in property tree
   pt.put("WorkLength", this->m_WorkLength);
   pt.put("PauseLength", this->m_PauseLength);
   pt.put("RemFreq", this->m_RemFreq);
   pt.put("Startup", this->m_Startup);
   pt.put("SoundAlarm", this->m_SoundAlarm);
   pt.put("PopupAlarm", this->m_PopupAlarm);
   pt.put("EmailAlarm", this->m_EmailAlarm);
   pt.put("CheckFreq", this->m_CheckFreq);
   pt.put("EmailAddr", this->m_EmailAddr);

   // Write the property tree to the XML file.
   write_json(this->m_filename, pt);
}
