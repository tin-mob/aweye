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

#include "EWLogic.h"
#include "WxHandlerFactory.h"

class OptionsDialog: public wxDialog
{
	public:

		OptionsDialog(wxWindow* parent, EWLogic* logic, wxWindowID id=wxID_ANY);
		virtual ~OptionsDialog();

		//(*Declarations(OptionsDialog)
		wxStaticText* workingLabel;
		wxCheckBox* startupCheckBox;
		wxCheckBox* soundCheckBox;
		wxTextCtrl* tolTextCtrl;
		wxTextCtrl* wrkTextCtrl;
		wxStaticText* tolStaticText;
		wxCheckBox* popupCheckBox;
		wxStaticText* zzzLabel;
		wxTextCtrl* emailTextCtrl;
		wxTextCtrl* zzzTextCtrl;
		wxTextCtrl* chkTextCtrl;
		wxStaticText* remLabel;
		wxStaticText* chkStaticText;
		wxCheckBox* emailCheckBox;
		wxTextCtrl* remTextCtrl;
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
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL6;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_TEXTCTRL1;
		//*)

	private:

        void setFields();

		//(*Handlers(OptionsDialog)
		//*)
		void OnOKClick(wxCommandEvent& event);

		EWLogic* m_Logic;

		DECLARE_EVENT_TABLE()
};

#endif
