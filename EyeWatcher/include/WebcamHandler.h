#ifndef WEBCAMHANDLER_H
#define WEBCAMHANDLER_H

#include "AbstractWebcamHandler.h"
#include "opencv2/opencv.hpp"
#include <stdexcept>

class MissingCascadeFileException : public std::logic_error
{
    public:
          MissingCascadeFileException() :  std::logic_error("Missing cascade file.") { }
};

class InvalidCameraException : public std::logic_error
{
    public:
          InvalidCameraException() :  std::logic_error("Camera is not working.") { }
};

class WebcamHandler : public AbstractWebcamHandler
{
    public:
        WebcamHandler(std::string faceCascadeName = "haarcascade_frontalface_alt.xml");
        ~WebcamHandler();
        bool isHere();
    protected:
    private:
        cv::CascadeClassifier m_FaceCascade;
        cv::VideoCapture m_VideoCapture;
};

#endif // WEBCAMHANDLER_H
