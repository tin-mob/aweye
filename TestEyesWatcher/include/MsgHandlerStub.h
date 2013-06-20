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


#ifndef MSGHANDLERSTUB_H
#define MSGHANDLERSTUB_H

#include "AbstractMsgHandler.h"
#include <string>

namespace EW
{
class MsgHandlerStub : public AbstractMsgHandler
{
    public:
        MsgHandlerStub() : m_LastError(""), m_LastAlert(""), m_LastSound("") {}
        virtual ~MsgHandlerStub() {}
        virtual void displayError(std::string msg) {m_LastError = msg;}
        virtual void displayAlert(std::string msg) {m_LastAlert = msg;}
        virtual void playSound(std::string msg) {m_LastSound = msg;}
        std::string m_LastError;
        std::string m_LastAlert;
        std::string m_LastSound;
    protected:
    private:
};
}

#endif // MSGHANDLERSTUB_H
