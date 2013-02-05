#ifndef WEBCAMHANDLER_H
#define WEBCAMHANDLER_H

#include "AbstractPresenceHandler.h"
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
