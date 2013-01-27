#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(OptionsDialog)
	#include <wx/checkbox.h>
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	//*)
#endif
//(*Headers(OptionsDialog)
//*)

class OptionsDialog: public wxDialog
{
	public:

		OptionsDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~OptionsDialog();

		//(*Declarations(OptionsDialog)
		wxStaticText* workingLabel;
		wxTextCtrl* reminderTextCtrl;
		wxTextCtrl* checkTextCtrl;
		wxCheckBox* startupCheckBox;
		wxCheckBox* soundCheckBox;
		wxStaticText* pauseLabel;
		wxCheckBox* popupCheckBox;
		wxTextCtrl* emailTextCtrl;
		wxTextCtrl* workingTextCtrl;
		wxStaticText* reminderLabel;
		wxStaticText* checkStaticText;
		wxTextCtrl* pauseTextCtrl;
		wxCheckBox* emailCheckBox;
		//*)

	protected:

		//(*Identifiers(OptionsDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL4;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL5;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_TEXTCTRL1;
		//*)

	private:

		//(*Handlers(OptionsDialog)
		//*)
		void OnOKClick(wxCommandEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif
