#include "TrashPanel.h"

//(*InternalHeaders(TrashPanel)
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/textctrl.h>
//*)

//(*IdInit(TrashPanel)
const long TrashPanel::ID_CHECKBOX4 = wxNewId();
const long TrashPanel::ID_BUTTON1 = wxNewId();
const long TrashPanel::ID_TEXTCTRL1 = wxNewId();
const long TrashPanel::ID_CHECKBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TrashPanel,wxPanel)
	//(*EventTable(TrashPanel)
	//*)
END_EVENT_TABLE()

TrashPanel::TrashPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(TrashPanel)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;
	wxStaticBoxSizer* emailStaticBoxSizer;
	
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	emailStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Email"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	emailCheckBox = new wxCheckBox(this, ID_CHECKBOX4, _("Email Alert When Pause Ends"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	emailCheckBox->SetValue(false);
	FlexGridSizer2->Add(emailCheckBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	testEmailButton = new wxButton(this, ID_BUTTON1, _("Test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(testEmailButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	emailTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer3->Add(emailTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	emailStaticBoxSizer->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(emailStaticBoxSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	startupCheckBox = new wxCheckBox(this, ID_CHECKBOX1, _("Start at PC Startup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	startupCheckBox->SetValue(false);
	FlexGridSizer1->Add(startupCheckBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

TrashPanel::~TrashPanel()
{
	//(*Destroy(TrashPanel)
	//*)
}

