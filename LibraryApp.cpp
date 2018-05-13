//---------------------------------------------------------------------------
//
// Name:        LibraryApp.cpp
// Author:      coderuth
// Created:     5/9/2018 12:23:29 AM
// Description: 
//
//---------------------------------------------------------------------------

#include "LibraryApp.h"
#include "LibraryForm.h"

IMPLEMENT_APP(LibraryFormApp)

bool LibraryFormApp::OnInit()
{
    LibraryForm* frame = new LibraryForm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int LibraryFormApp::OnExit()
{
	return 0;
}
