/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef CONFIGDIALOGSTUB_H
#define CONFIGDIALOGSTUB_H

#include "aweye/core/AbstractOptionsDialog.h"
#include "aweye/test/OptionsDialogPresStub.h"

namespace Aweye
{
class OptionsDialogStub : public AbstractOptionsDialog
{
    public:
        OptionsDialogStub(std::nullptr_t, OptionsDialogPresStub& pres) :
            m_Disabled(false), m_Presenter(&pres), m_Data(ConfigData::getDefault()) {}
        OptionsDialogStub() :
            m_Disabled(false), m_Presenter(nullptr), m_Data(ConfigData::getDefault()) {}
        virtual ~OptionsDialogStub() {}
        virtual ConfigData getData() const
        {
            return m_Data;
        }

        virtual void setData(const ConfigData& data)
        {
            m_Data = data;
        }
        virtual void disableTray()
        {
            m_Disabled = true;
        }
        int ShowModal()
        {
            m_Presenter->display();
            return IdOK;
        }

        bool m_Disabled;

        OptionsDialogPresStub* m_Presenter;
        static const int IdOK = 1;
    protected:
    private:
        ConfigData m_Data;
};
}

#endif // CONFIGDIALOGSTUB_H
