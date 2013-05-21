#ifndef EWAPPCONTROLLERSTUB_H
#define EWAPPCONTROLLERSTUB_H

#include "AbstractEWAppController.h"
#include "ConfigData.h"

class EWAppControllerStub : public AbstractEWAppController
{
    public:
        EWAppControllerStub() : displayedDialog(false) {}
        virtual ~EWAppControllerStub() {}

        virtual bool saveConfig(const ConfigData& d) {data = d; return true;}
        virtual const ConfigData& getConfigData() const {return data;}
        virtual void displayOptionsDialog() {displayedDialog = true;}

        bool checkDisplayedDialog() {bool temp = displayedDialog; displayedDialog = false; return temp;}

        ConfigData data;
    protected:
    private:
        bool displayedDialog;
};

#endif // EWAPPCONTROLLERSTUB_H
