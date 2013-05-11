#ifndef CONFIGSTUB_H
#define CONFIGSTUB_H

#include "AbstractConfig.h"
#include "ConfigData.h"
#include "BaseException.h"

class ConfigStub : public AbstractConfig
{
    public:
        ConfigStub(ConfigData data) : fail(false), m_data(data) {}
        virtual ~ConfigStub() {}
        virtual void load() {}
        virtual void save(const ConfigData& data)
        {
            if (fail) { throw BaseException("Testing!"); }
            m_data = data;
        }
        virtual const ConfigData& getData() const
        {
            return m_data;
        }
        bool fail;
    protected:
    private:
        ConfigData m_data;
};


#endif // CONFIGSTUB_H
