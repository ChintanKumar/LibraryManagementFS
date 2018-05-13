///-----------------------------------------------------------------
///
/// @file      LibraryForm.h
/// @author    coderuth
/// Created:   5/9/2018 12:23:29 AM
/// @section   DESCRIPTION
///            LibraryForm class declaration
///
///------------------------------------------------------------------

#ifndef __LIBRARYFORM_H__
#define __LIBRARYFORM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/menu.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include "EditBookDialog.h"
#include "AddBookDialog.h"
#include "DeleteBookDialog.h"
#include "SearchBookDialog.h"

#include "NewIssueDialog.h"
#include "DeleteIssueDialog.h"
#include "SearchIssueDialog.h"
////Header Include End

////Dialog Style Start       
#undef LibraryForm_STYLE
#define LibraryForm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class LibraryForm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		LibraryForm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Library"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = LibraryForm_STYLE);
		virtual ~LibraryForm();
		void addBookButtonClick(wxCommandEvent& event);
		void deleteBookButtonClick(wxCommandEvent& event);
		void searchBookButtonClick(wxCommandEvent& event);
		void editBookButtonClick(wxCommandEvent& event);
		void newIssueButtonClick(wxCommandEvent& event);
		void deleteIssueButtonClick(wxCommandEvent& event);
		void searchIssueButtonClick(wxCommandEvent& event);
		void editIssueButtonClick(wxCommandEvent& event);
		void tabPagePageChanged(wxNotebookEvent& event);  
		void loadBookData();
		void loadIssueData();
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxMenuBar *WxMenuBar1;
		wxButton *searchIssueButton;
		wxButton *deleteIssueButton;
		wxButton *newIssueButton;
		wxPanel *issueButtonPanel;
		wxGrid *issueGrid;
		wxPanel *issuePage;
		wxGrid *bookGrid;
		wxButton *searchBookButton;
		wxButton *deleteBookButton;
		wxButton *addBookButton;
		wxButton *editBookButton;
		wxPanel *bookButtonPanel;
		wxPanel *bookPage;
		wxNotebook *tabPage;
		wxStatusBar *statusBar;
		
		SearchBookDialog *searchBookDialog;
		EditBookDialog *editBookDialog;
		AddBookDialog *addBookDialog;
        DeleteBookDialog *deleteBookDialog;
        
        NewIssueDialog *newIssueDialog;
        DeleteIssueDialog *deleteIssueDialog;
        SearchIssueDialog *searchIssueDialog;
		////GUI Control Declarat
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{                                          
			ID_MNU_FILE_1023 = 1023,
			ID_MNU_CLOSE_1025 = 1025,
			ID_MNU_ABOUT_1024 = 1024,
			
			ID_ISSUEBUTTONPANEL = 1022,
			ID_ISSUEGRID = 1021,
			ID_ISSUEPAGE = 1017,
			ID_BOOKGRID = 1020,
			ID_SEARCHBOOKBUTTON = 1011,
			ID_DELETEBOOKBUTTON = 1010,
			ID_ADDBOOKBUTTON = 1009,
			ID_BOOKBUTTONPANEL = 1019,
            ID_EDITBOOKBUTTON = 1018,			
			ID_BOOKPAGE = 1016,
			ID_TABPAGE = 1015,
			ID_STATUSBAR = 1001,
			ID_SEARCHISSUEBUTTON = 1023,
			ID_DELETEISSUEBUTTON = 1024,
			ID_ADDISSUEBUTTON = 1025,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:                     
        void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
