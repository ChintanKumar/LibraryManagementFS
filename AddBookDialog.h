///-----------------------------------------------------------------
///
/// @file      AddBookDialog.h
/// @author    coderuth
/// Created:   5/9/2018 12:45:06 AM
/// @section   DESCRIPTION
///            AddBookDialog class declaration
///
///------------------------------------------------------------------

#ifndef __ADDBOOKDIALOG_H__
#define __ADDBOOKDIALOG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include "Book.h"
////Header Include End

////Dialog Style Start
#undef AddBookDialog_STYLE
#define AddBookDialog_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class AddBookDialog : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		AddBookDialog(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Add New Book"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = AddBookDialog_STYLE);
		virtual ~AddBookDialog();
		bool checkID(int);
		void addNewBook(Book);
		void cancelButtonClick(wxCommandEvent& event);
		void addButtonClick(wxCommandEvent& event);
		void idFieldEnter(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxStaticText *WxStaticText4;
		wxTextCtrl *priceField;
		wxTextCtrl *qtyField;
		wxTextCtrl *authorField;
		wxTextCtrl *rackField;
		wxTextCtrl *nameField;
		wxTextCtrl *idField;
		wxStaticText *WxStaticText7;
		wxStaticText *WxStaticText6;
		wxStaticText *WxStaticText5;
		wxStaticText *bookNameLabel;
		wxStaticText *WxStaticText3;
		wxStaticText *WxStaticText2;
		wxButton *addButton;
		wxButton *cancelButton;
		wxStaticBox *addStaticBox;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXSTATICTEXT4 = 1018,
			ID_PRICEFIELD = 1017,
			ID_QTYFIELD = 1016,
			ID_AUTHORFIELD = 1015,
			ID_RACKFIELD = 1014,
			ID_NAMEFIELD = 1013,
			ID_IDFIELD = 1012,
			ID_WXSTATICTEXT7 = 1011,
			ID_WXSTATICTEXT6 = 1010,
			ID_WXSTATICTEXT5 = 1009,
			ID_BOOKNAMELABEL = 1008,
			ID_WXSTATICTEXT3 = 1007,
			ID_WXSTATICTEXT2 = 1006,
			ID_ADDBUTTON = 1003,
			ID_CANCELBUTTON = 1002,
			ID_ADDSTATICBOX = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
