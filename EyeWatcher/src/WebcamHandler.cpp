#include "WebcamHandler.h"
#include "AbstractMsgHandler.h"
#include <boost/filesystem.hpp>

/// @todo: find a way to manage paths (Win/Linux)
WebcamHandler::WebcamHandler(int index, std::string faceCascadeName) :
    m_index(index)
{
    //ctor
    namespace fs = boost::filesystem;
    fs::path p;
    p = fs::current_path();

    if( !this->m_FaceCascade.load( faceCascadeName ) ){
		throw MissingCascadeFileException();
	}
}

WebcamHandler::~WebcamHandler()
{
    //dtor
}

/// @todo: face size (minSize last param)
/// @todo: test away state (seems to me there are false positives...)
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
	this->m_FaceCascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );

    return !faces.empty();
}
