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


#ifndef ABSTRACTOPTIONSDIALOGPRES_H
#define ABSTRACTOPTIONSDIALOGPRES_H

namespace Aweye {

class AbstractOptionsDialog;
struct ConfigData;
class AbstractOptionsDialogPres
{
    public:
        virtual ~AbstractOptionsDialogPres() {}
        virtual bool saveData(const ConfigData& data) = 0;
        virtual void init(AbstractOptionsDialog& dialog) = 0;
    protected:
    private:
};
}

#endif // ABSTRACTOPTIONSDIALOGPRES_H
