#include "wx_pch.h"
#include "OptionsDialog.h"
#include "EWPresenter.h"
#include "AbstractOptionsDialog.h"
#include "ConfigData.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(OptionsDialog)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(OptionsDialog)
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
const long OptionsDialog::ID_CHECKBOX1 = wxNewId();
const long OptionsDialog::ID_CHECKBOX2 = wxNewId();
const long OptionsDialog::ID_CHECKBOX3 = wxNewId();
const long OptionsDialog::ID_CHECKBOX4 = wxNewId();
const long OptionsDialog::ID_BUTTON1 = wxNewId();
const long OptionsDialog::ID_TEXTCTRL1 = wxNewId();
const long OptionsDialog::ID_PANEL1 = wxNewId();
const long OptionsDialog::ID_STATICTEXT6 = wxNewId();
const long OptionsDialog::ID_SPINCTRL4 = wxNewId();
const long OptionsDialog::ID_SPINCTRL7 = wxNewId();
const long OptionsDialog::ID_STATICTEXT5 = wxNewId();
const long OptionsDialog::ID_SPINCTRL1 = wxNewId();
const long OptionsDialog::ID_STATICTEXT8 = wxNewId();
const long OptionsDialog::ID_SPINCTRL10 = wxNewId();
const long OptionsDialog::ID_STATICTEXT7 = wxNewId();
const long OptionsDialog::ID_CUSTOM1 = wxNewId();
const long OptionsDialog::ID_STATICTEXT9 = wxNewId();
const long OptionsDialog::ID_CUSTOM2 = wxNewId();
const long OptionsDialog::ID_PANEL2 = wxNewId();
const long OptionsDialog::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OptionsDialog,wxDialog)
	//(*EventTable(OptionsDialog)
	//*)
END_EVENT_TABLE()

