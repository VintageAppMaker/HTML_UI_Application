#if !defined(AFX_MAINVIEW_H__9DFEF1B9_FC71_43B6_B89B_AF900DF35C11__INCLUDED_)
#define AFX_MAINVIEW_H__9DFEF1B9_FC71_43B6_B89B_AF900DF35C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MainView html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

#include "WebPage.h"
#include "CPage.h"

class MainView : public CHtmlView
{
protected:
	MainView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MainView)

// html Data
public:
	//{{AFX_DATA(MainView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
    static MainView* GetHtmlView();
	BOOL   CreateWnd(CRect rcWnd, CWnd* pParent);

    CWebPage m_CurPage;
    CPageUI  m_StateManager;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MainView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(MainView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINVIEW_H__9DFEF1B9_FC71_43B6_B89B_AF900DF35C11__INCLUDED_)
