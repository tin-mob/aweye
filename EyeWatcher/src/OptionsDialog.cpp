#include "wx_pch.h"
#include "OptionsDialog.h"
#include "EWPresenter.h"
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
const long OptionsDialog::ID_STATICTEXT5 = wxNewId();
const long OptionsDialog::ID_TEXTCTRL6 = wxNewId();
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

OptionsDialog::OptionsDialog(wxWindow* parent, EWPresenter* presenter, wxWindowID id) : m_Presenter(presenter)
{
	//(*Initialize(OptionsDialog)
	wxFlexGridSizer* wrkFlexGridSizer;
	wxFlexGridSizer* chkFlexGridSizer;
	wxFlexGridSizer* optionsFlexGridSizer;
	wxStaticBoxSizer* timeStaticBoxSizer;
	wxFlexGridSizer* zzzFlexGridSizer;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* remFlexGridSizer;
	wxStdDialogButtonSizer* optionsStdDialogButtonSizer;
	wxStaticBoxSizer* emailStaticBoxSizer;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	optionsFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
	timeStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Time (Seconds)"));
	wrkFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	workingLabel = new wxStaticText(this, ID_STATICTEXT1, _("Working Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wrkFlexGridSizer->Add(workingLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wrkFlexGridSizer->Add(22,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wrkTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	wrkFlexGridSizer->Add(wrkTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(wrkFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	zzzFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	zzzLabel = new wxStaticText(this, ID_STATICTEXT2, _("Pause Period"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	zzzFlexGridSizer->Add(zzzLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	zzzFlexGridSizer->Add(40,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	zzzTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	zzzFlexGridSizer->Add(zzzTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(zzzFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	remFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	remLabel = new wxStaticText(this, ID_STATICTEXT3, _("Reminder Frequency"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	remFlexGridSizer->Add(remLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	remTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	remFlexGridSizer->Add(remTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(remFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	chkFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	chkStaticText = new wxStaticText(this, ID_STATICTEXT4, _("Check Interval"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	chkFlexGridSizer->Add(chkStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkFlexGridSizer->Add(29,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	chkFlexGridSizer->Add(chkTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(chkFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	optionsFlexGridSizer->Add(timeStaticBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	tolStaticText = new wxStaticText(this, ID_STATICTEXT5, _("Pause Tolerance"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	tolStaticText->SetToolTip(_("Test"));
	BoxSizer1->Add(tolStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	tolTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	BoxSizer1->Add(tolTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	optionsFlexGridSizer->Add(BoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	startupCheckBox = new wxCheckBox(this, ID_CHECKBOX1, _("Start at PC Startup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	startupCheckBox->SetValue(false);
	optionsFlexGridSizer->Add(startupCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	soundCheckBox = new wxCheckBox(this, ID_CHECKBOX2, _("Sound Alarm"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	soundCheckBox->SetValue(false);
	optionsFlexGridSizer->Add(soundCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	popupCheckBox = new wxCheckBox(this, ID_CHECKBOX3, _("Popup Alarm"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	popupCheckBox->SetValue(false);
	optionsFlexGridSizer->Add(popupCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	emailStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Email"));
	emailCheckBox = new wxCheckBox(this, ID_CHECKBOX4, _("Email Alert When Pause Ends"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	emailCheckBox->SetValue(false);
	emailStaticBoxSizer->Add(emailCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	emailTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
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

	this->setFields();


	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OptionsDialog::OnOKClick);
}

OptionsDialog::~OptionsDialog()
{
	//(*Destroy(OptionsDialog)
	//*)
}

void OptionsDialog::setFields()
{
    const ConfigData& config = this->m_Presenter->getConfigData();
    this->startupCheckBox->SetValue(config.startup);
	this->soundCheckBox->SetValue(config.soundAlarm);
    this->tolTextCtrl->SetValue(wxString::Format(wxT("%i"), config.pauseTol));
    this->wrkTextCtrl->SetValue(wxString::Format(wxT("%li"), config.workLength.total_seconds()));
    this->popupCheckBox->SetValue(config.popupAlarm);
    this->emailTextCtrl->SetValue(wxString(config.emailAddr.c_str(), wxConvUTF8));
    this->zzzTextCtrl->SetValue(wxString::Format(wxT("%li"), config.pauseLength.total_seconds()));
    this->chkTextCtrl->SetValue(wxString::Format(wxT("%li"), config.checkFreq.total_seconds()));
    this->emailCheckBox->SetValue(config.emailAlarm);
    this->remTextCtrl->SetValue(wxString::Format(wxT("%li"), config.remFreq.total_seconds()));
}


/// @todo: validation
void OptionsDialog::OnOKClick(wxCommandEvent& event)
{

    ConfigData data ={
        boost::posix_time::seconds(wxAtoi(this->wrkTextCtrl->GetValue())),
        boost::posix_time::seconds(wxAtoi(this->zzzTextCtrl->GetValue())),
        boost::posix_time::seconds(wxAtoi(this->remTextCtrl->GetValue())),
        boost::posix_time::seconds(wxAtoi(this->chkTextCtrl->GetValue())),
        wxAtoi(this->tolTextCtrl->GetValue()),
        this->startupCheckBox->GetValue(),
        this->soundCheckBox->GetValue(),
        this->popupCheckBox->GetValue(),
        this->emailCheckBox->GetValue(),
        std::string(this->emailTextCtrl->GetValue().mb_str())
    };

    this->m_Presenter->saveConfig(data);

    Close();
}

