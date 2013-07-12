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


#ifndef ABSTRACTPRESENCEHANDLER_H
#define ABSTRACTPRESENCEHANDLER_H

#include "aweye/BaseException.h"
#include "aweye/tr.h"

#include <functional>

namespace Aweye {

class GenericPresenceHandlerException : public BaseException
{
    public:
          GenericPresenceHandlerException() :  BaseException(tr("Error while establishing presence.")) { }
};

///@todo these are not generic
class MissingCascadeFileException : public BaseException
{
    public:
          MissingCascadeFileException() :  BaseException(tr("Cascade file not found.")) { }
};

class InvalidCameraException : public BaseException
{
    public:
          InvalidCameraException() :  BaseException(tr("Error using the camera.")) { }
};

// isHere takes a callback rather than returning to allow async execution
class AbstractPresenceHandler
{
    public:
        virtual ~AbstractPresenceHandler() {}
        virtual void isHere(std::function<void (bool)> callBack) = 0;

        ///@todo this is specific to webcam - create another interface someday
        virtual void setCascade(std::string name) = 0;
        virtual void setIndex(int index) = 0;
        virtual void setFaceSize(unsigned int x, unsigned int y) = 0;
    protected:
    private:
};
}

#endif // ABSTRACTPRESENCEHANDLER_H
