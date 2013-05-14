#include "WebcamHandlerProc.h"
#include <wx/stdpaths.h>

WebcamHandlerProc::WebcamHandlerProc(int index, std::string faceCascadeName,
                             int faceSizeX, int faceSizeY) :
    m_index(index), m_FaceCascadeName(faceCascadeName),
    m_FaceSizeX(faceSizeX), m_FaceSizeY(faceSizeY)
{
    //ctor
}

WebcamHandlerProc::~WebcamHandlerProc()
{
    //dtor
}

void WebcamHandlerProc::setCascade(std::string name)
{
    this->m_FaceCascadeName = name;
}

void WebcamHandlerProc::setIndex(int index)
{
    this->m_index = index;
}

void WebcamHandlerProc::setFaceSize(unsigned int x, unsigned int y)
{
    this->m_FaceSizeX = x;
    this->m_FaceSizeY = y;
}

// IsHereCmd in same path than main executable...
bool WebcamHandlerProc::isHere()
{
    ///@todo: test if this works in windows
    wxString cmd = wxT("./IsHereCmd '");
    wxString cascade(this->m_FaceCascadeName.c_str(), wxConvUTF8);

    cmd << this->m_index << "' '" << cascade << "' '" << this->m_FaceSizeX << "' '" << this->m_FaceSizeY << "'";
    long ret = wxExecute(cmd, wxEXEC_SYNC);

    assert(ret != -1);
    return ret == 1;
}
