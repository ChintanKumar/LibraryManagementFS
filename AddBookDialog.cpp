#include "AddBookDialog.h"
#include <iostream>
#include <string>
#include <sstream>

FILE *fpone;

BEGIN_EVENT_TABLE(AddBookDialog,wxDialog)
	EVT_TEXT_ENTER(ID_IDFIELD,AddBookDialog::idFieldEnter)
	EVT_BUTTON(ID_ADDBUTTON,AddBookDialog::addButtonClick)
	EVT_BUTTON(ID_CANCELBUTTON,AddBookDialog::cancelButtonClick)
END_EVENT_TABLE()

AddBookDialog::AddBookDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style){
	CreateGUIControls();
}

AddBookDialog::~AddBookDialog() {
} 

void AddBookDialog::CreateGUIControls() {
    idField = new wxTextCtrl(this, ID_IDFIELD, _(""), wxPoint(100, 30), wxSize(180, 20), 0, wxTextValidator(wxFILTER_NUMERIC, NULL), _("idField"));
	nameField = new wxTextCtrl(this, ID_NAMEFIELD, _(""), wxPoint(100, 55), wxSize(180, 20), 0, wxDefaultValidator, _("nameField"));
    authorField = new wxTextCtrl(this, ID_AUTHORFIELD, _(""), wxPoint(100, 80), wxSize(180, 20), 0, wxDefaultValidator, _("authorField"));
	qtyField = new wxTextCtrl(this, ID_QTYFIELD, _(""), wxPoint(100, 105), wxSize(180, 20), 0, wxTextValidator(wxFILTER_NUMERIC, NULL), _("qtyField"));
    priceField = new wxTextCtrl(this, ID_PRICEFIELD, _(""), wxPoint(100, 130), wxSize(180, 20), 0, wxTextValidator(wxFILTER_NUMERIC, NULL), _("priceField"));
	rackField = new wxTextCtrl(this, ID_RACKFIELD, _(""), wxPoint(100, 155), wxSize(180, 20), 0, wxTextValidator(wxFILTER_NUMERIC, NULL), _("rackField"));

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("ID"), wxPoint(15, 33), wxDefaultSize, 0, _("WxStaticText2"));
	bookNameLabel = new wxStaticText(this, ID_BOOKNAMELABEL, _("Book Name"), wxPoint(16, 58), wxDefaultSize, 0, _("bookNameLabel"));
	WxStaticText5 = new wxStaticText(this, ID_WXSTATICTEXT5, _("Author"), wxPoint(16, 83), wxDefaultSize, 0, _("WxStaticText5"));
	WxStaticText4 = new wxStaticText(this, ID_WXSTATICTEXT4, _("Quantity"), wxPoint(16, 108), wxDefaultSize, 0, _("WxStaticText4"));
    WxStaticText6 = new wxStaticText(this, ID_WXSTATICTEXT6, _("Price"), wxPoint(17, 133), wxDefaultSize, 0, _("WxStaticText6"));
	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("Rack No."), wxPoint(16, 158), wxDefaultSize, 0, _("WxStaticText3"));
    
	addButton = new wxButton(this, ID_ADDBUTTON, _("Add"), wxPoint(203, 210), wxSize(75, 25), 0, wxDefaultValidator, _("addButton"));
	cancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(126, 210), wxSize(75, 25), 0, wxDefaultValidator, _("cancelButton"));

	addStaticBox = new wxStaticBox(this, ID_ADDSTATICBOX, _("Add New Book"), wxPoint(5, 5), wxSize(285, 245));

	SetSize(8,8,303,290);
	Center();
	////GUI Items Creation End
}

void AddBookDialog::addNewBook(Book a) {
    FILE *fp_index;
    fp_index = fopen("Index.dat", "ab+");
	fpone = fopen("Bibek.dat", "ab+");
    fseek(fpone, 0, SEEK_END);
    fseek(fp_index, 0, SEEK_END);
    fwrite(&a, sizeof(a), 1, fpone);
    putw(a.id, fp_index);
    fclose(fp_index);
    fclose(fpone);
}


bool AddBookDialog::checkID(int ID) {
    Book a;
    fpone = fopen("Bibek.dat", "rb+");
    while (fread(&a, sizeof(a), 1, fpone) == 1) {
        if (a.id == ID) {
            return true;
        }
    }
    return false;
}

void AddBookDialog::cancelButtonClick(wxCommandEvent& event) {
	EndModal(true);
}

void AddBookDialog::addButtonClick(wxCommandEvent& event) {
    Book a;
    wxString str = idField->GetValue();
    // Handle Duplicate ID here
    if(checkID(wxAtoi(str))) {
        wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Book ID already exists, Try Again?"), wxT("Info"), wxOK );
        dial->ShowModal();
    } else {
        a.id = wxAtoi(str);
    
        wxString name = nameField->GetValue();
        wxCharBuffer buffer = name.ToUTF8();
        strcpy(a.name, buffer.data());
    
        wxString author = authorField->GetValue();
        wxCharBuffer bufferTwo = author.ToUTF8();
        strcpy(a.author, bufferTwo.data());

        wxString quantity = qtyField->GetValue();
        a.quantity = wxAtoi(quantity);
    
        wxString rack = rackField->GetValue();
        a.rackno = wxAtoi(rack);
    
        wxString price = priceField->GetValue();
        a.price = wxAtoi(price);
        
        addNewBook(a);
        EndModal(666);
    }
}

void AddBookDialog::idFieldEnter(wxCommandEvent& event) {
    
}
