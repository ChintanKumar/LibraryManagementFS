///-----------------------------------------------------------------
///
/// @file      DeleteIssueDialog.h
/// @author    coderuth
/// Created:   5/13/2018 9:25:50 AM
/// @section   DESCRIPTION
///            DeleteIssueDialog class declaration
///
///------------------------------------------------------------------

#ifndef __DELETEISSUEDIALOG_H__
#define __DELETEISSUEDIALOG_H__

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
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
////Header Include End

////Dialog Style Start
#undef DeleteIssueDialog_STYLE
#define DeleteIssueDialog_STYLE wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX
////Dialog Style End

class DeleteIssueDialog : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		DeleteIssueDialog(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("DeleteIssueDialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = DeleteIssueDialog_STYLE);
		virtual ~DeleteIssueDialog();
        void deleteButtonClick(wxCommandEvent& event);
		void cancelButtonClick(wxCommandEvent& event);
		void searchButtonClick(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxGrid *WxGrid1;
		wxButton *searchButton;
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
			ID_WXGRID1 = 1017,
			ID_SEARCHBUTTON = 1016,
			ID_DELETEBUTTON = 1015,
			ID_CANCELBUTTON = 1014,
			ID_IDFIELD = 1013,
			ID_IDLABEL = 1012,
			ID_WXSTATICBOX1 = 1011,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
