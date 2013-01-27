#include "WebcamHandler.h"
#include <boost/filesystem.hpp>

/// @todo: catch this in view, file path cross-platform
WebcamHandler::WebcamHandler(std::string faceCascadeName) :
m_VideoCapture(0)
{
    //ctor
    namespace fs = boost::filesystem;
    fs::path p;
    p = fs::current_path();

    if( !this->m_FaceCascade.load( faceCascadeName ) ){
		throw MissingCascadeFileException();
	}

	if(!this->m_VideoCapture.isOpened()) { // check if we succeeded
		throw InvalidCameraException();
	}
}

WebcamHandler::~WebcamHandler()
{
    //dtor
}

/// @todo: face size (minSize last param)
bool WebcamHandler::isHere()
{
    cv::Mat frame;
    this->m_VideoCapture >> frame; // get a new frame from camera

	std::vector<cv::Rect> faces;
	cv::Mat frame_gray;

	cv::cvtColor( frame, frame_gray, CV_BGR2GRAY );
	cv::equalizeHist( frame_gray, frame_gray );

	//-- Detect faces
	this->m_FaceCascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );

    return !faces.empty();
}
