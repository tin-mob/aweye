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
            cascadePath(fcn), webcamIndex(i), faceSizeX(fx), faceSizeY(fy){}
        virtual ~PresenceHandlerStub() {}

        virtual bool isHere()
        {
            assert (!this->m_results.empty());
            bool result  = this->m_results.front();
            this->m_results.pop();
            return result;
        }

        virtual void pushResult(bool result)
        {
            this->m_results.push(result);
        }

        virtual void setCascade(std::string name) {cascadePath = name;}
        virtual void setIndex(int index) {webcamIndex = index;}
        virtual void setFaceSize(unsigned int x, unsigned int y) {faceSizeX = x; faceSizeY = y;}

        std::string cascadePath;
        int webcamIndex;
        unsigned int faceSizeX;
        unsigned int faceSizeY;

    protected:
    private:
        std::queue<bool> m_results;
};

#endif // PRESENCEHANDLERSTUB_H
