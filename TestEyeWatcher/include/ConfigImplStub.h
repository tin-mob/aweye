#ifndef CONFIGIMPLSTUB_H
#define CONFIGIMPLSTUB_H

#include <map>
#include "AbstractConfigImpl.h"

class ConfigImplStub : public AbstractConfigImpl
{
    public:
        ConfigImplStub() {}
        virtual ~ConfigImplStub() {}

        virtual std::string read(std::string key, std::string defaultValue) const
        {
                std::map<std::string,std::string>::const_iterator itr = stringData.find(key);
                if (itr == stringData.end())
                {
                    return defaultValue;
                }
                return itr->second;
        }

        virtual long read(std::string key, long defaultValue) const
        {
                std::map<std::string,long >::const_iterator itr = longData.find(key);
                if (itr == longData.end())
                {
                    return defaultValue;
                }
                return itr->second;
        }

        virtual bool read(std::string key, bool defaultValue) const
        {
                std::map<std::string,bool>::const_iterator itr = boolData.find(key);
                if (itr == boolData.end())
                {
                    return defaultValue;
                }
                return itr->second;
        }

        virtual void write(std::string key, std::string value) {stringData[key] = value;}
        virtual void write(std::string key, long value) {longData[key] = value;}
        virtual void write(std::string key, bool value) {boolData[key] = value;}

        virtual void flush() {flushed = true;}

        bool getFlushed() {bool t = flushed; flushed = false; return t;}

        // I know, I can do better... but its quicker to code this way.
        std::map<std::string,std::string> stringData;
        std::map<std::string,long> longData;
        std::map<std::string,bool> boolData;

    protected:
    private:
        bool flushed;
};

#endif // CONFIGIMPLSTUB_H
