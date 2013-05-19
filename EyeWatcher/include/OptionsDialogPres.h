#ifndef OPTIONSDIALOGPRES_H
#define OPTIONSDIALOGPRES_H

#include "AbstractOptionsDialogPres.h"

class AbstractEWAppController;
class ConfigData;
class OptionsDialogPres :  public AbstractOptionsDialogPres
{
    public:
        OptionsDialogPres(AbstractEWAppController* controller);
        virtual ~OptionsDialogPres();
        virtual const ConfigData&  getData() const;
        virtual bool saveData(const ConfigData& data);
    protected:
    private:
        AbstractEWAppController* m_Controller;
};

#endif // OPTIONSDIALOGPRES_H
