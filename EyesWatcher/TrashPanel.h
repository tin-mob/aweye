#ifndef TRASHPANEL_H
#define TRASHPANEL_H

//(*Headers(TrashPanel)
#include <wx/panel.h>
class wxTextCtrl;
class wxStaticBoxSizer;
class wxFlexGridSizer;
class wxButton;
class wxCheckBox;
//*)

class TrashPanel: public wxPanel
{
	public:

		TrashPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TrashPanel();

		//(*Declarations(TrashPanel)
		wxCheckBox* startupCheckBox;
		wxTextCtrl* emailTextCtrl;
		wxButton* testEmailButton;
		wxCheckBox* emailCheckBox;
		//*)

	protected:

		//(*Identifiers(TrashPanel)
		static const long ID_CHECKBOX4;
		static const long ID_BUTTON1;
		static const long ID_TEXTCTRL1;
		static const long ID_CHECKBOX1;
		//*)

	private:

		//(*Handlers(TrashPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
