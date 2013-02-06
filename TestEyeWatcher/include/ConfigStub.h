#ifndef CONFIGSTUB_H
#define CONFIGSTUB_H

#include "AbstractConfig.h"
#include "ConfigData.h"

class ConfigStub : public AbstractConfig
{
    public:
        ConfigStub(ConfigData data) : m_data(data) {}
        virtual ~ConfigStub() {}
        virtual void checkLoad() {}
        virtual void save(const ConfigData& data)
        {
            m_data = data;
        }
        virtual const ConfigData& getData() const
        {
            return m_data;
        }
    protected:
    private:
        ConfigData m_data;
};


#endif // CONFIGSTUB_H
