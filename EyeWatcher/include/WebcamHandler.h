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
        WebcamHandler(int index, std::string faceCascadeName,
                      int faceSizeX, int faceSizeY);
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
        int m_FaceSizeY;
        cv::CascadeClassifier m_FaceCascade;
};

#endif // WEBCAMHANDLER_H
