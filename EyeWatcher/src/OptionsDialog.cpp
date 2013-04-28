#include "wx_pch.h"
#include "OptionsDialog.h"
#include "EWPresenter.h"
#include "AbstractOptionsDialog.h"
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
const long OptionsDialog::ID_SPINCTRL2 = wxNewId();
const long OptionsDialog::ID_SPINCTRL3 = wxNewId();
const long OptionsDialog::ID_STATICTEXT2 = wxNewId();
const long OptionsDialog::ID_SPINCTRL5 = wxNewId();
const long OptionsDialog::ID_SPINCTRL6 = wxNewId();
const long OptionsDialog::ID_STATICTEXT3 = wxNewId();
const long OptionsDialog::ID_SPINCTRL8 = wxNewId();
const long OptionsDialog::ID_SPINCTRL9 = wxNewId();
const long OptionsDialog::ID_STATICTEXT4 = wxNewId();
const long OptionsDialog::ID_SPINCTRL11 = wxNewId();
const long OptionsDialog::ID_SPINCTRL12 = wxNewId();
const long OptionsDialog::ID_STATICTEXT5 = wxNewId();
const long OptionsDialog::ID_SPINCTRL1 = wxNewId();
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
	timeStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Time (Minutes / Seconds)"));
	wrkFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	workingLabel = new wxStaticText(this, ID_STATICTEXT1, _("Working Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wrkFlexGridSizer->Add(workingLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wrkFlexGridSizer->Add(22,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wrkMinSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL2"));
	wrkMinSpinCtrl->SetValue(_T("0"));
	wrkFlexGridSizer->Add(wrkMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wrkSecSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL3"));
	wrkSecSpinCtrl->SetValue(_T("0"));
	wrkFlexGridSizer->Add(wrkSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(wrkFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	zzzFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	zzzLabel = new wxStaticText(this, ID_STATICTEXT2, _("Pause Period"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	zzzFlexGridSizer->Add(zzzLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	zzzFlexGridSizer->Add(40,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	zzzMinSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL5, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL5"));
	zzzMinSpinCtrl->SetValue(_T("0"));
	zzzFlexGridSizer->Add(zzzMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	zzzSecSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL6, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL6"));
	zzzSecSpinCtrl->SetValue(_T("0"));
	zzzFlexGridSizer->Add(zzzSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(zzzFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	remFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	remLabel = new wxStaticText(this, ID_STATICTEXT3, _("Reminder Frequency"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	remFlexGridSizer->Add(remLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	remMinSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL8, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL8"));
	remMinSpinCtrl->SetValue(_T("0"));
	remFlexGridSizer->Add(remMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	remSecSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL9, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL9"));
	remSecSpinCtrl->SetValue(_T("0"));
	remFlexGridSizer->Add(remSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(remFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	chkFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	chkStaticText = new wxStaticText(this, ID_STATICTEXT4, _("Check Interval"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	chkFlexGridSizer->Add(chkStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkFlexGridSizer->Add(29,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkMinSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL11, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL11"));
	chkMinSpinCtrl->SetValue(_T("0"));
	chkFlexGridSizer->Add(chkMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSecSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL12, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL12"));
	chkSecSpinCtrl->SetValue(_T("0"));
	chkFlexGridSizer->Add(chkSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(chkFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	optionsFlexGridSizer->Add(timeStaticBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	tolStaticText = new wxStaticText(this, ID_STATICTEXT5, _("Pause Tolerance"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	tolStaticText->SetToolTip(_("Test"));
	BoxSizer1->Add(tolStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	tolSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 10000, 0, _T("ID_SPINCTRL1"));
	tolSpinCtrl->SetValue(_T("0"));
	BoxSizer1->Add(tolSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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

	this->m_Presenter->loadConfig(this);

	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OptionsDialog::OnOKClick);
}

OptionsDialog::~OptionsDialog()
{
	//(*Destroy(OptionsDialog)
	//*)
}

ConfigData OptionsDialog::getData() const
{
    return {
        boost::posix_time::seconds(
            this->wrkMinSpinCtrl->GetValue() * 60 + this->wrkSecSpinCtrl->GetValue()),
        boost::posix_time::seconds(
            this->zzzMinSpinCtrl->GetValue() * 60 + this->zzzSecSpinCtrl->GetValue()),
        boost::posix_time::seconds(
            this->remMinSpinCtrl->GetValue() * 60 + this->remSecSpinCtrl->GetValue()),
        boost::posix_time::seconds(
            this->chkMinSpinCtrl->GetValue() * 60 + this->chkSecSpinCtrl->GetValue()),
        this->tolSpinCtrl->GetValue(),
        this->startupCheckBox->GetValue(),
        this->soundCheckBox->GetValue(),
        this->popupCheckBox->GetValue(),
        this->emailCheckBox->GetValue(),
        std::string(this->emailTextCtrl->GetValue().mb_str())
    };
}

void OptionsDialog::setData(const ConfigData& data)
{
    this->startupCheckBox->SetValue(data.startup);
	this->soundCheckBox->SetValue(data.soundAlarm);
    this->tolSpinCtrl->SetValue(data.pauseTol);
    this->wrkMinSpinCtrl->SetValue(data.workLength.total_seconds() / 60);
    this->wrkSecSpinCtrl->SetValue(data.workLength.seconds());
    this->popupCheckBox->SetValue(data.popupAlarm);
    this->emailTextCtrl->SetValue(wxString(data.emailAddr.c_str(), wxConvUTF8));
    this->zzzMinSpinCtrl->SetValue(data.pauseLength.total_seconds() / 60);
    this->zzzSecSpinCtrl->SetValue(data.pauseLength.seconds());
    this->chkMinSpinCtrl->SetValue(data.checkFreq.total_seconds() / 60);
    this->chkSecSpinCtrl->SetValue(data.checkFreq.seconds());
    this->emailCheckBox->SetValue(data.emailAlarm);
    this->remMinSpinCtrl->SetValue(data.remFreq.total_seconds() / 60);
    this->remSecSpinCtrl->SetValue(data.remFreq.seconds());
}

void OptionsDialog::OnOKClick(wxCommandEvent& event)
{
    if (this->m_Presenter->saveConfig(this))
    {
        Close();
    }
}

