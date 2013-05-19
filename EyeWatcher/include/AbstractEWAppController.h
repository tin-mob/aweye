#ifndef ABSTRACTEWAPPCONTROLLER_H
#define ABSTRACTEWAPPCONTROLLER_H

class ConfigData;
class AbstractEWAppController
{
    public:
        AbstractEWAppController() {}
        virtual ~AbstractEWAppController() {}

        virtual bool saveConfig(const ConfigData& data) = 0;
        virtual const ConfigData& getConfigData() const = 0;
    protected:
    private:
};

#endif // ABSTRACTEWAPPCONTROLLER_H
