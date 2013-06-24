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


#include "ew/WebcamHandler.h"

#include <fstream>

namespace EW {

/// @note opencv 2.3.1 leaks in ishere (videocapture and mat not deleted)
/// options are either installing 2.4 from source, installing a new version
/// of os or put this in a separate process...
/// @note tried 2.4.5? and the camera is not released at the end...
/// so it is used for now in a throwaway subprocess (see main-Ishere.cpp)

WebcamHandler::WebcamHandler(int index, std::string faceCascadeName,
                             int faceSizeX, int faceSizeY) :
    m_index(index), m_FaceCascadeName(faceCascadeName),
    m_FaceSizeX(faceSizeX), m_FaceSizeY(faceSizeY)
{
    if( !m_FaceCascade.load(m_FaceCascadeName) ){
        throw MissingCascadeFileException();
    }
}

WebcamHandler::~WebcamHandler()
{
}

void WebcamHandler::setCascade(std::string name)
{
    if (name != m_FaceCascadeName)
    {
        if( !m_FaceCascade.load(name) ){
            throw MissingCascadeFileException();
        }
        m_FaceCascadeName = name;
    }
}

void WebcamHandler::setIndex(int index)
{
    m_index = index;
}

void WebcamHandler::setFaceSize(unsigned int x, unsigned int y)
{
    m_FaceSizeX = x;
    m_FaceSizeY = y;
}

bool WebcamHandler::isHere()
{
    cv::VideoCapture videoCapture(m_index);

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
	m_FaceCascade.detectMultiScale( frame_gray, faces,
        1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(m_FaceSizeX, m_FaceSizeY) );

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

void WebcamHandler::isHere(std::function<void (bool)> callBack)
{
    callBack(isHere());
}
}
