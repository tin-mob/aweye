#ifndef WXCONFIGIMPL_H
#define WXCONFIGIMPL_H

#include "AbstractConfigImpl.h"

class wxConfigBase;
class wxConfigImpl : public AbstractConfigImpl
{
    public:
        wxConfigImpl();
        virtual ~wxConfigImpl();

        virtual std::string read(std::string key, std::string defaultValue) const;
        virtual long read(std::string key, long defaultValue) const;
        virtual bool read(std::string key, bool defaultValue) const;

        virtual void write(std::string key, std::string value);
        virtual void write(std::string key, long value);
        virtual void write(std::string key, bool value);

        virtual void flush();
    protected:
    private:
        wxConfigBase* m_Config;
};

#endif // WXCONFIGIMPL_H
