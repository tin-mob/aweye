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


#ifndef MSGHANDLER_H
#define MSGHANDLER_H

#include "aweye/core/AbstractMsgHandler.h"

#include <string>

namespace Aweye { namespace WX {

class MsgHandler : public AbstractMsgHandler
{
    public:
        MsgHandler();
        virtual ~MsgHandler();
        virtual void displayError(std::string msg);
        virtual void displayAlert(std::string msg);
        virtual void playSound(std::string filename);
    protected:
    private:
};
}}

#endif // MSGHANDLER_H
