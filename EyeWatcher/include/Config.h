#ifndef CONFIG_H
#define CONFIG_H

#include <boost/property_tree/ptree_fwd.hpp>
#include <stdexcept>

#include "ConfigData.h"
#include "AbstractConfig.h"

class Config : public AbstractConfig
{
    public:
        /// @todo: check config path...
        Config(std::string filename = "EyeWatcher.cfg");
        virtual ~Config();

        const ConfigData& getData() const;

        void checkLoad();
        void save(const ConfigData& data);

    protected:
    private:
        void load();
        void generate(boost::property_tree::ptree &pt);
        void write();

        std::string m_filename;
        ConfigData m_data;
};

#endif // CONFIG_H
