///-----------------------------------------------------------------
///
/// @file      SearchIssueDialog.h
/// @author    coderuth
/// Created:   5/13/2018 9:26:36 AM
/// @section   DESCRIPTION
///            SearchIssueDialog class declaration
///
///------------------------------------------------------------------

#ifndef __SEARCHISSUEDIALOG_H__
#define __SEARCHISSUEDIALOG_H__

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
#include <wx/grid.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/statbox.h>
////Header Include End

////Dialog Style Start
#undef SearchIssueDialog_STYLE
#define SearchIssueDialog_STYLE wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX
////Dialog Style End

class SearchIssueDialog : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		SearchIssueDialog(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("SearchIssueDialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = SearchIssueDialog_STYLE);
		virtual ~SearchIssueDialog();
		void searchButtonClick(wxCommandEvent& event);
		void cancelButtonClick(wxCommandEvent& event);
		void okButtonClick(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *cancelButton;
		wxTextCtrl *idField;
		wxButton *okButton;
		wxGrid *issueResultGrid;
		wxStaticText *idLabel;
		wxButton *searchButton;
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
			ID_CANCELBUTTON = 1014,
			ID_IDFIELD = 1013,
			ID_OKBUTTON = 1012,
			ID_ISSUERESULTGRID = 1010,
			ID_IDLABLE = 1009,
			ID_SEARCHBUTTON = 1008,
			ID_WXSTATICBOX1 = 1007,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
