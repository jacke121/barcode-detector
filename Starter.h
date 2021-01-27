// Starter.h : main header file for the STARTER DLL
//

#if !defined(AFX_STARTER_H__AF29C9AF_EA18_4B72_A11C_667186A0D1E2__INCLUDED_)
#define AFX_STARTER_H__AF29C9AF_EA18_4B72_A11C_667186A0D1E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Barcode.h"
#include "BarcodeDetector.h"

/////////////////////////////////////////////////////////////////////////////
// CStarterApp
// See Starter.cpp for the implementation of this class
//

class CStarterApp : public CWinApp
{
public:
	CStarterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStarterApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CStarterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTER_H__AF29C9AF_EA18_4B72_A11C_667186A0D1E2__INCLUDED_)
