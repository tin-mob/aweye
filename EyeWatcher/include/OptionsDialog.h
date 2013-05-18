#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(OptionsDialog)
	#include <wx/checkbox.h>
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	#include <wx/panel.h>
	#include <wx/stattext.h>
	//*)
#endif
//(*Headers(OptionsDialog)
#include <wx/spinctrl.h>
#include <wx/notebook.h>
#include <wx/filepicker.h>
//*)

#include "AbstractOptionsDialog.h"

class OptionsDialogPres;
class ConfigData;
class OptionsDialog: public wxDialog, public AbstractOptionsDialog
{
	public:

		OptionsDialog(wxWindow* parent, OptionsDialogPres* presenter, wxWindowID id=wxID_ANY);
		virtual ~OptionsDialog();

        virtual ConfigData getData() const;
        virtual void setData(const ConfigData& data);

		//(*Declarations(OptionsDialog)
		wxStaticText* workingLabel;
		wxSpinCtrl* chkMinSpinCtrl;
		wxCheckBox* soundCheckBox;
		wxSpinCtrl* FaceSizeYSpinCtrl;
		wxFilePickerCtrl* soundLocFilePickerCtrl;
		wxStaticText* tolStaticText;
		wxCheckBox* popupCheckBox;
		wxStaticText* zzzLabel;
		wxSpinCtrl* chkSecSpinCtrl;
		wxStaticText* soundLocStaticText;
		wxSpinCtrl* wrkSecSpinCtrl;
		wxSpinCtrl* runningLateMinSpinCtrl;
		wxNotebook* optionsNotebook;
		wxSpinCtrl* tolSpinCtrl;
		wxStaticText* StaticText1;
		wxSpinCtrl* indexSpinCtrl;
		wxSpinCtrl* zzzSecSpinCtrl;
		wxPanel* GeneralPanel;
		wxSpinCtrl* remSecSpinCtrl;
		wxCheckBox* trayIconCheckBox;
		wxPanel* AdvancedPanel;
		wxSpinCtrl* wrkMinSpinCtrl;
		wxStaticText* indexStaticText;
		wxSpinCtrl* zzzMinSpinCtrl;
		wxFilePickerCtrl* cascadeFilePickerCtrl;
		wxStaticText* remLabel;
		wxSpinCtrl* runningLateSecSpinCtrl;
		wxStaticText* chkStaticText;
		wxStaticText* runningLateStaticText;
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
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX5;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT6;
		static const long ID_SPINCTRL4;
		static const long ID_SPINCTRL7;
		static const long ID_STATICTEXT5;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT8;
		static const long ID_SPINCTRL10;
		static const long ID_STATICTEXT7;
		static const long ID_CUSTOM1;
		static const long ID_STATICTEXT9;
		static const long ID_CUSTOM2;
		static const long ID_STATICTEXT10;
		static const long ID_SPINCTRL13;
		static const long ID_SPINCTRL14;
		static const long ID_PANEL2;
		static const long ID_NOTEBOOK1;
		//*)

	private:

		//(*Handlers(OptionsDialog)
		//*)
		void OnOKClick(wxCommandEvent& event);

		OptionsDialogPres* m_Presenter;

		DECLARE_EVENT_TABLE()
};

#endif
