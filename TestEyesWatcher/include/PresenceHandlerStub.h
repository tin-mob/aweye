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


#ifndef PRESENCEHANDLERSTUB_H
#define PRESENCEHANDLERSTUB_H

#include "AbstractPresenceHandler.h"
#include "BaseException.h"

#include <queue>
#include <assert.h>

class PresenceHandlerStub : public AbstractPresenceHandler
{
    public:
        PresenceHandlerStub(int i = 1001, std::string fcn = "", int fx = 1010, int fy = 1011) :
            m_CascadePath(fcn), m_WebcamIndex(i), m_FaceSizeX(fx), m_FaceSizeY(fy){}
        virtual ~PresenceHandlerStub() {}

        virtual bool isHere()
        {
            assert (!m_Results.empty());
            bool result  = m_Results.front();
            m_Results.pop();
            return result;
        }

        virtual void pushResult(bool result)
        {
            m_Results.push(result);
        }

        virtual void setCascade(std::string name) {m_CascadePath = name;}
        virtual void setIndex(int index) {m_WebcamIndex = index;}
        virtual void setFaceSize(unsigned int x, unsigned int y) {m_FaceSizeX = x; m_FaceSizeY = y;}

        std::string m_CascadePath;
        int m_WebcamIndex;
        unsigned int m_FaceSizeX;
        unsigned int m_FaceSizeY;

    protected:
    private:
        std::queue<bool> m_Results;
};

#endif // PRESENCEHANDLERSTUB_H
