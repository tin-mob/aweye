#ifndef ABSTRACTOPTIONSDIALOGPRES_H
#define ABSTRACTOPTIONSDIALOGPRES_H

class ConfigData;
class AbstractOptionsDialogPres
{
    public:
        virtual ~AbstractOptionsDialogPres() {}
        virtual const ConfigData&  getData() const = 0;
        virtual bool saveData(const ConfigData& data) = 0;
    protected:
    private:
};

#endif // ABSTRACTOPTIONSDIALOGPRES_H
