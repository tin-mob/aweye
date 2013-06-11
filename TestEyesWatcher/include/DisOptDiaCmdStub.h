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


#ifndef DISOPTDIACMDSTUB_H
#define DISOPTDIACMDSTUB_H

#include "CommandStub.h"

class DisOptDiaCmdStub : public CommandStub
{
    public:
        DisOptDiaCmdStub(AbstractOptionsDialogPres* pres = nullptr, bool s = true) :
                         CommandStub(s), m_Presenter(pres) {}
        virtual ~DisOptDiaCmdStub() {}

        AbstractOptionsDialogPres* m_Presenter;
    protected:
    private:
};

class DisOptDiaCmdStubFail : public DisOptDiaCmdStub
{
    public:
        DisOptDiaCmdStubFail(AbstractOptionsDialogPres* pres = nullptr) :
                         DisOptDiaCmdStub(pres, false) {}
};

#endif // DISOPTDIACMDSTUB_H
