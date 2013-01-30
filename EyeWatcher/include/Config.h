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
        unsigned int getWorkLength() const { return m_WorkLength; }
        unsigned int getPauseLength() const { return m_PauseLength; }
        unsigned int getRemFreq() const { return m_RemFreq; }
        unsigned int getCheckFreq() const { return m_CheckFreq; }
        unsigned int getPauseTol() const { return m_PauseTol; }
        bool getStartup() const { return m_Startup; }
        bool getSoundAlarm() const { return m_SoundAlarm; }
        bool getPopupAlarm() const { return m_PopupAlarm; }
        bool getEmailAlarm() const { return m_EmailAlarm; }
        std::string getEmailAddr() const { return m_EmailAddr; }

        void setWorkLength(unsigned int val) { m_WorkLength = val; }
        void setPauseLength(unsigned int val) { m_PauseLength = val; }
        void setRemFreq(unsigned int val) { m_RemFreq = val; }
        void setCheckFreq(unsigned int val) { m_CheckFreq = val; }
        void setPauseTol(unsigned int val) { m_PauseTol = val; }
        void setStartup(bool val) { m_Startup = val; }
        void setSoundAlarm(bool val) { m_SoundAlarm = val; }
        void setPopupAlarm(bool val) { m_PopupAlarm = val; }
        void setEmailAlarm(bool val) { m_EmailAlarm = val; }
        void setEmailAddr(std::string val) { m_EmailAddr = val; }

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

    protected:
    private:
        void load();
        void generate(boost::property_tree::ptree &pt);

        unsigned int m_WorkLength;
        unsigned int m_PauseLength;
        unsigned int m_RemFreq;
        unsigned int m_CheckFreq;
        unsigned int m_PauseTol;
        bool m_Startup;
        bool m_SoundAlarm;
        bool m_PopupAlarm;
        bool m_EmailAlarm;
        std::string m_EmailAddr;

        std::string m_filename;
};

#endif // CONFIG_H
