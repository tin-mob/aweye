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


#ifndef SETTOPWINDOWSTUB_H
#define SETTOPWINDOWSTUB_H

#include "aweye/SetTopWindowInt.h"

namespace Aweye
{
class AbstractMainFrame;
class SetTopWindowStub : public SetTopWindowInt
{
    public:
        SetTopWindowStub() : m_Frame(nullptr){}
        virtual ~SetTopWindowStub() {}
        virtual void setTopWindow(AbstractMainFrame* f) {m_Frame = f;}

        AbstractMainFrame* m_Frame;
    protected:
    private:
};
}

#endif // SETTOPWINDOWSTUB_H
