//---------------------------------------------------------------------------
//
// Name:        LibraryApp.h
// Author:      coderuth
// Created:     5/9/2018 12:23:29 AM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __LIBRARYFORMApp_h__
#define __LIBRARYFORMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class LibraryFormApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
