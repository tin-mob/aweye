/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


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
