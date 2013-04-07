#include "MsgHandler.h"
#include "wx_pch.h"

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
