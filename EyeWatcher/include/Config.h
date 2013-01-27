#ifndef CONFIG_H
#define CONFIG_H

#include <boost/property_tree/ptree_fwd.hpp>
#include <stdexcept>

class InvalidConfigFileException : public std::logic_error
{
    public:
          InvalidConfigFileException() :  std::logic_error("invalid config file.") { }
};

class Config
{
    public:
        /// @todo: check config path...
        Config(std::string filename = "EyeWatcher.cfg");
        virtual ~Config();

        void checkLoad();
        void save();

        // getter/setter
        unsigned int getWorkLength() { return m_WorkLength; }
        unsigned int getPauseLength() { return m_PauseLength; }
        unsigned int getRemFreq() { return m_RemFreq; }
        bool getStartup() { return m_Startup; }
        bool getSoundAlarm() { return m_SoundAlarm; }
        bool getPopupAlarm() { return m_PopupAlarm; }
        bool getEmailAlarm() { return m_EmailAlarm; }
        unsigned int getCheckFreq() { return m_CheckFreq; }
        std::string getEmailAddr() { return m_EmailAddr; }

        void setWorkLength(unsigned int val) { m_WorkLength = val; }
        void setPauseLength(unsigned int val) { m_PauseLength = val; }
        void setRemFreq(unsigned int val) { m_RemFreq = val; }
        void setStartup(bool val) { m_Startup = val; }
        void setSoundAlarm(bool val) { m_SoundAlarm = val; }
        void setPopupAlarm(bool val) { m_PopupAlarm = val; }
        void setEmailAlarm(bool val) { m_EmailAlarm = val; }
        void setCheckFreq(unsigned int val) { m_CheckFreq = val; }
        void setEmailAddr(std::string val) { m_EmailAddr = val; }

        static const unsigned int default_WorkLength;
        static const unsigned int default_PauseLength;
        static const unsigned int default_RemFreq;
        static const bool default_Startup;
        static const bool default_SoundAlarm;
        static const bool default_PopupAlarm;
        static const bool default_EmailAlarm;
        static const unsigned int default_CheckFreq;
        static const std::string default_EmailAddr;

    protected:
    private:
        void load();
        void generate(boost::property_tree::ptree &pt);

        unsigned int m_WorkLength;
        unsigned int m_PauseLength;
        unsigned int m_RemFreq;
        bool m_Startup;
        bool m_SoundAlarm;
        bool m_PopupAlarm;
        bool m_EmailAlarm;
        unsigned int m_CheckFreq;
        std::string m_EmailAddr;

        std::string m_filename;
};

#endif // CONFIG_H
