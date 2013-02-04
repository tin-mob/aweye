#include "Config.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

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

const ConfigData& Config::getData() const
{
    return this->m_data;
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
        this->write();
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
    this->m_data.workLength = pt.get("WorkLength", ConfigData::default_WorkLength);
    this->m_data.pauseLength = pt.get("PauseLength", ConfigData::default_PauseLength);
    this->m_data.remFreq = pt.get("RemFreq", ConfigData::default_RemFreq);
    this->m_data.checkFreq = pt.get("CheckFreq", ConfigData::default_CheckFreq);
    this->m_data.pauseTol = pt.get("PauseTol", ConfigData::default_PauseTol);
    this->m_data.startup = pt.get("Startup", ConfigData::default_Startup);
    this->m_data.soundAlarm = pt.get("SoundAlarm", ConfigData::default_SoundAlarm);
    this->m_data.popupAlarm = pt.get("PopupAlarm", ConfigData::default_PopupAlarm);
    this->m_data.emailAlarm = pt.get("EmailAlarm", ConfigData::default_EmailAlarm);
    this->m_data.emailAddr = pt.get("EmailAddr", ConfigData::default_EmailAddr);
}

/// @todo: check if validation could be done
void Config::save(const ConfigData& data)
{
    this->m_data = data;

    this->write();
}

void Config::write()
{
    // Create an empty property tree object
    using boost::property_tree::ptree;
    ptree pt;

    // Put log filename in property tree
    pt.put("WorkLength", this->m_data.workLength);
    pt.put("PauseLength", this->m_data.pauseLength);
    pt.put("RemFreq", this->m_data.remFreq);
    pt.put("CheckFreq", this->m_data.checkFreq);
    pt.put("PauseTol", this->m_data.pauseTol);
    pt.put("Startup", this->m_data.startup);
    pt.put("SoundAlarm", this->m_data.soundAlarm);
    pt.put("PopupAlarm", this->m_data.popupAlarm);
    pt.put("EmailAlarm", this->m_data.emailAlarm);
    pt.put("EmailAddr", this->m_data.emailAddr);

    // Write the property tree to the XML file.
    write_json(this->m_filename, pt);
}
