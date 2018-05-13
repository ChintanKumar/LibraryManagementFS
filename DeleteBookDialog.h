///-----------------------------------------------------------------
///
/// @file      DeleteBookDialog.h
/// @author    coderuth
/// Created:   5/9/2018 12:45:42 AM
/// @section   DESCRIPTION
///            DeleteBookDialog class declaration
///
///------------------------------------------------------------------

#ifndef __DELETEBOOKDIALOG_H__
#define __DELETEBOOKDIALOG_H__

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
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
////Header Include End

////Dialog Style Start
#undef DeleteBookDialog_STYLE
#define DeleteBookDialog_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class DeleteBookDialog : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		DeleteBookDialog(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("DeleteBookDialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = DeleteBookDialog_STYLE);
		virtual ~DeleteBookDialog();
		void deleteButtonClick(wxCommandEvent& event);
		void cancelButtonClick(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *deleteButton;
		wxButton *cancelButton;
		wxTextCtrl *idField;
		wxStaticText *idLabel;
		wxStaticBox *WxStaticBox1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_DELETEBUTTON = 1007,
			ID_CANCEL = 1006,
			ID_IDFIELD = 1004,
			ID_IDLABEL = 1003,
			ID_WXSTATICBOX1 = 1002,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
