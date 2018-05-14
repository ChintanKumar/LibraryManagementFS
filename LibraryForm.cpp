///-----------------------------------------------------------------
///
/// @file      LibraryForm.cpp
/// @author    coderuth
/// Created:   5/9/2018 12:23:29 AM
/// @section   DESCRIPTION
///            LibraryForm class implementation
///
///------------------------------------------------------------------

#include "LibraryForm.h"
//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

////Header Include End
//----------------------------------------------------------------------------
// LibraryForm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(LibraryForm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(LibraryForm::OnClose)
	
	//EVT_MENU(ID_MNU_CLOSE_1025, LibraryForm::OnClose)
	
    EVT_BUTTON(ID_SEARCHISSUEBUTTON,LibraryForm::searchIssueButtonClick)
	EVT_BUTTON(ID_DELETEISSUEBUTTON,LibraryForm::deleteIssueButtonClick)
	EVT_BUTTON(ID_ADDISSUEBUTTON,LibraryForm::newIssueButtonClick)

	
	EVT_BUTTON(ID_SEARCHBOOKBUTTON,LibraryForm::searchBookButtonClick)
	EVT_BUTTON(ID_DELETEBOOKBUTTON,LibraryForm::deleteBookButtonClick)
	EVT_BUTTON(ID_EDITBOOKBUTTON,LibraryForm::editBookButtonClick)
	EVT_BUTTON(ID_ADDBOOKBUTTON,LibraryForm::addBookButtonClick)
	
	EVT_NOTEBOOK_PAGE_CHANGED(ID_TABPAGE,LibraryForm::tabPagePageChanged)
END_EVENT_TABLE()
////Event Table End

LibraryForm::LibraryForm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
	loadBookData();
	loadIssueData();
}

LibraryForm::~LibraryForm()
{
}

void LibraryForm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	statusBar = new wxStatusBar(this, ID_STATUSBAR);

	tabPage = new wxNotebook(this, ID_TABPAGE, wxPoint(0, 0), wxSize(870, 364), wxNB_DEFAULT);

	bookPage = new wxPanel(tabPage, ID_BOOKPAGE, wxPoint(4, 26), wxSize(862, 334));
	tabPage->AddPage(bookPage, _("Book Record"));

	bookButtonPanel = new wxPanel(bookPage, ID_BOOKBUTTONPANEL, wxPoint(0, 0), wxSize(861, 30));

	addBookButton = new wxButton(bookButtonPanel, ID_ADDBOOKBUTTON, _("Add Book"), wxPoint(0, 3), wxSize(100, 25), 0, wxDefaultValidator, _("addBookButton"));

	deleteBookButton = new wxButton(bookButtonPanel, ID_DELETEBOOKBUTTON, _("Delete Book"), wxPoint(100, 3), wxSize(100, 25), 0, wxDefaultValidator, _("deleteBookButton"));

	searchBookButton = new wxButton(bookButtonPanel, ID_SEARCHBOOKBUTTON, _("Search Book"), wxPoint(200, 3), wxSize(100, 25), 0, wxDefaultValidator, _("searchBookButton"));
	
	editBookButton = new wxButton(bookButtonPanel, ID_EDITBOOKBUTTON, _("Edit Book"), wxPoint(300, 3), wxSize(100, 25), 0, wxDefaultValidator, _("editBookButton"));

	bookGrid = new wxGrid(bookPage, ID_BOOKGRID, wxPoint(0, 31), wxSize(861, 302));
	bookGrid->SetDefaultColSize(90);
	bookGrid->SetDefaultRowSize(25);
	bookGrid->SetRowLabelSize(50);
	bookGrid->SetColLabelSize(25);
	bookGrid->CreateGrid(10,6,wxGrid::wxGridSelectCells);
	
    bookGrid->SetColLabelValue(0, _("ID"));  //from wxSmith 
    bookGrid->SetColLabelValue(1, _("Name")); //from wxSmith 
    bookGrid->SetColLabelValue(2, _("Author"));
    bookGrid->SetColLabelValue(3, _("Quantity"));
    bookGrid->SetColLabelValue(4, _("Price"));
    bookGrid->SetColLabelValue(5, _("Rack"));

	issuePage = new wxPanel(tabPage, ID_ISSUEPAGE, wxPoint(4, 26), wxSize(862, 334));
	tabPage->AddPage(issuePage, _("Issue Record"));

	issueGrid = new wxGrid(issuePage, ID_ISSUEGRID, wxPoint(0, 30), wxSize(861, 305));
	issueGrid->SetDefaultColSize(120);
	issueGrid->SetDefaultRowSize(25);
	issueGrid->SetRowLabelSize(50);
	issueGrid->SetColLabelSize(25);
	issueGrid->CreateGrid(10,6,wxGrid::wxGridSelectCells);
	
	issueGrid->SetColLabelValue(0, _("Issue ID")); //from wxSmith 
    issueGrid->SetColLabelValue(1, _("Student Name"));
    issueGrid->SetColLabelValue(2, _("ID")); //from wxSmith 
    issueGrid->SetColLabelValue(3, _("Book Name"));
    issueGrid->SetColLabelValue(4, _("Issued Date"));
    issueGrid->SetColLabelValue(5, _("Return Date"));

	issueButtonPanel = new wxPanel(issuePage, ID_ISSUEBUTTONPANEL, wxPoint(0, 0), wxSize(861, 30));

	newIssueButton = new wxButton(issueButtonPanel, ID_ADDISSUEBUTTON, _("New Issue"), wxPoint(0, 3), wxSize(100, 25), 0, wxDefaultValidator, _("newIssueButton"));

	deleteIssueButton = new wxButton(issueButtonPanel, ID_DELETEISSUEBUTTON, _("Delete Issue"), wxPoint(100, 3), wxSize(100, 25), 0, wxDefaultValidator, _("deleteIssueButton"));

	searchIssueButton = new wxButton(issueButtonPanel, ID_SEARCHISSUEBUTTON, _("Search Issue"), wxPoint(200, 3), wxSize(100, 25), 0, wxDefaultValidator, _("searchIssueButton"));

	WxMenuBar1 = new wxMenuBar();
	wxMenu *ID_MNU_FILE_1023_Mnu_Obj = new wxMenu();
	ID_MNU_FILE_1023_Mnu_Obj->Append(ID_MNU_CLOSE_1025, _("Close"), _(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_FILE_1023_Mnu_Obj, _("File"));
	
	wxMenu *ID_MNU_ABOUT_1024_Mnu_Obj = new wxMenu();
	WxMenuBar1->Append(ID_MNU_ABOUT_1024_Mnu_Obj, _("About"));
	SetMenuBar(WxMenuBar1);
	
	SetStatusBar(statusBar);
	SetTitle(_("Library"));
	SetIcon(wxNullIcon);
	SetSize(8,8,888,422);
	Center();
	
	////GUI Items Creation End
}