OptionsDialog::OptionsDialog(wxWindow* parent, EWPresenter* presenter, wxWindowID id) : m_Presenter(presenter)
{
	//(*Initialize(OptionsDialog)
	wxFlexGridSizer* wrkFlexGridSizer;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* faceSizeFlexGridSizer;
	wxFlexGridSizer* tolFlexGridSizer;
	wxFlexGridSizer* chkFlexGridSizer;
	wxFlexGridSizer* cascadeFlexGridSizer;
	wxFlexGridSizer* soundLocFlexGridSizer;
	wxFlexGridSizer* optionsFlexGridSizer;
	wxFlexGridSizer* indexFlexGridSizer;
	wxStaticBoxSizer* timeStaticBoxSizer;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* zzzFlexGridSizer;
	wxFlexGridSizer* generalFlexGridSizer;
	wxFlexGridSizer* remFlexGridSizer;
	wxStdDialogButtonSizer* optionsStdDialogButtonSizer;
	wxFlexGridSizer* advancedFlexGridSizer;
	wxStaticBoxSizer* emailStaticBoxSizer;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	optionsFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
	optionsNotebook = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
	GeneralPanel = new wxPanel(optionsNotebook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	generalFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
	generalFlexGridSizer->AddGrowableCol(1);
	timeStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, GeneralPanel, _("Time (Minutes / Seconds)"));
	wrkFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	workingLabel = new wxStaticText(GeneralPanel, ID_STATICTEXT1, _("Working Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wrkFlexGridSizer->Add(workingLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wrkFlexGridSizer->Add(22,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wrkMinSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL2"));
	wrkMinSpinCtrl->SetValue(_T("0"));
	wrkFlexGridSizer->Add(wrkMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wrkSecSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL3"));
	wrkSecSpinCtrl->SetValue(_T("0"));
	wrkFlexGridSizer->Add(wrkSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(wrkFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	zzzFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	zzzLabel = new wxStaticText(GeneralPanel, ID_STATICTEXT2, _("Pause Period"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	zzzFlexGridSizer->Add(zzzLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	zzzFlexGridSizer->Add(40,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	zzzMinSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL5, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL5"));
	zzzMinSpinCtrl->SetValue(_T("0"));
	zzzFlexGridSizer->Add(zzzMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	zzzSecSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL6, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL6"));
	zzzSecSpinCtrl->SetValue(_T("0"));
	zzzFlexGridSizer->Add(zzzSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(zzzFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	remFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	remLabel = new wxStaticText(GeneralPanel, ID_STATICTEXT3, _("Reminder Frequency"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	remFlexGridSizer->Add(remLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	remMinSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL8, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL8"));
	remMinSpinCtrl->SetValue(_T("0"));
	remFlexGridSizer->Add(remMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	remSecSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL9, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL9"));
	remSecSpinCtrl->SetValue(_T("0"));
	remFlexGridSizer->Add(remSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(remFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	chkFlexGridSizer = new wxFlexGridSizer(0, 5, 0, 0);
	chkStaticText = new wxStaticText(GeneralPanel, ID_STATICTEXT4, _("Check Interval"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	chkFlexGridSizer->Add(chkStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkFlexGridSizer->Add(29,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkMinSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL11, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL11"));
	chkMinSpinCtrl->SetValue(_T("0"));
	chkFlexGridSizer->Add(chkMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSecSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL12, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL12"));
	chkSecSpinCtrl->SetValue(_T("0"));
	chkFlexGridSizer->Add(chkSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(chkFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	generalFlexGridSizer->Add(timeStaticBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	startupCheckBox = new wxCheckBox(GeneralPanel, ID_CHECKBOX1, _("Start at PC Startup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	startupCheckBox->SetValue(false);
	generalFlexGridSizer->Add(startupCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	soundCheckBox = new wxCheckBox(GeneralPanel, ID_CHECKBOX2, _("Sound Alarm"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	soundCheckBox->SetValue(false);
	generalFlexGridSizer->Add(soundCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	popupCheckBox = new wxCheckBox(GeneralPanel, ID_CHECKBOX3, _("Popup Alarm"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	popupCheckBox->SetValue(false);
	generalFlexGridSizer->Add(popupCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	emailStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, GeneralPanel, _("Email"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	emailCheckBox = new wxCheckBox(GeneralPanel, ID_CHECKBOX4, _("Email Alert When Pause Ends"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	emailCheckBox->SetValue(false);
	FlexGridSizer2->Add(emailCheckBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	testEmailButton = new wxButton(GeneralPanel, ID_BUTTON1, _("Test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(testEmailButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	emailTextCtrl = new wxTextCtrl(GeneralPanel, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer3->Add(emailTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	emailStaticBoxSizer->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	generalFlexGridSizer->Add(emailStaticBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GeneralPanel->SetSizer(generalFlexGridSizer);
	generalFlexGridSizer->Fit(GeneralPanel);
	generalFlexGridSizer->SetSizeHints(GeneralPanel);
	AdvancedPanel = new wxPanel(optionsNotebook, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	advancedFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
	faceSizeFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
	FaceSizeStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT6, _("Minimum Face Size (X/Y)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	faceSizeFlexGridSizer->Add(FaceSizeStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FaceSizeXSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL4"));
	FaceSizeXSpinCtrl->SetValue(_T("0"));
	faceSizeFlexGridSizer->Add(FaceSizeXSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FaceSizeYSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL7, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL7"));
	FaceSizeYSpinCtrl->SetValue(_T("0"));
	faceSizeFlexGridSizer->Add(FaceSizeYSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(faceSizeFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	tolFlexGridSizer = new wxFlexGridSizer(0, 10, 0, 0);
	tolFlexGridSizer->AddGrowableCol(1);
	tolStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT5, _("Pause Tolerance"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	tolStaticText->SetToolTip(_("Test"));
	tolFlexGridSizer->Add(tolStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	tolFlexGridSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	tolSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 10000, 0, _T("ID_SPINCTRL1"));
	tolSpinCtrl->SetValue(_T("0"));
	tolFlexGridSizer->Add(tolSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(tolFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	indexFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
	indexFlexGridSizer->AddGrowableCol(1);
	indexStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT8, _("Webcam Index"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	indexFlexGridSizer->Add(indexStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	indexFlexGridSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	indexSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL10, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL10"));
	indexSpinCtrl->SetValue(_T("0"));
	indexFlexGridSizer->Add(indexSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(indexFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	cascadeFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
	cascadeFlexGridSizer->AddGrowableCol(1);
	StaticText1 = new wxStaticText(AdvancedPanel, ID_STATICTEXT7, _("Cascade File Location"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	cascadeFlexGridSizer->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cascadeFilePickerCtrl = new wxFilePickerCtrl(AdvancedPanel,ID_CUSTOM1,wxEmptyString,wxEmptyString,wxT("*"),wxDefaultPosition,wxDefaultSize,wxFLP_USE_TEXTCTRL|wxFLP_OPEN|wxFLP_FILE_MUST_EXIST,wxDefaultValidator,_T("ID_CUSTOM1"));
	cascadeFlexGridSizer->Add(cascadeFilePickerCtrl, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(cascadeFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	soundLocFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
	soundLocFlexGridSizer->AddGrowableCol(1);
	soundLocStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT9, _("Sound File Location"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	soundLocFlexGridSizer->Add(soundLocStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	soundLocFilePickerCtrl = new wxFilePickerCtrl(AdvancedPanel,ID_CUSTOM2,wxEmptyString,wxEmptyString,wxT("*"),wxDefaultPosition,wxDefaultSize,wxFLP_USE_TEXTCTRL|wxFLP_OPEN|wxFLP_FILE_MUST_EXIST,wxDefaultValidator,_T("ID_CUSTOM2"));
	soundLocFlexGridSizer->Add(soundLocFilePickerCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(soundLocFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	AdvancedPanel->SetSizer(advancedFlexGridSizer);
	advancedFlexGridSizer->Fit(AdvancedPanel);
	advancedFlexGridSizer->SetSizeHints(AdvancedPanel);
	optionsNotebook->AddPage(GeneralPanel, _("General"), false);
	optionsNotebook->AddPage(AdvancedPanel, _("Advanced"), false);
	optionsFlexGridSizer->Add(optionsNotebook, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	optionsStdDialogButtonSizer = new wxStdDialogButtonSizer();
	optionsStdDialogButtonSizer->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	optionsStdDialogButtonSizer->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	optionsStdDialogButtonSizer->Realize();
	optionsFlexGridSizer->Add(optionsStdDialogButtonSizer, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
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
        std::string(this->emailTextCtrl->GetValue().mb_str()),
        this->indexSpinCtrl->GetValue(),
        this->FaceSizeXSpinCtrl->GetValue(),
        this->FaceSizeYSpinCtrl->GetValue(),
        std::string(this->cascadeFilePickerCtrl->GetPath().mb_str()),
        std::string(this->soundLocFilePickerCtrl->GetPath().mb_str())
    };
}

const int default_WebcamIndex = 0;
const unsigned int default_FaceSizeX = 30;
const unsigned int default_FaceSizeY = 30;
const std::string default_CascadePath = "haarcascade_frontalface_alt.xml";

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
    this->indexSpinCtrl->SetValue(data.webcamIndex);
    this->FaceSizeXSpinCtrl->SetValue(data.faceSizeX);
    this->FaceSizeYSpinCtrl->SetValue(data.faceSizeY);
    this->cascadeFilePickerCtrl->SetPath(wxString(data.cascadePath.c_str(), wxConvUTF8));
    this->soundLocFilePickerCtrl->SetPath(wxString(data.soundPath.c_str(), wxConvUTF8));
}

void OptionsDialog::OnOKClick(wxCommandEvent& event)
{
    if (this->m_Presenter->saveConfig(this))
    {
        Close();
    }
}

