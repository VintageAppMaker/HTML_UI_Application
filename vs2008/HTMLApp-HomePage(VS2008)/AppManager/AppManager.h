// AppManager.h : main header file for the APPMANAGER application
//

#if !defined(AFX_APPMANAGER_H__7DA5712F_1C8B_4F74_ACF4_17E814823796__INCLUDED_)
#define AFX_APPMANAGER_H__7DA5712F_1C8B_4F74_ACF4_17E814823796__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAppManagerApp:
// See AppManager.cpp for the implementation of this class
//

class CAppManagerApp : public CWinApp
{
public:
	CAppManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAppManagerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPMANAGER_H__7DA5712F_1C8B_4F74_ACF4_17E814823796__INCLUDED_)
