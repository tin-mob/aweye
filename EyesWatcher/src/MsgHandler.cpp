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
        wxT("Eyes Watcher"), wxString(msg.c_str(), wxConvUTF8), nullptr, wxICON_INFORMATION);
    notification.Show();
}

void MsgHandler::playSound(std::string filename)
{
    ///@todo: investigate why this is not working in linux
    /// (sample does not work either) ; works in windows
    wxSound sound(wxString(filename.c_str(), wxConvUTF8));
    sound.Play(wxSOUND_SYNC);
}
