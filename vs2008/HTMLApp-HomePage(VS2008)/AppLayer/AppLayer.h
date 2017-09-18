// AppLayer.h : main header file for the APPLAYER DLL
//

#if !defined(AFX_APPLAYER_H__22FAEBBB_4C18_4811_8B1D_A3554C5E8236__INCLUDED_)
#define AFX_APPLAYER_H__22FAEBBB_4C18_4811_8B1D_A3554C5E8236__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAppLayerApp
// See AppLayer.cpp for the implementation of this class
//

class CAppLayerApp : public CWinApp
{
public:
	CAppLayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppLayerApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAppLayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLAYER_H__22FAEBBB_4C18_4811_8B1D_A3554C5E8236__INCLUDED_)
