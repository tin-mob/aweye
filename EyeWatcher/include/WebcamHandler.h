#ifndef WEBCAMHANDLER_H
#define WEBCAMHANDLER_H

#include "AbstractWebcamHandler.h"
#include "opencv2/opencv.hpp"

class WebcamHandler : public AbstractWebcamHandler
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
