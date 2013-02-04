#ifndef ABSTRACTCONFIG_H
#define ABSTRACTCONFIG_H


#include <stdexcept>

class InvalidConfigFileException : public std::logic_error
{
    public:
          InvalidConfigFileException() :  std::logic_error("invalid config file.") { }
};

struct ConfigData;

class AbstractConfig
{
    public:
        virtual ~AbstractConfig() {}
        virtual void checkLoad() = 0;
        virtual void save(const ConfigData& data) = 0;
        virtual const ConfigData& getData() const = 0;

    protected:
    private:
};

#endif // ABSTRACTCONFIG_H
