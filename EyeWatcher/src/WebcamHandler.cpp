#include "WebcamHandler.h"
#include <boost/filesystem.hpp>

#include <fstream>

/// @todo: opencv 2.3.1 leaks in ishere (videocapture and mat not deleted)
/// options are either installing 2.4 from source, installing a new version
/// of os or put this in a separate process...

/// @todo: find a way to manage paths (Win/Linux)
WebcamHandler::WebcamHandler(int index, std::string faceCascadeName,
                             int faceSizeX, int faceSizeY) :
    m_index(index), m_FaceCascadeName(faceCascadeName),
    m_FaceSizeX(faceSizeX), m_FaceSizeY(faceSizeY)
{
    if( !this->m_FaceCascade.load(m_FaceCascadeName) ){
        throw MissingCascadeFileException();
    }
}

WebcamHandler::~WebcamHandler()
{
}

void WebcamHandler::setCascade(std::string name)
{
    if (name != this->m_FaceCascadeName)
    {
        if( !this->m_FaceCascade.load(name) ){
            throw MissingCascadeFileException();
        }
        this->m_FaceCascadeName = name;
    }
}

void WebcamHandler::setIndex(int index)
{
    this->m_index = index;
}

void WebcamHandler::setFaceSize(unsigned int x, unsigned int y)
{
    this->m_FaceSizeX = x;
    this->m_FaceSizeY = y;
}

bool WebcamHandler::isHere()
{
    cv::VideoCapture videoCapture(this->m_index);

    if(!videoCapture.isOpened()) { // check if we have a camera
		throw InvalidCameraException();
	}
    cv::Mat frame;
    videoCapture >> frame; // get a new frame from camera

	std::vector<cv::Rect> faces;
	cv::Mat frame_gray;

	cv::cvtColor( frame, frame_gray, CV_BGR2GRAY );
	cv::equalizeHist( frame_gray, frame_gray );

	//-- Detect faces
	this->m_FaceCascade.detectMultiScale( frame_gray, faces,
        1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(this->m_FaceSizeX, this->m_FaceSizeY) );

    // kept for debugging purposes
    /*
    std::ofstream myfile;
    myfile.open ("log.txt", std::ios::app);
    for( unsigned int i = 0; i < faces.size(); i++ ) {
        myfile << faces[0].width << "; " << faces[0].height << "\n";
    }
    myfile.close();*/

    return !faces.empty();
}
