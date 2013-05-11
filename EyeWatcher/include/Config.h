#ifndef CONFIG_H
#define CONFIG_H

#include "BaseException.h"

#include "ConfigData.h"
#include "AbstractConfig.h"

class InvalidConfigFileException : public BaseException
{
    public:
          InvalidConfigFileException() :  BaseException("invalid config file.") { }
};

class InvalidConfigDataException : public BaseException
{
    public:
          InvalidConfigDataException() :  BaseException("invalid configuration data.") { }
};

class AbstractConfigImpl;
class Config : public AbstractConfig
{
    public:
        /// @todo: check config path...
        Config(AbstractConfigImpl* impl);
        virtual ~Config();

        const ConfigData& getData() const;

        void load();
        void save(const ConfigData& data);

        static bool validateData(const ConfigData& data);

    protected:
    private:
        void write();

        AbstractConfigImpl* m_Impl;
        ConfigData m_data;
};

#endif // CONFIG_H
