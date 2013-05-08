#ifndef OPTIONSDIALOGPRES_H
#define OPTIONSDIALOGPRES_H

class EWPresenter;
class ConfigData;
class OptionsDialogPres
{
    public:
        OptionsDialogPres(EWPresenter* presenter);
        virtual ~OptionsDialogPres();
        const ConfigData&  getData() const;
        bool saveData(const ConfigData& data);
    protected:
    private:
        EWPresenter* m_Presenter;
};

#endif // OPTIONSDIALOGPRES_H
