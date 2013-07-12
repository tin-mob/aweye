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

#include "aweye/wx/AboutDialog.h"
#include "aweye/wx/wx_pch.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(AboutDialog)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(AboutDialog)
#include <wx/button.h>
//*)

namespace Aweye { namespace WX {

//(*IdInit(AboutDialog)
const long AboutDialog::ID_STATICTEXT1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AboutDialog,wxDialog)
	//(*EventTable(AboutDialog)
	//*)
END_EVENT_TABLE()

AboutDialog::AboutDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AboutDialog)
	wxStdDialogButtonSizer* m_AboutButtonSizer;
	wxBoxSizer* m_MainBoxSizer;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	m_MainBoxSizer = new wxBoxSizer(wxVERTICAL);
	m_AboutStaticText = new wxStaticText(this, ID_STATICTEXT1, _("EyeWatcher - Watches your eyes and reminds you to take a break.\n\nCopyright (C) 2013 - Robert Morin\n\nThis program is free software: you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\nthe Free Software Foundation, either version 3 of the License, or\n(at your option) any later version.\n\nThis program is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\nGNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with this program.  If not, see <http://www.gnu.org/licenses/>.\n\nwebcam.ico is part of WPZOOM Developer Icon Set by WPZOOM,\ndesigned by David Ferreira. http://www.wpzoom.com\nwebcam-*.png are derived from webcam.ico.\n\nThe icons are licensed under a Creative Commons Attribution-Share Alike 3.0\nUnported License (http://creativecommons.org/licenses/by-nc-sa/3.0/). \n\n"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	m_MainBoxSizer->Add(m_AboutStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_AboutButtonSizer = new wxStdDialogButtonSizer();
	m_AboutButtonSizer->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	m_AboutButtonSizer->Realize();
	m_MainBoxSizer->Add(m_AboutButtonSizer, 0, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5);
	SetSizer(m_MainBoxSizer);
	m_MainBoxSizer->Fit(this);
	m_MainBoxSizer->SetSizeHints(this);
	//*)
}

AboutDialog::~AboutDialog()
{
	//(*Destroy(AboutDialog)
	//*)
}
}}
