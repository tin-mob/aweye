#ifndef ABSTRACTOPTIONSDIALOG_H
#define ABSTRACTOPTIONSDIALOG_H

struct ConfigData;
class AbstractOptionsDialog
{
    public:
        AbstractOptionsDialog() {}
        virtual ConfigData getData() const = 0;
        virtual void setData(const ConfigData& data) = 0;

    protected:
    private:
};

#endif // ABSTRACTOPTIONSDIALOG_H
