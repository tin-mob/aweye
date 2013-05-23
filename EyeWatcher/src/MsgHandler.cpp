#include "MsgHandler.h"
#include "wx_pch.h"
#include <wx/notifmsg.h>
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
    wxMessageDialog errorDialog(nullptr,
        wxString(msg.c_str(), wxConvUTF8), wxT("Error"), wxOK | wxICON_ERROR);
    errorDialog.ShowModal();
}

void MsgHandler::displayAlert(std::string msg)
{
    wxNotificationMessage notification(
        wxT("EyeWatcher"), wxString(msg.c_str(), wxConvUTF8), nullptr, wxICON_INFORMATION);
    notification.Show();
}

void MsgHandler::playSound(std::string filename)
{
    ///@todo: investigate why this is not working in linux
    /// (sample does not work either) ; works in windows
    wxSound sound(wxString(filename.c_str(), wxConvUTF8));
    sound.Play(wxSOUND_SYNC);
}
