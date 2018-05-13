///-----------------------------------------------------------------
///
/// @file      DeleteIssueDialog.cpp
/// @author    coderuth
/// Created:   5/13/2018 9:25:50 AM
/// @section   DESCRIPTION
///            DeleteIssueDialog class implementation
///
///------------------------------------------------------------------

#include "DeleteIssueDialog.h"
#include "Book.h"
#include <sstream>

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// DeleteIssueDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(DeleteIssueDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(DeleteIssueDialog::OnClose)
	EVT_BUTTON(ID_SEARCHBUTTON,DeleteIssueDialog::searchButtonClick)
	EVT_BUTTON(ID_DELETEBUTTON,DeleteIssueDialog::deleteButtonClick)
	EVT_BUTTON(ID_CANCELBUTTON,DeleteIssueDialog::cancelButtonClick)
END_EVENT_TABLE()
////Event Table End

DeleteIssueDialog::DeleteIssueDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

DeleteIssueDialog::~DeleteIssueDialog()
{
} 

void DeleteIssueDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxGrid1 = new wxGrid(this, ID_WXGRID1, wxPoint(15, 87), wxSize(275, 100));
	WxGrid1->SetDefaultColSize(175);
	WxGrid1->SetDefaultRowSize(25);
	WxGrid1->SetRowLabelSize(100);
	WxGrid1->SetColLabelSize(25);
	WxGrid1->CreateGrid(3,1,wxGrid::wxGridSelectCells);
	
    WxGrid1->SetRowLabelValue(0, _("Book Taken By")); //from wxSmith 
    WxGrid1->SetRowLabelValue(1, _("Issued Date")); //from wxSmith 
    WxGrid1->SetRowLabelValue(2, _("Due Date"));
    
    WxGrid1->SetColLabelValue(0, _("Result"));

	searchButton = new wxButton(this, ID_SEARCHBUTTON, _("Search"), wxPoint(15, 58), wxSize(276, 25), 0, wxDefaultValidator, _("searchButton"));

	deleteButton = new wxButton(this, ID_DELETEBUTTON, _("Delete"), wxPoint(216, 190), wxSize(75, 25), 0, wxDefaultValidator, _("deleteButton"));

	cancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(140, 190), wxSize(75, 24), 0, wxDefaultValidator, _("cancelButton"));

	idField = new wxTextCtrl(this, ID_IDFIELD, _(""), wxPoint(82, 30), wxSize(208, 25), 0, wxDefaultValidator, _("idField"));

	idLabel = new wxStaticText(this, ID_IDLABEL, _("Enter ID"), wxPoint(16, 35), wxDefaultSize, 0, _("idLabel"));

	WxStaticBox1 = new wxStaticBox(this, ID_WXSTATICBOX1, _("Delete Issue by ID"), wxPoint(5, 5), wxSize(292, 220));

	SetTitle(_("DeleteIssueDialog"));
	SetIcon(wxNullIcon);
	SetSize(8,8,310,260);
	Center();
	
	////GUI Items Creation End
}

void DeleteIssueDialog::OnClose(wxCloseEvent& /*event*/) {
	Destroy();
}

void DeleteIssueDialog::deleteButtonClick(wxCommandEvent& event) {
    FILE *fs, *fg;
    Book a;
    bool found = false;
    wxString str = idField->GetValue();
    fs = fopen("Issue.dat", "rb+");
    while (fread(&a, sizeof(a), 1, fs) == 1) {
        if (a.id == wxAtoi(str)) {
            found = true;
        }
    }
    if (found) {
        wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Issue Found, Delete?"), wxT("Info"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
        if (dial->ShowModal() == wxID_YES) {
            fg = fopen("record.dat", "wb+");
            rewind(fs);
            while (fread(&a, sizeof(a), 1, fs) == 1) {
              if (a.id != wxAtoi(str)) {
                  fseek(fs, 0, SEEK_CUR);
                  fwrite(&a, sizeof(a), 1, fg);
              }
            }
            fclose(fs);
            fclose(fg);
            remove("Issue.dat");
            rename("record.dat", "Issue.dat");
            wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Issue Removed"), wxT("Info"), wxOK | wxICON_QUESTION);
            dial->ShowModal();
            EndModal(666);
        }
    }else {
        wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Issue Not Found, Try Again ?"), wxT("Info"), wxOK | wxICON_EXCLAMATION);
        dial->ShowModal();
    }
}


/*
 * cancelButtonClick
 */
void DeleteIssueDialog::cancelButtonClick(wxCommandEvent& event) {
	EndModal(true);
}

/*
 * searchButtonClick
 */
void DeleteIssueDialog::searchButtonClick(wxCommandEvent& event)
{
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
        WxGrid1->SetCellValue(0, 0, _(temp.stname));
        
        ss << temp.issued.dd << "-" << temp.issued.mm << "-" << temp.issued.yy;
        WxGrid1->SetCellValue(1, 0, _(ss.str()));
        ss.str(std::string());
        
        ss << temp.duedate.dd << "-" << temp.duedate.mm << "-" << temp.duedate.yy;
        WxGrid1->SetCellValue(2, 0, _(ss.str()));
        ss.str(std::string());

    } else {
        wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No Issue found, Try Again?"), wxT("Info"), wxOK | wxICON_EXCLAMATION);
        dial->ShowModal();
    }
    fclose(fs);
}
