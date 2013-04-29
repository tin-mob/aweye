#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(OptionsDialog)
	#include <wx/checkbox.h>
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/panel.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	//*)
#endif
//(*Headers(OptionsDialog)
#include <wx/spinctrl.h>
#include <wx/notebook.h>
#include <wx/filepicker.h>
//*)

#include "EWPresenter.h"
#include "WxHandlerFactory.h"
#include "AbstractOptionsDialog.h"

class OptionsDialog: public wxDialog, public AbstractOptionsDialog
{
	public:

		OptionsDialog(wxWindow* parent, EWPresenter* presenter, wxWindowID id=wxID_ANY);
		virtual ~OptionsDialog();

        virtual ConfigData getData() const;
        virtual void setData(const ConfigData& data);

		//(*Declarations(OptionsDialog)
		wxStaticText* workingLabel;
		wxSpinCtrl* chkMinSpinCtrl;
		wxCheckBox* startupCheckBox;
		wxCheckBox* soundCheckBox;
		wxSpinCtrl* FaceSizeYSpinCtrl;
		wxStaticText* tolStaticText;
		wxCheckBox* popupCheckBox;
		wxStaticText* zzzLabel;
		wxSpinCtrl* chkSecSpinCtrl;
		wxTextCtrl* emailTextCtrl;
		wxSpinCtrl* wrkSecSpinCtrl;
		wxNotebook* optionsNotebook;
		wxSpinCtrl* tolSpinCtrl;
		wxStaticText* StaticText1;
		wxSpinCtrl* zzzSecSpinCtrl;
		wxPanel* GeneralPanel;
		wxSpinCtrl* remSecSpinCtrl;
		wxPanel* AdvancedPanel;
		wxSpinCtrl* wrkMinSpinCtrl;
		wxSpinCtrl* zzzMinSpinCtrl;
		wxFilePickerCtrl* cascadeFilePickerCtrl;
		wxButton* testEmailButton;
		wxStaticText* remLabel;
		wxStaticText* chkStaticText;
		wxCheckBox* emailCheckBox;
		wxStaticText* FaceSizeStaticText;
		wxSpinCtrl* remMinSpinCtrl;
		wxSpinCtrl* FaceSizeXSpinCtrl;
		//*)

	protected:

		//(*Identifiers(OptionsDialog)
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL2;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL5;
		static const long ID_SPINCTRL6;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL8;
		static const long ID_SPINCTRL9;
		static const long ID_STATICTEXT4;
		static const long ID_SPINCTRL11;
		static const long ID_SPINCTRL12;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_BUTTON1;
		static const long ID_TEXTCTRL1;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT6;
		static const long ID_SPINCTRL4;
		static const long ID_SPINCTRL7;
		static const long ID_STATICTEXT5;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT7;
		static const long ID_CUSTOM1;
		static const long ID_PANEL2;
		static const long ID_NOTEBOOK1;
		//*)

	private:

		//(*Handlers(OptionsDialog)
		//*)
		void OnOKClick(wxCommandEvent& event);

		EWPresenter* m_Presenter;

		DECLARE_EVENT_TABLE()
};

#endif
