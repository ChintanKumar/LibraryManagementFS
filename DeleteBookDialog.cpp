///-----------------------------------------------------------------
///
/// @file      DeleteBookDialog.cpp
/// @author    coderuth
/// Created:   5/9/2018 12:45:42 AM
/// @section   DESCRIPTION
///            DeleteBookDialog class implementation
///
///------------------------------------------------------------------

#include "DeleteBookDialog.h"
#include "Book.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// DeleteBookDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(DeleteBookDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(DeleteBookDialog::OnClose)
	EVT_BUTTON(ID_DELETEBUTTON,DeleteBookDialog::deleteButtonClick)
	EVT_BUTTON(ID_CANCEL,DeleteBookDialog::cancelButtonClick)
END_EVENT_TABLE()
////Event Table End

DeleteBookDialog::DeleteBookDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

DeleteBookDialog::~DeleteBookDialog()
{
} 

void DeleteBookDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	deleteButton = new wxButton(this, ID_DELETEBUTTON, _("Delete"), wxPoint(214, 65), wxSize(75, 25), 0, wxDefaultValidator, _("deleteButton"));

	cancelButton = new wxButton(this, ID_CANCEL, _("Cancel"), wxPoint(137, 64), wxSize(75, 26), 0, wxDefaultValidator, _("cancelButton"));

	idField = new wxTextCtrl(this, ID_IDFIELD, _(""), wxPoint(74, 30), wxSize(216, 25), 0, wxDefaultValidator, _("idField"));

	idLabel = new wxStaticText(this, ID_IDLABEL, _("ID"), wxPoint(16, 35), wxDefaultSize, 0, _("idLabel"));

	WxStaticBox1 = new wxStaticBox(this, ID_WXSTATICBOX1, _("Delete Book by ID"), wxPoint(5, 5), wxSize(292, 100));

	SetTitle(_("DeleteBookDialog"));
	SetIcon(wxNullIcon);
	SetSize(8,8,312,144);
	Center();
	
	////GUI Items Creation End
}

void DeleteBookDialog::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * deleteButtonClick
 */
void DeleteBookDialog::deleteButtonClick(wxCommandEvent& event) {
    FILE *fptwo, *fpthree;
    Book a;
    int FOUND_POS;
    bool found = false;
    wxString str = idField->GetValue();
    fptwo = fopen("Bibek.dat", "rb+");
    rewind(fptwo);
    while (fread(&a, sizeof(a), 1, fptwo) == 1) {
        if (a.id == wxAtoi(str)) {
            //std::string msg = "Book Available, Name : " + a.name + "Rack No. : " + a.rackno + "Delete?";
            found = true;
            
        }
    }

    if (found) {
      wxMessageDialog *dialo = new wxMessageDialog(NULL, wxT("Book Available, Delete?"), wxT("Info"), 
        wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
        if (dialo->ShowModal() == wxID_YES) {
            fpthree = fopen("test.dat", "wb+");
            rewind(fptwo);
            while (fread(&a, sizeof(a), 1, fptwo) == 1) {
                if (a.id != wxAtoi(str)) {
                    fseek(fpthree, 0, SEEK_CUR);
                    fwrite(&a, sizeof(a), 1, fpthree);
                }
            }
            fclose(fptwo);
            fclose(fpthree);
            remove("Bibek.dat");
            rename("test.dat", "Bibek.dat");
            fptwo = fopen("Bibek.dat", "rb+");    //we want to delete
            fclose(fptwo);
            if (found == true) {
                wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Deleted Sucessfully."), wxT("Info"), wxOK | wxICON_EXCLAMATION);
                dial->ShowModal();
            }
            EndModal(666);
        }
    } else {
      wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No Book found, Try Again?"), wxT("Info"), wxOK | wxICON_EXCLAMATION);
      dial->ShowModal();
    }   
}


/*
 * cancelButtonClick
 */
void DeleteBookDialog::cancelButtonClick(wxCommandEvent& event)
{
	EndModal(true);
}