void LibraryForm::OnClose(wxCloseEvent& event) {
	Destroy();
}

void LibraryForm::addBookButtonClick(wxCommandEvent& event) {
    addBookDialog = new AddBookDialog(NULL);
	if (addBookDialog->ShowModal() == 666) {
        addBookDialog->Destroy();
        loadBookData();
    }
}

void LibraryForm::deleteBookButtonClick(wxCommandEvent& event) {
    deleteBookDialog = new DeleteBookDialog(NULL);
	if (deleteBookDialog->ShowModal() == 666) {
        deleteBookDialog->Destroy();
        loadBookData();
    }
}

void LibraryForm::searchBookButtonClick(wxCommandEvent& event) {
	searchBookDialog = new SearchBookDialog(NULL);
	if (searchBookDialog->ShowModal() == 666) {
        searchBookDialog->Destroy();
    }
}

void LibraryForm::editBookButtonClick(wxCommandEvent& event) {
	editBookDialog = new EditBookDialog(NULL);
	if (editBookDialog->ShowModal() == 666) {
        editBookDialog->Destroy();
        loadBookData();
    }
}
void LibraryForm::loadBookData() {
    FILE *fp;
    int j = 0;
    Book a;
    std::stringstream ss;
    fp = fopen("Bibek.dat", "rb+");
    while (fread(&a, sizeof(a), 1, fp) == 1) {  
        ss << a.id;
        bookGrid->SetCellValue(j, 0, _(ss.str()));
        ss.str(std::string());
        
        bookGrid->SetCellValue(j, 1, _(a.name));
        bookGrid->SetCellValue(j, 2, _(a.author));
        
        ss << a.quantity;
        bookGrid->SetCellValue(j, 3, _(ss.str()));
        ss.str(std::string());
        
        ss << a.price;
        bookGrid->SetCellValue(j, 4, _(ss.str()));
        ss.str(std::string());
        
        ss << a.rackno;
        bookGrid->SetCellValue(j, 5, _(ss.str()));
        ss.str(std::string());
        
        j++;
    }
    fclose(fp);
}

void LibraryForm::loadIssueData() {
    int j = 0;
    FILE *fs;
    Book a;
    std::stringstream ss;
    fs = fopen("Issue.dat", "rb+");
    while (fread(&a, sizeof(a), 1, fs) == 1) {
        
        ss << a.issueID;
        issueGrid->SetCellValue(j, 0, _(ss.str()));
        ss.str(std::string());
        
        issueGrid->SetCellValue(j, 1, _(a.stname));
    
        ss << a.id;
        issueGrid->SetCellValue(j, 2, _(ss.str()));
        ss.str(std::string());
        
        issueGrid->SetCellValue(j, 3, _(a.name));
        
        ss << a.duedate.dd << "-" << a.duedate.mm << "-" << a.duedate.yy;
        issueGrid->SetCellValue(j, 4, _(ss.str()));
        ss.str(std::string());
        
        ss << a.issued.dd << "-" << a.issued.mm << "-" << a.issued.yy;
        issueGrid->SetCellValue(j, 5, _(ss.str()));
        ss.str(std::string());
        
        j++;
    }
    fclose(fs);
}


/*
 * newIssueButtonClick
 */
void LibraryForm::newIssueButtonClick(wxCommandEvent& event) {
	newIssueDialog = new NewIssueDialog(NULL);
	if (newIssueDialog->ShowModal() == 666) {
        newIssueDialog->Destroy();
        loadIssueData();
        loadBookData();
    }
}

/*
 * deleteIssueButtonClick
 */
void LibraryForm::deleteIssueButtonClick(wxCommandEvent& event) {
	deleteIssueDialog = new DeleteIssueDialog(NULL);
	if (deleteIssueDialog->ShowModal() == 666) {
        deleteIssueDialog->Destroy();
        loadIssueData();
        loadBookData();
    }
}

/*
 * searchIssueButtonClick
 */
void LibraryForm::searchIssueButtonClick(wxCommandEvent& event) {
	searchIssueDialog = new SearchIssueDialog(NULL);
	if (searchIssueDialog->ShowModal() == 666) {
        searchIssueDialog->Destroy();
        loadIssueData();
    }
}

/*
 * tabPagePageChanged
 */
void LibraryForm::tabPagePageChanged(wxNotebookEvent& event) {
    loadIssueData();
	// insert your code here
}
