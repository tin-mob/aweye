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


#ifndef MSGHANDLERSTUB_H
#define MSGHANDLERSTUB_H


#include "AbstractMsgHandler.h"

#include <string>

class MsgHandlerStub : public AbstractMsgHandler
{
    public:
        MsgHandlerStub() : lastError(""), lastAlert(""), lastSound("") {}
        virtual ~MsgHandlerStub() {}
        virtual void displayError(std::string msg) {lastError = msg;}
        virtual void displayAlert(std::string msg) {lastAlert = msg;}
        virtual void playSound(std::string msg) {lastSound = msg;}
        std::string lastError;
        std::string lastAlert;
        std::string lastSound;
    protected:
    private:
};



#endif // MSGHANDLERSTUB_H
