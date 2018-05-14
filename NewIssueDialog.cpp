///-----------------------------------------------------------------
///
/// @file      NewIssueDialog.cpp
/// @author    coderuth
/// Created:   5/13/2018 9:25:07 AM
/// @section   DESCRIPTION
///            NewIssueDialog class implementation
///
///------------------------------------------------------------------
#define RETURNTIME 15
#include "NewIssueDialog.h"
#include "Book.h"
#include <sstream>
#include <ctime>

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// NewIssueDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(NewIssueDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(NewIssueDialog::OnClose)
	EVT_BUTTON(ID_ISSUEBUTTON,NewIssueDialog::issueButtonClick)
	EVT_BUTTON(ID_OKBUTTON,NewIssueDialog::okButtonClick)
	EVT_BUTTON(ID_CANCELBUTTON,NewIssueDialog::cancelButtonClick)
END_EVENT_TABLE()
////Event Table End

NewIssueDialog::NewIssueDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

NewIssueDialog::~NewIssueDialog()
{
} 

void NewIssueDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	issueButton = new wxButton(this, ID_ISSUEBUTTON, _("Issue"), wxPoint(14, 74), wxSize(274, 25), 0, wxDefaultValidator, _("issueButton"));

	WxGrid1 = new wxGrid(this, ID_WXGRID1, wxPoint(16, 105), wxSize(273, 200));
	WxGrid1->SetDefaultColSize(173);
	WxGrid1->SetDefaultRowSize(25);
	WxGrid1->SetRowLabelSize(100);
	WxGrid1->SetColLabelSize(25);
	WxGrid1->CreateGrid(7,1,wxGrid::wxGridSelectCells);
	
	WxGrid1->SetRowLabelValue(0, _("Issue ID"));
    WxGrid1->SetRowLabelValue(1, _("Unissued Books")); //from wxSmith 
    WxGrid1->SetRowLabelValue(2, _("Book ID"));
    WxGrid1->SetRowLabelValue(3, _("Book Name")); //from wxSmith 
    WxGrid1->SetRowLabelValue(4, _("Student Name")); //from wxSmith 
    WxGrid1->SetRowLabelValue(5, _("Issued Date"));
    WxGrid1->SetRowLabelValue(6, _("Due Date"));
    
    WxGrid1->SetColLabelValue(0, _("Result"));
        
	studentField = new wxTextCtrl(this, ID_STUDENTFIELD, _(""), wxPoint(128, 48), wxSize(160, 21), 0, wxDefaultValidator, _("studentField"));

	idField = new wxTextCtrl(this, ID_IDFIELD, _(""), wxPoint(128, 25), wxSize(160, 19), 0, wxDefaultValidator, _("idField"));

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("Enter ID"), wxPoint(14, 27), wxDefaultSize, 0, _("WxStaticText2"));

	studentLabel = new wxStaticText(this, ID_STUDENTLABEL, _("Enter Student Name"), wxPoint(14, 48), wxDefaultSize, 0, _("studentLabel"));

	okButton = new wxButton(this, ID_OKBUTTON, _("OK"), wxPoint(213, 310), wxSize(75, 25), 0, wxDefaultValidator, _("okButton"));

	cancelButton = new wxButton(this, ID_CANCELBUTTON, _("Cancel"), wxPoint(129, 310), wxSize(81, 25), 0, wxDefaultValidator, _("cancelButton"));

	WxStaticBox1 = new wxStaticBox(this, ID_WXSTATICBOX1, _("Add Issue with ID"), wxPoint(4, 5), wxSize(293, 340));

	SetTitle(_("NewIssueDialog"));
	SetIcon(wxNullIcon);
	SetSize(8,8,313,380);
	Center();
	
	////GUI Items Creation End
}

void NewIssueDialog::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * WxButton1Click
 */
void NewIssueDialog::WxButton1Click(wxCommandEvent& event) {
	// insert your code here
}

/*
 * addIssueButtonClick
 */
void NewIssueDialog::addIssueButtonClick(wxCommandEvent& event) {
	// insert your code here
}

/*
 * cancelButtonClick
 */
void NewIssueDialog::cancelButtonClick(wxCommandEvent& event) {
	EndModal(true);
}

