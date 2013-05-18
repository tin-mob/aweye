#ifndef OPTIONSDIALOGPRES_H
#define OPTIONSDIALOGPRES_H

#include "AbstractOptionsDialogPres.h"

class AbstractEWPresenter;
class ConfigData;
class OptionsDialogPres :  public AbstractOptionsDialogPres
{
    public:
        OptionsDialogPres(AbstractEWPresenter* presenter);
        virtual ~OptionsDialogPres();
        virtual const ConfigData&  getData() const;
        virtual bool saveData(const ConfigData& data);
    protected:
    private:
        AbstractEWPresenter* m_Presenter;
};

#endif // OPTIONSDIALOGPRES_H
