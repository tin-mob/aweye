#include "Config.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

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
        throw InvalidConfigFileException();
    }
    this->generate(pt);
}

// Loads Config structure from the specified XML file
void Config::generate(boost::property_tree::ptree &pt)
{
    ConfigData tempData =
    {
        pt.get("WorkLength", ConfigData::default_WorkLength),
        pt.get("PauseLength", ConfigData::default_PauseLength),
        pt.get("RemFreq", ConfigData::default_RemFreq),
        pt.get("CheckFreq", ConfigData::default_CheckFreq),
        pt.get("PauseTol", ConfigData::default_PauseTol),
        pt.get("Startup", ConfigData::default_Startup),
        pt.get("SoundAlarm", ConfigData::default_SoundAlarm),
        pt.get("PopupAlarm", ConfigData::default_PopupAlarm),
        pt.get("EmailAlarm", ConfigData::default_EmailAlarm),
        pt.get("EmailAddr", ConfigData::default_EmailAddr)
    };

    if (Config::validateData(tempData))
    {
        this->m_data = tempData;
    }
    else
    {
        throw InvalidConfigFileException();
    }
}

void Config::save(const ConfigData& data)
{
    if (Config::validateData(data))
    {
        this->m_data = data;
        this->write();
    }
    else
    {
        throw InvalidConfigDataException();
    }
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

/// @todo: more specific errors?
bool Config::validateData(const ConfigData& data)
{
    if (data.workLength.is_special() ||
        data.pauseLength.is_special() ||
        data.remFreq.is_special() ||
        data.checkFreq.is_special() ||
        data.workLength.total_seconds() <= 0 ||
        data.pauseLength.total_seconds() <= 0 ||
        data.remFreq.total_seconds() <= 0 ||
        data.checkFreq.total_seconds() <= 0 ||
        data.pauseTol < 0)
    {
        return false;
    }
    return true;
}
