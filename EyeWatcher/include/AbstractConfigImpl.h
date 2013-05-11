#ifndef ABSTRACTCONFIGIMPL_H
#define ABSTRACTCONFIGIMPL_H

#include <string>

class AbstractConfigImpl
{
    public:
        virtual ~AbstractConfigImpl() {}
        virtual std::string read(std::string key, std::string defaultValue) const = 0;
        virtual long read(std::string key, long defaultValue) const = 0;
        virtual bool read(std::string key, bool defaultValue) const = 0;

        virtual void write(std::string key, std::string value) = 0;
        virtual void write(std::string key, long value) = 0;
        virtual void write(std::string key, bool value) = 0;

        virtual void flush() = 0;
    protected:
    private:
};


#endif // ABSTRACTCONFIGIMPL_H
