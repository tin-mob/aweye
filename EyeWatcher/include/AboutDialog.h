#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(AboutDialog)
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	//*)
#endif
//(*Headers(AboutDialog)
//*)

class AboutDialog: public wxDialog
{
	public:

		AboutDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AboutDialog();

		//(*Declarations(AboutDialog)
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(AboutDialog)
		static const long ID_STATICTEXT1;
		//*)

	private:

		//(*Handlers(AboutDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
