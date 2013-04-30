#ifndef WEBCAMHANDLER_H
#define WEBCAMHANDLER_H

#include "AbstractPresenceHandler.h"
#include "opencv2/opencv.hpp"

#include "BaseException.h"

class MissingCascadeFileException : public BaseException
{
    public:
          MissingCascadeFileException() :  BaseException("Missing cascade file.") { }
};

class InvalidCameraException : public BaseException
{
    public:
          InvalidCameraException() :  BaseException("Camera is not working.") { }
};

class AbstractMsgHandler;
class AbstractConfig;
class WebcamHandler : public AbstractPresenceHandler
{
    public:
        /// @todo: find best minimum size
        WebcamHandler(int index = 0, std::string faceCascadeName = "haarcascade_frontalface_alt.xml",
                      int faceSizeX = 30, int facesizeY = 30);
        ~WebcamHandler();

        bool isHere();
        void setCascade(std::string name);
        void setIndex(int index);
        void setFaceSize(unsigned int x, unsigned int y);
    protected:
    private:
        int m_index;
        std::string m_FaceCascadeName;
        int m_FaceSizeX;
        int m_FacesizeY;
        cv::CascadeClassifier m_FaceCascade;
};

#endif // WEBCAMHANDLER_H
