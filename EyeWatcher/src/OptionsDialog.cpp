#include "wx_pch.h"
#include "OptionsDialog.h"
#include "EyeWatcherInt.h"
#include "Config.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(OptionsDialog)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(OptionsDialog)
#include <wx/button.h>
//*)

//(*IdInit(OptionsDialog)
const long OptionsDialog::ID_STATICTEXT1 = wxNewId();
const long OptionsDialog::ID_TEXTCTRL2 = wxNewId();
const long OptionsDialog::ID_STATICTEXT2 = wxNewId();
const long OptionsDialog::ID_TEXTCTRL3 = wxNewId();
const long OptionsDialog::ID_STATICTEXT3 = wxNewId();
const long OptionsDialog::ID_TEXTCTRL4 = wxNewId();
const long OptionsDialog::ID_STATICTEXT4 = wxNewId();
const long OptionsDialog::ID_TEXTCTRL5 = wxNewId();
const long OptionsDialog::ID_CHECKBOX1 = wxNewId();
const long OptionsDialog::ID_CHECKBOX2 = wxNewId();
const long OptionsDialog::ID_CHECKBOX3 = wxNewId();
const long OptionsDialog::ID_CHECKBOX4 = wxNewId();
const long OptionsDialog::ID_TEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OptionsDialog,wxDialog)
	//(*EventTable(OptionsDialog)
	//*)
END_EVENT_TABLE()

OptionsDialog::OptionsDialog(wxWindow* parent,wxWindowID id)
{
    Config* config = EyeWatcherInt::Instance()->getConfig();
    config->checkLoad();

	//(*Initialize(OptionsDialog)
	wxBoxSizer* workingBoxSizer;
	wxFlexGridSizer* optionsFlexGridSizer;
	wxBoxSizer* checkBoxSizer;
	wxBoxSizer* reminderBoxSizer;
	wxStdDialogButtonSizer* optionsStdDialogButtonSizer;
	wxBoxSizer* pauseBoxSizer;
	wxStaticBoxSizer* emailStaticBoxSizer;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	optionsFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
	workingBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	workingLabel = new wxStaticText(this, ID_STATICTEXT1, _("Working Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	workingBoxSizer->Add(workingLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	workingTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL2, wxString::Format(wxT("%i"), config->getWorkLength()), wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, NULL), _T("ID_TEXTCTRL2"));
	workingBoxSizer->Add(workingTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	optionsFlexGridSizer->Add(workingBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	pauseBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	pauseLabel = new wxStaticText(this, ID_STATICTEXT2, _("Pause Period"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	pauseBoxSizer->Add(pauseLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pauseTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL3, wxString::Format(wxT("%i"), config->getPauseLength()), wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, NULL), _T("ID_TEXTCTRL3"));
	pauseBoxSizer->Add(pauseTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	optionsFlexGridSizer->Add(pauseBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	reminderBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	reminderLabel = new wxStaticText(this, ID_STATICTEXT3, _("Reminder Frequency"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	reminderBoxSizer->Add(reminderLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	reminderTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL4, wxString::Format(wxT("%i"), config->getRemFreq()), wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, NULL), _T("ID_TEXTCTRL4"));
	reminderBoxSizer->Add(reminderTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	optionsFlexGridSizer->Add(reminderBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	checkBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	checkStaticText = new wxStaticText(this, ID_STATICTEXT4, _("Check Interval"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	checkBoxSizer->Add(checkStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	checkTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL5, wxString::Format(wxT("%i"), config->getCheckFreq()), wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, NULL), _T("ID_TEXTCTRL5"));
	checkBoxSizer->Add(checkTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	optionsFlexGridSizer->Add(checkBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	startupCheckBox = new wxCheckBox(this, ID_CHECKBOX1, _("Start at PC Startup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	startupCheckBox->SetValue(config->getStartup());
	optionsFlexGridSizer->Add(startupCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	soundCheckBox = new wxCheckBox(this, ID_CHECKBOX2, _("Sound Alarm"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	soundCheckBox->SetValue(config->getSoundAlarm());
	optionsFlexGridSizer->Add(soundCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	popupCheckBox = new wxCheckBox(this, ID_CHECKBOX3, _("Popup Alarm"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	popupCheckBox->SetValue(config->getPopupAlarm());
	optionsFlexGridSizer->Add(popupCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	emailStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Email"));
	emailCheckBox = new wxCheckBox(this, ID_CHECKBOX4, _("Email Alert When Pause Ends"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	emailCheckBox->SetValue(config->getEmailAlarm());
	emailStaticBoxSizer->Add(emailCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	emailTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, wxString(config->getEmailAddr().c_str(),wxConvUTF8), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	emailStaticBoxSizer->Add(emailTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	optionsFlexGridSizer->Add(emailStaticBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	optionsStdDialogButtonSizer = new wxStdDialogButtonSizer();
	optionsStdDialogButtonSizer->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	optionsStdDialogButtonSizer->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	optionsStdDialogButtonSizer->Realize();
	optionsFlexGridSizer->Add(optionsStdDialogButtonSizer, 1, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5);
	SetSizer(optionsFlexGridSizer);
	optionsFlexGridSizer->Fit(this);
	optionsFlexGridSizer->SetSizeHints(this);
	//*)


	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OptionsDialog::OnOKClick);
}

OptionsDialog::~OptionsDialog()
{
	//(*Destroy(OptionsDialog)
	//*)
}

/// @todo: validation
void OptionsDialog::OnOKClick(wxCommandEvent& event)
{
    Config* config = EyeWatcherInt::Instance()->getConfig();
    config->setWorkLength(wxAtoi(this->workingTextCtrl->GetValue()));
    config->setPauseLength(wxAtoi(this->pauseTextCtrl->GetValue()));
    config->setRemFreq(wxAtoi(this->reminderTextCtrl->GetValue()));
    config->setStartup(this->startupCheckBox->GetValue());
    config->setSoundAlarm(this->soundCheckBox->GetValue());
    config->setPopupAlarm(this->popupCheckBox->GetValue());
    config->setEmailAlarm(this->emailCheckBox->GetValue());
    config->setCheckFreq(wxAtoi(this->checkTextCtrl->GetValue()));
    config->setEmailAddr(std::string(this->emailTextCtrl->GetValue().mb_str()));

    config->save();

    Close();
}

