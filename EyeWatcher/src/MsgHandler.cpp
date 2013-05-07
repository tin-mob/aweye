#include "MsgHandler.h"
#include "wx_pch.h"
#include <wx/sound.h>

MsgHandler::MsgHandler()
{
    //ctor
}

MsgHandler::~MsgHandler()
{
    //dtor
}

void MsgHandler::displayError(std::string msg)
{
    wxMessageDialog *errorDialog = new wxMessageDialog(NULL,
        wxString(msg.c_str(), wxConvUTF8), wxT("Error"), wxOK | wxICON_ERROR);
    errorDialog->ShowModal();
}

void MsgHandler::displayAlert(std::string msg)
{
    wxMessageDialog *errorDialog = new wxMessageDialog(NULL,
        wxString(msg.c_str(), wxConvUTF8), wxT("Alert"), wxOK | wxICON_EXCLAMATION);
    errorDialog->ShowModal();
}

void MsgHandler::playSound(std::string filename)
{
    ///@todo: investigate why this is not working (sample does not work either)
    wxSound sound(wxString(filename.c_str(), wxConvUTF8));
    bool played = sound.Play(wxSOUND_SYNC);
    assert(played);
}
