///-----------------------------------------------------------------
///
/// @file      EditBookDialog.cpp
/// @author    coderuth
/// Created:   5/13/2018 9:33:38 AM
/// @section   DESCRIPTION
///            EditBookDialog class implementation
///
///------------------------------------------------------------------

#include "EditBookDialog.h"
#include "Book.h"
#include <sstream>

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// EditBookDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(EditBookDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	EVT_BUTTON(ID_OKBUTTON,EditBookDialog::okButtonClick)
	EVT_BUTTON(ID_CANCELBUTTON,EditBookDialog::cancelButtonClick)
	EVT_BUTTON(ID_SEARCHBUTTON,EditBookDialog::searchButtonClick)
END_EVENT_TABLE()
////Event Table End

EditBookDialog::EditBookDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

EditBookDialog::~EditBookDialog()
{
} 

void EditBookDialog::CreateGUIControls()
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

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("Enter ID"), wxPoint(15, 30), wxDefaultSize, 0, _("WxStaticText1"));

	idLabel = new wxStaticBox(this, ID_IDLABEL, _("Edit Book"), wxPoint(5, 5), wxSize(292, 300));

	SetTitle(_("EditBookDialog"));
	SetIcon(wxNullIcon);
	SetSize(8,8,313,340);
	Center();
	
	////GUI Items Creation End
}

void EditBookDialog::searchButtonClick(wxCommandEvent& event) {
    FILE *fpfour;
    Book a, temp;
    bool found =false;
    std::stringstream ss;
    wxString str = idField->GetValue();
    fpfour = fopen("Bibek.dat", "rb+"); //open file for reading propose
    rewind(fpfour);
	while (fread(&a, sizeof(a), 1, fpfour) == 1) {
        if (a.id == wxAtoi(str)) {
            found = true;
            temp = a;
        }
    }
    
    if(found == true) {
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
void EditBookDialog::cancelButtonClick(wxCommandEvent& event) {
	EndModal(666);
}

/*
 * okButtonClick
 */
void EditBookDialog::okButtonClick(wxCommandEvent& event) {
	FILE *fptwo;
    fptwo = fopen("Bibek.dat", "rb+");
    Book temp, a;

    wxString str = searchGrid->GetCellValue(0, 0);
    temp.id = wxAtoi(str);
    
    wxString name = searchGrid->GetCellValue(1, 0);
    wxCharBuffer buffer = name.ToUTF8();
    strcpy(temp.name, buffer.data());

    wxString author = searchGrid->GetCellValue(2, 0);
    wxCharBuffer bufferTwo = author.ToUTF8();
    strcpy(temp.author, bufferTwo.data());

    wxString quantity = searchGrid->GetCellValue(3, 0);
    temp.quantity = wxAtoi(quantity);

    wxString rack = searchGrid->GetCellValue(5, 0);
    temp.rackno = wxAtoi(rack);

    wxString price = searchGrid->GetCellValue(4, 0);
    temp.price = wxAtoi(price);

    while (fread(&a, sizeof(a), 1, fptwo) == 1) {
        if (a.id == wxAtoi(str)) {
            //std::string msg = "Book Available, Name : " + a.name + "Rack No. : " + a.rackno + "Delete?";
            fseek(fptwo, -sizeof(a), SEEK_CUR);      //  move one structure back     
            fwrite(&temp, sizeof(temp), 1, fptwo);         //  Overwrite updated structure
            break;  
        }
    }
    fclose(fptwo);
    EndModal(666);
}
