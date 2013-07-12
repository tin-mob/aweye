/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "aweye/ConfigData.h"
#include "aweye/AbstractOptionsDialogPres.h"
#include "aweye/wx/OptionsDialog.h"
#include "aweye/wx/wx_pch.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(OptionsDialog)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(OptionsDialog)
#include <wx/button.h>
//*)

namespace Aweye { namespace WX {

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
const long OptionsDialog::ID_CHECKBOX2 = wxNewId();
const long OptionsDialog::ID_CHECKBOX3 = wxNewId();
const long OptionsDialog::ID_CHECKBOX5 = wxNewId();
const long OptionsDialog::ID_CHECKBOX1 = wxNewId();
const long OptionsDialog::ID_PANEL1 = wxNewId();
const long OptionsDialog::ID_STATICTEXT6 = wxNewId();
const long OptionsDialog::ID_SPINCTRL4 = wxNewId();
const long OptionsDialog::ID_SPINCTRL7 = wxNewId();
const long OptionsDialog::ID_STATICTEXT5 = wxNewId();
const long OptionsDialog::ID_SPINCTRL1 = wxNewId();
const long OptionsDialog::ID_STATICTEXT11 = wxNewId();
const long OptionsDialog::ID_SPINCTRL15 = wxNewId();
const long OptionsDialog::ID_STATICTEXT8 = wxNewId();
const long OptionsDialog::ID_SPINCTRL10 = wxNewId();
const long OptionsDialog::ID_STATICTEXT7 = wxNewId();
const long OptionsDialog::ID_CUSTOM1 = wxNewId();
const long OptionsDialog::ID_STATICTEXT9 = wxNewId();
const long OptionsDialog::ID_CUSTOM2 = wxNewId();
const long OptionsDialog::ID_STATICTEXT10 = wxNewId();
const long OptionsDialog::ID_SPINCTRL13 = wxNewId();
const long OptionsDialog::ID_SPINCTRL14 = wxNewId();
const long OptionsDialog::ID_PANEL2 = wxNewId();
const long OptionsDialog::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OptionsDialog,wxDialog)
	//(*EventTable(OptionsDialog)
	//*)
END_EVENT_TABLE()

OptionsDialog::OptionsDialog(wxWindow* parent, AbstractOptionsDialogPres& presenter, wxWindowID id) :
                             m_Presenter(presenter)
{
	//(*Initialize(OptionsDialog)
	wxFlexGridSizer* runningLateFlexGridSizer;
	wxFlexGridSizer* wrkFlexGridSizer;
	wxFlexGridSizer* faceSizeFlexGridSizer;
	wxFlexGridSizer* workTolFlexGridSizer;
	wxFlexGridSizer* chkFlexGridSizer;
	wxFlexGridSizer* cascadeFlexGridSizer;
	wxFlexGridSizer* soundLocFlexGridSizer;
	wxFlexGridSizer* optionsFlexGridSizer;
	wxFlexGridSizer* indexFlexGridSizer;
	wxStaticBoxSizer* timeStaticBoxSizer;
	wxFlexGridSizer* zzzFlexGridSizer;
	wxFlexGridSizer* generalFlexGridSizer;
	wxFlexGridSizer* remFlexGridSizer;
	wxStdDialogButtonSizer* optionsStdDialogButtonSizer;
	wxFlexGridSizer* pauseTolFlexGridSizer;
	wxFlexGridSizer* advancedFlexGridSizer;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	optionsFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
	optionsNotebook = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
	GeneralPanel = new wxPanel(optionsNotebook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	generalFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
	generalFlexGridSizer->AddGrowableCol(0);
	timeStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, GeneralPanel, _("Time (Minutes / Seconds)"));
	wrkFlexGridSizer = new wxFlexGridSizer(0, 4, 0, 0);
	wrkFlexGridSizer->AddGrowableCol(1);
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
	zzzFlexGridSizer = new wxFlexGridSizer(0, 4, 0, 0);
	zzzFlexGridSizer->AddGrowableCol(1);
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
	remFlexGridSizer = new wxFlexGridSizer(0, 4, 0, 0);
	remFlexGridSizer->AddGrowableCol(1);
	remLabel = new wxStaticText(GeneralPanel, ID_STATICTEXT3, _("Reminder Frequency"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	remFlexGridSizer->Add(remLabel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	remFlexGridSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	remMinSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL8, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL8"));
	remMinSpinCtrl->SetValue(_T("0"));
	remFlexGridSizer->Add(remMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	remSecSpinCtrl = new wxSpinCtrl(GeneralPanel, ID_SPINCTRL9, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL9"));
	remSecSpinCtrl->SetValue(_T("0"));
	remFlexGridSizer->Add(remSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	timeStaticBoxSizer->Add(remFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	chkFlexGridSizer = new wxFlexGridSizer(0, 4, 0, 0);
	chkFlexGridSizer->AddGrowableCol(1);
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
	soundCheckBox = new wxCheckBox(GeneralPanel, ID_CHECKBOX2, _("Sound Alarm"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	soundCheckBox->SetValue(false);
	generalFlexGridSizer->Add(soundCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	popupCheckBox = new wxCheckBox(GeneralPanel, ID_CHECKBOX3, _("Popup Alarm"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	popupCheckBox->SetValue(false);
	generalFlexGridSizer->Add(popupCheckBox, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	trayIconCheckBox = new wxCheckBox(GeneralPanel, ID_CHECKBOX5, _("Tray Icon"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	trayIconCheckBox->SetValue(false);
	generalFlexGridSizer->Add(trayIconCheckBox, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cummulCheckBox = new wxCheckBox(GeneralPanel, ID_CHECKBOX1, _("Cummulative Pause"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	cummulCheckBox->SetValue(false);
	generalFlexGridSizer->Add(cummulCheckBox, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GeneralPanel->SetSizer(generalFlexGridSizer);
	generalFlexGridSizer->Fit(GeneralPanel);
	generalFlexGridSizer->SetSizeHints(GeneralPanel);
	AdvancedPanel = new wxPanel(optionsNotebook, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	advancedFlexGridSizer = new wxFlexGridSizer(0, 1, 0, 0);
	faceSizeFlexGridSizer = new wxFlexGridSizer(0, 4, 0, 0);
	faceSizeFlexGridSizer->AddGrowableCol(1);
	FaceSizeStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT6, _("Minimum Face Size (X/Y)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	faceSizeFlexGridSizer->Add(FaceSizeStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	faceSizeFlexGridSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FaceSizeXSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL4"));
	FaceSizeXSpinCtrl->SetValue(_T("0"));
	faceSizeFlexGridSizer->Add(FaceSizeXSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FaceSizeYSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL7, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL7"));
	FaceSizeYSpinCtrl->SetValue(_T("0"));
	faceSizeFlexGridSizer->Add(FaceSizeYSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(faceSizeFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	pauseTolFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
	pauseTolFlexGridSizer->AddGrowableCol(1);
	pauseTolStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT5, _("Pause Tolerance"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	pauseTolStaticText->SetToolTip(_("Test"));
	pauseTolFlexGridSizer->Add(pauseTolStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pauseTolFlexGridSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pauseTolSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 10000, 0, _T("ID_SPINCTRL1"));
	pauseTolSpinCtrl->SetValue(_T("0"));
	pauseTolFlexGridSizer->Add(pauseTolSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(pauseTolFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	workTolFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
	workTolFlexGridSizer->AddGrowableCol(1);
	workTolStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT11, _("Work Tolerance"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	workTolStaticText->SetToolTip(_("Test"));
	workTolFlexGridSizer->Add(workTolStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	workTolFlexGridSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	workTolSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL15, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 10000, 0, _T("ID_SPINCTRL15"));
	workTolSpinCtrl->SetValue(_T("0"));
	workTolFlexGridSizer->Add(workTolSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(workTolFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	indexFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
	indexFlexGridSizer->AddGrowableCol(1);
	indexStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT8, _("Webcam Index"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	indexFlexGridSizer->Add(indexStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	indexFlexGridSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	indexSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL10, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL10"));
	indexSpinCtrl->SetValue(_T("0"));
	indexFlexGridSizer->Add(indexSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(indexFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	cascadeFlexGridSizer = new wxFlexGridSizer(0, 2, 0, 0);
	cascadeFlexGridSizer->AddGrowableCol(1);
	StaticText1 = new wxStaticText(AdvancedPanel, ID_STATICTEXT7, _("Cascade File Location"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	cascadeFlexGridSizer->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cascadeFilePickerCtrl = new wxFilePickerCtrl(AdvancedPanel,ID_CUSTOM1,wxEmptyString,wxEmptyString,wxT("*"),wxDefaultPosition,wxDefaultSize,wxFLP_USE_TEXTCTRL|wxFLP_OPEN|wxFLP_FILE_MUST_EXIST,wxDefaultValidator,_T("ID_CUSTOM1"));
	cascadeFlexGridSizer->Add(cascadeFilePickerCtrl, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(cascadeFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	soundLocFlexGridSizer = new wxFlexGridSizer(0, 2, 0, 0);
	soundLocFlexGridSizer->AddGrowableCol(1);
	soundLocStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT9, _("Sound File Location"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	soundLocFlexGridSizer->Add(soundLocStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	soundLocFilePickerCtrl = new wxFilePickerCtrl(AdvancedPanel,ID_CUSTOM2,wxEmptyString,wxEmptyString,wxT("*"),wxDefaultPosition,wxDefaultSize,wxFLP_USE_TEXTCTRL|wxFLP_OPEN|wxFLP_FILE_MUST_EXIST,wxDefaultValidator,_T("ID_CUSTOM2"));
	soundLocFlexGridSizer->Add(soundLocFilePickerCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(soundLocFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	runningLateFlexGridSizer = new wxFlexGridSizer(0, 4, 0, 0);
	runningLateFlexGridSizer->AddGrowableCol(1);
	runningLateStaticText = new wxStaticText(AdvancedPanel, ID_STATICTEXT10, _("Yellow Icon Threshold"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	runningLateFlexGridSizer->Add(runningLateStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	runningLateFlexGridSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	runningLateMinSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL13, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL13"));
	runningLateMinSpinCtrl->SetValue(_T("0"));
	runningLateFlexGridSizer->Add(runningLateMinSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	runningLateSecSpinCtrl = new wxSpinCtrl(AdvancedPanel, ID_SPINCTRL14, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 59, 0, _T("ID_SPINCTRL14"));
	runningLateSecSpinCtrl->SetValue(_T("0"));
	runningLateFlexGridSizer->Add(runningLateSecSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	advancedFlexGridSizer->Add(runningLateFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
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
    m_Presenter.init(*this);

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
            wrkMinSpinCtrl->GetValue() * 60 + wrkSecSpinCtrl->GetValue()),
        boost::posix_time::seconds(
            zzzMinSpinCtrl->GetValue() * 60 + zzzSecSpinCtrl->GetValue()),
        boost::posix_time::seconds(
            remMinSpinCtrl->GetValue() * 60 + remSecSpinCtrl->GetValue()),
        boost::posix_time::seconds(
            chkMinSpinCtrl->GetValue() * 60 + chkSecSpinCtrl->GetValue()),
        pauseTolSpinCtrl->GetValue(),
        workTolSpinCtrl->GetValue(),
        soundCheckBox->GetValue(),
        popupCheckBox->GetValue(),
        trayIconCheckBox->GetValue(),
        indexSpinCtrl->GetValue(),
        FaceSizeXSpinCtrl->GetValue(),
        FaceSizeYSpinCtrl->GetValue(),
        std::string(cascadeFilePickerCtrl->GetPath().mb_str()),
        std::string(soundLocFilePickerCtrl->GetPath().mb_str()),
        boost::posix_time::seconds(
            runningLateMinSpinCtrl->GetValue() * 60 + runningLateSecSpinCtrl->GetValue()),
        cummulCheckBox->GetValue()
    };
}

void OptionsDialog::setData(const ConfigData& data)
{
	soundCheckBox->SetValue(data.soundAlarm);
    pauseTolSpinCtrl->SetValue(data.pauseTol);
    workTolSpinCtrl->SetValue(data.workTol);
    wrkMinSpinCtrl->SetValue(data.workLength.total_seconds() / 60);
    wrkSecSpinCtrl->SetValue(data.workLength.seconds());
    popupCheckBox->SetValue(data.popupAlarm);
    zzzMinSpinCtrl->SetValue(data.pauseLength.total_seconds() / 60);
    zzzSecSpinCtrl->SetValue(data.pauseLength.seconds());
    chkMinSpinCtrl->SetValue(data.checkFreq.total_seconds() / 60);
    chkSecSpinCtrl->SetValue(data.checkFreq.seconds());
    remMinSpinCtrl->SetValue(data.remFreq.total_seconds() / 60);
    remSecSpinCtrl->SetValue(data.remFreq.seconds());
    indexSpinCtrl->SetValue(data.webcamIndex);
    FaceSizeXSpinCtrl->SetValue(data.faceSizeX);
    FaceSizeYSpinCtrl->SetValue(data.faceSizeY);
    cascadeFilePickerCtrl->SetPath(wxString(data.cascadePath.c_str(), wxConvUTF8));
    soundLocFilePickerCtrl->SetPath(wxString(data.soundPath.c_str(), wxConvUTF8));
    runningLateMinSpinCtrl->SetValue(data.runningLateThreshold.total_seconds() / 60);
    runningLateSecSpinCtrl->SetValue(data.runningLateThreshold.seconds());
    trayIconCheckBox->SetValue(data.trayIcon);
    cummulCheckBox->SetValue(data.cummulPause);
}

void OptionsDialog::disableTray()
{
    trayIconCheckBox->Disable();
}

void OptionsDialog::OnOKClick(wxCommandEvent& event)
{
    if (m_Presenter.saveData(getData()))
    {
        EndModal(wxID_OK);
    }
}
}}