/*
 * issueButtonClick
 */
void NewIssueDialog::issueButtonClick(wxCommandEvent& event) {
    Book a, temp;
    FILE *fs;
    bool found;
    std::stringstream ss;
    wxString id = idField->GetValue();
    wxString name = studentField->GetValue();
    
    fs = fopen("Bibek.dat", "rb+");
    while (fread(&a, sizeof(a), 1, fs) == 1) {
        if (a.id == wxAtoi(id)) {
            found = true;
            temp = a;
        }
    }
    fclose(fs);
    
    fs = fopen("Issue.dat", "ab+");
    if (found) {
        FILE *fpt;
        fpt = fopen("Bibek.dat", "rb+");
        Book aone;
        while (fread(&aone, sizeof(aone), 1, fpt) == 1) {
            if (aone.id == temp.id) {
                temp.quantity = temp.quantity - 1;
                //std::string msg = "Book Available, Name : " + a.name + "Rack No. : " + a.rackno + "Delete?";
                fseek(fpt, -sizeof(aone), SEEK_CUR);      //  move one structure back     
                fwrite(&temp, sizeof(temp), 1, fpt);         //  Overwrite updated structure
                break;  
            }
        }
        fclose(fpt);
        //Book aone, tempone;
//        FILE *fptwo;
//        fptwo = fopen("Bibek.dat", "wb+");
//        while (fread(&aone, sizeof(aone), 1, fptwo) == 1) {
//            if (aone.id == temp.id) {
//                tempone = aone;
//                fseek(fptwo, -sizeof(aone), SEEK_CUR);      //  move one structure back     
//                tempone.quantity = tempone.quantity - 1;
//                fwrite(&tempone, sizeof(tempone), 1, fptwo);         //  Overwrite updated structure
//                break;  
//            }
//        }
//        fclose(fptwo);
        
        temp.issueID = getRandomID();
        
        wxCharBuffer bufferTwo = name.ToUTF8();
        strcpy(temp.stname, bufferTwo.data());
        
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        temp.issued.dd = t->tm_mday;
        temp.issued.mm = t->tm_mon + 1;
        temp.issued.yy = t->tm_year + 1900;

        temp.duedate.dd = temp.issued.dd + RETURNTIME;   //for return date
        temp.duedate.mm = temp.issued.mm;
        temp.duedate.yy = temp.issued.yy;
        
        if (temp.duedate.dd > 30) {
            temp.duedate.mm += temp.duedate.dd / 30;
            temp.duedate.dd -= 30;

        }
        if (temp.duedate.mm > 12) {
            temp.duedate.yy += temp.duedate.mm / 12;
            temp.duedate.mm -= 12;

        }
         
        fseek(fs, sizeof(temp), SEEK_END);
        fwrite(&temp, sizeof(temp), 1, fs);
        
        ss << temp.issueID;
        WxGrid1->SetCellValue(0, 0, _(ss.str()));
        ss.str(std::string());
        
        ss << temp.quantity;
        WxGrid1->SetCellValue(1, 0, _(ss.str()));
        ss.str(std::string());
        
        ss << temp.id;
        WxGrid1->SetCellValue(2, 0, _(ss.str()));
        ss.str(std::string());
        
        WxGrid1->SetCellValue(3, 0, _(temp.name));
        WxGrid1->SetCellValue(4, 0, _(temp.stname));
        
        ss << temp.issued.dd << "-" << temp.issued.mm << "-" << temp.issued.yy;
        WxGrid1->SetCellValue(5, 0, _(ss.str()));
        ss.str(std::string());
        
        ss << temp.duedate.dd << "-" << temp.duedate.mm << "-" << temp.duedate.yy;
        WxGrid1->SetCellValue(6, 0, _(ss.str()));
        ss.str(std::string());
        
        fclose(fs);
    
    } else {
        wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No Book found, Try Again?"), wxT("Info"), wxOK | wxICON_EXCLAMATION);
        dial->ShowModal();
    }
}

/*
 * okButtonClick
 */
void NewIssueDialog::okButtonClick(wxCommandEvent& event) {
	EndModal(666);
}

int NewIssueDialog::getRandomID() {
    srand(time(NULL)); 
    return (rand() % 100000) + 1;
}
