#ifndef CONFIGDIALOGSTUB_H
#define CONFIGDIALOGSTUB_H

#include "AbstractOptionsDialog.h"

class OptionsDialogStub : public AbstractOptionsDialog
{
    public:
        OptionsDialogStub() {}
        virtual ~OptionsDialogStub() {}
        virtual ConfigData getData() const
        {
            return m_Data;
        }

        virtual void setData(const ConfigData& data)
        {
            m_Data = data;
        }

    protected:
    private:
        ConfigData m_Data;
};

#endif // CONFIGDIALOGSTUB_H
