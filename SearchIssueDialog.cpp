///-----------------------------------------------------------------
///
/// @file      SearchIssueDialog.cpp
/// @author    coderuth
/// Created:   5/13/2018 9:26:36 AM
/// @section   DESCRIPTION
///            SearchIssueDialog class implementation
///
///------------------------------------------------------------------

#include "SearchIssueDialog.h"
#include "Book.h"
#include <sstream>

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// SearchIssueDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(SearchIssueDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(SearchIssueDialog::OnClose)
	EVT_BUTTON(ID_CANCELBUTTON,SearchIssueDialog::cancelButtonClick)
	EVT_BUTTON(ID_OKBUTTON,SearchIssueDialog::okButtonClick)
	EVT_BUTTON(ID_SEARCHBUTTON,SearchIssueDialog::searchButtonClick)
END_EVENT_TABLE()
////Event Table End

SearchIssueDialog::SearchIssueDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

SearchIssueDialog::~SearchIssueDialog()
{
} 

void SearchIssueDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	cancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(111, 190), wxSize(75, 25), 0, wxDefaultValidator, _("cancelButton"));

	idField = new wxTextCtrl(this, ID_IDFIELD, _(""), wxPoint(93, 24), wxSize(170, 20), 0, wxDefaultValidator, _("idField"));

	okButton = new wxButton(this, ID_OKBUTTON, _("OK"), wxPoint(189, 190), wxSize(75, 25), 0, wxDefaultValidator, _("okButton"));

	issueResultGrid = new wxGrid(this, ID_ISSUERESULTGRID, wxPoint(16, 80), wxSize(247, 100));
	issueResultGrid->SetDefaultColSize(147);
	issueResultGrid->SetDefaultRowSize(25);
	issueResultGrid->SetRowLabelSize(100);
	issueResultGrid->SetColLabelSize(25);
	issueResultGrid->CreateGrid(3,1,wxGrid::wxGridSelectCells);
	
    issueResultGrid->SetRowLabelValue(0, _("Book Taken By")); //from wxSmith 
    issueResultGrid->SetRowLabelValue(1, _("Issued Date")); //from wxSmith 
    issueResultGrid->SetRowLabelValue(2, _("Due Date"));
    
    issueResultGrid->SetColLabelValue(0, _("Result"));

	idLabel = new wxStaticText(this, ID_IDLABLE, _("Enter ID"), wxPoint(16, 26), wxDefaultSize, 0, _("idLabel"));

	searchButton = new wxButton(this, ID_SEARCHBUTTON, _("Search"), wxPoint(14, 50), wxSize(251, 25), 0, wxDefaultValidator, _("searchButton"));

	WxStaticBox1 = new wxStaticBox(this, ID_WXSTATICBOX1, _("Search Issue by ID"), wxPoint(5, 4), wxSize(269, 220));

	SetTitle(_("SearchIssueDialog"));
	SetIcon(wxNullIcon);
	SetSize(8,8,290,260);
	Center();
	
	////GUI Items Creation End
}

void SearchIssueDialog::OnClose(wxCloseEvent& /*event*/) {
	Destroy();
}

/*
 * searchButtonClick
 */
void SearchIssueDialog::searchButtonClick(wxCommandEvent& event) {
    FILE *fs;
    Book a, temp;
    bool found = false;
    
    std::stringstream ss;
    wxString str = idField->GetValue();
    
    fs = fopen("Issue.dat", "rb");
    while (fread(&a, sizeof(a), 1, fs) == 1) {
        if (a.id == wxAtoi(str)) {
            found = true;
            temp = a;
        }
    }
    if (found) {
        issueResultGrid->SetCellValue(0, 0, _(temp.stname));
        
        ss << temp.issued.dd << "-" << temp.issued.mm << "-" << temp.issued.yy;
        issueResultGrid->SetCellValue(1, 0, _(ss.str()));
        ss.str(std::string());
        
        ss << temp.duedate.dd << "-" << temp.duedate.mm << "-" << temp.duedate.yy;
        issueResultGrid->SetCellValue(2, 0, _(ss.str()));
        ss.str(std::string());

    } else {
        wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No Issue found, Try Again?"), wxT("Info"), wxOK | wxICON_EXCLAMATION);
        dial->ShowModal();
    }
    fclose(fs);  
}


/*
 * cancelButtonClick
 */
void SearchIssueDialog::cancelButtonClick(wxCommandEvent& event) {
	EndModal(true);
}

/*
 * okButtonClick
 */
void SearchIssueDialog::okButtonClick(wxCommandEvent& event) {
    EndModal(true);
	// insert your code here
}
