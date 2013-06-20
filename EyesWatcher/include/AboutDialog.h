/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


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

namespace EW
{
class AboutDialog: public wxDialog
{
	public:

		AboutDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AboutDialog();

		//(*Declarations(AboutDialog)
		wxStaticText* m_AboutStaticText;
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
}
#endif
