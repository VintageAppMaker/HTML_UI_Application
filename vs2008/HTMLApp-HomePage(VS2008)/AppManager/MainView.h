#if !defined(AFX_MAINVIEW_H__0B3A5CBD_CD15_4140_B2E5_9AEBD728F8B4__INCLUDED_)
#define AFX_MAINVIEW_H__0B3A5CBD_CD15_4140_B2E5_9AEBD728F8B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainView html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

#include "WebPage.h"

class CMainView : public CHtmlView
{
protected:
	CMainView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMainView)

// html Data
public:
	//{{AFX_DATA(CMainView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
    static CMainView* GetHtmlView();
    BOOL   CreateWnd(CRect rcWnd, CWnd* pParent);


// Operations
public:
    CWebPage m_CurPage;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainView)
	public:
	//virtual void OnInitialUpdate();
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMainView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINVIEW_H__0B3A5CBD_CD15_4140_B2E5_9AEBD728F8B4__INCLUDED_)
