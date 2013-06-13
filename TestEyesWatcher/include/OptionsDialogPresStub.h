/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef OPTIONSDIALOGPRESSTUB_H
#define OPTIONSDIALOGPRESSTUB_H

#include "AbstractOptionsDialogPres.h"

class AbstractEWAppController;
class OptionsDialogPresStub : public AbstractOptionsDialogPres
{
    public:
        OptionsDialogPresStub(AbstractEWAppController& c) : m_Controller(&c) {}
        virtual ~OptionsDialogPresStub() {}

        virtual bool saveData(const ConfigData& m_Data) {return true;}
        virtual void init(AbstractOptionsDialog& dialog) {}

        AbstractEWAppController* m_Controller;
        ConfigData m_Data;
    protected:
    private:
};

#endif // OPTIONSDIALOGPRESSTUB_H
