///-----------------------------------------------------------------
///
/// @file      SearchBookDialog.cpp
/// @author    coderuth
/// Created:   5/9/2018 12:46:27 AM
/// @section   DESCRIPTION
///            SearchBookDialog class implementation
///
///------------------------------------------------------------------

#include "SearchBookDialog.h"
#include <sstream>
#include "Book.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End
FILE *fpfour;
//----------------------------------------------------------------------------
// SearchBookDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(SearchBookDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(SearchBookDialog::OnClose)
	EVT_BUTTON(ID_OKBUTTON,SearchBookDialog::okButtonClick)
	EVT_BUTTON(ID_CANCELBUTTON,SearchBookDialog::cancelButtonClick)
	EVT_BUTTON(ID_SEARCHBUTTON,SearchBookDialog::searchButtonClick)
	
	EVT_TEXT(ID_IDFIELD,SearchBookDialog::idFieldUpdated)
END_EVENT_TABLE()
////Event Table End

SearchBookDialog::SearchBookDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

SearchBookDialog::~SearchBookDialog()
{
} 

void SearchBookDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	okButton = new wxButton(this, ID_OKBUTTON, _("OK"), wxPoint(208, 270), wxSize(75, 25), 0, wxDefaultValidator, _("okButton"));

	cancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(130, 270), wxSize(75, 25), 0, wxDefaultValidator, _("cancelButton"));

	searchGrid = new wxGrid(this, ID_SEARCHGRID, wxPoint(15, 89), wxSize(270, 175));
	searchGrid->SetDefaultColSize(180);
	searchGrid->SetDefaultRowSize(25);
	searchGrid->SetRowLabelSize(90);
	searchGrid->SetColLabelSize(25);
	searchGrid->CreateGrid(6,1,wxGrid::wxGridSelectCells);
	
	searchGrid->SetRowLabelValue(0, _("ID")); //from wxSmith 
    searchGrid->SetRowLabelValue(1, _("Book Name")); //from wxSmith 
    searchGrid->SetRowLabelValue(2, _("Author"));
    searchGrid->SetRowLabelValue(3, _("Quantity"));
    searchGrid->SetRowLabelValue(4, _("Price"));
    searchGrid->SetRowLabelValue(5, _("Rack No."));
    
    searchGrid->SetColLabelValue(0, _("Result"));

	searchButton = new wxButton(this, ID_SEARCHBUTTON, _("Search"), wxPoint(15, 55), wxSize(272, 25), 0, wxDefaultValidator, _("searchButton"));

	idField = new wxTextCtrl(this, ID_IDFIELD, _(""), wxPoint(95, 26), wxSize(190, 25), 0, wxDefaultValidator, _("idField"));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("ID"), wxPoint(15, 30), wxDefaultSize, 0, _("WxStaticText1"));

	idLabel = new wxStaticBox(this, ID_IDLABEL, _("Search Book"), wxPoint(5, 5), wxSize(292, 300));

	SetTitle(_("SearchBookDialog"));
	SetIcon(wxNullIcon);
	SetSize(8,8,313,340);
	Center();
	
	////GUI Items Creation End
}

void SearchBookDialog::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * idFieldUpdated
 */
void SearchBookDialog::idFieldUpdated(wxCommandEvent& event)
{
	// insert your code here
}

/*
 * searchButtonClick
 */
void SearchBookDialog::searchButtonClick(wxCommandEvent& event) {
    Book a, temp;
    int num, pos = 0;
    bool found =false;
    std::stringstream ss;
    wxString str = idField->GetValue();
    
    fpfour = fopen("Index.dat", "rb+"); //open file for reading propose
	while ((num = getw(fpfour)) != EOF) {
        if (num == wxAtoi(str)) {
            found = true;
            break;
            //temp = a;
        }
        pos++;
    }
    

    
    //fpfour = fopen("Bibek.dat", "rb+"); //open file for reading propose
//    rewind(fpfour);
//	while (fread(&a, sizeof(a), 1, fpfour) == 1) {
//        if (a.id == wxAtoi(str)) {
//            found = true;
//            temp = a;
//        }
//    }
    
    if(found == true) {
        fpfour = fopen("Bibek.dat", "rb+"); //open file for reading propose
        
        fseek(fpfour, pos * sizeof(temp), SEEK_SET);
        fread(&temp, sizeof(temp), 1, fpfour);
        
        ss << temp.id;
        searchGrid->SetCellValue(0, 0, _(ss.str()));
        ss.str(std::string());
        
        searchGrid->SetCellValue(1, 0, _(temp.name));
        searchGrid->SetCellValue(2, 0, _(temp.author));
        
        ss << temp.quantity;
        searchGrid->SetCellValue(3, 0, _(ss.str()));
        ss.str(std::string());
        
        ss << temp.price;
        searchGrid->SetCellValue(4, 0, _(ss.str()));
        ss.str(std::string());
        
        ss << temp.rackno;
        searchGrid->SetCellValue(5, 0, _(ss.str()));
        ss.str(std::string());
        
    } else {
        wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No Book found, Try Again?"), wxT("Info"), wxOK | wxICON_EXCLAMATION);
        dial->ShowModal();
    }
}

/*
 * cancelButtonClick
 */
void SearchBookDialog::cancelButtonClick(wxCommandEvent& event) {
	EndModal(666);
}

/*
 * okButtonClick
 */
void SearchBookDialog::okButtonClick(wxCommandEvent& event) {
	EndModal(666);
}
