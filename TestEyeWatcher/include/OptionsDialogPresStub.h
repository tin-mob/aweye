#ifndef OPTIONSDIALOGPRESSTUB_H
#define OPTIONSDIALOGPRESSTUB_H

#include "AbstractOptionsDialogPres.h"

class OptionsDialogPresStub : public AbstractOptionsDialogPres
{
    public:
        OptionsDialogPresStub(AbstractEWAppController* c) : controller(c) {}
        virtual ~OptionsDialogPresStub() {}

        virtual const ConfigData&  getData() const {return data;}
        virtual bool saveData(const ConfigData& data) {return true;}

        AbstractEWAppController* controller;
        ConfigData data;
    protected:
    private:
};

#endif // OPTIONSDIALOGPRESSTUB_H
