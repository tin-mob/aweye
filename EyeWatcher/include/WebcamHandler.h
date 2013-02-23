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

/// @todo: check webcam light stay on until release...
class WebcamHandler : public AbstractPresenceHandler
{
    public:
        WebcamHandler(int index = 0, std::string faceCascadeName = "haarcascade_frontalface_alt.xml");
        ~WebcamHandler();
        void open();
        void release();
        bool isHere();
    protected:
    private:
        int m_index;
        cv::CascadeClassifier m_FaceCascade;
        cv::VideoCapture m_VideoCapture;
};

#endif // WEBCAMHANDLER_H
