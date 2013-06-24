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


#ifndef WEBCAMHANDLER_H
#define WEBCAMHANDLER_H

#include "ew/AbstractPresenceHandler.h"

#include <functional>
#include <opencv2/opencv.hpp>

namespace EW {

class AbstractConfig;
class AbstractMsgHandler;
class WebcamHandler : public AbstractPresenceHandler
{
    public:
        WebcamHandler(int index, std::string faceCascadeName,
                      int faceSizeX, int faceSizeY);
        ~WebcamHandler();

        bool isHere();
        virtual void isHere(std::function<void (bool)> callBack);
        virtual void setCascade(std::string name);
        virtual void setIndex(int index);
        virtual void setFaceSize(unsigned int x, unsigned int y);
    protected:
    private:
        int m_index;
        std::string m_FaceCascadeName;
        int m_FaceSizeX;
        int m_FaceSizeY;
        cv::CascadeClassifier m_FaceCascade;
};
}

#endif // WEBCAMHANDLER_H
