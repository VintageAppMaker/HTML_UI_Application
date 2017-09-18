// AppManagerDlg.h : header file
//

#if !defined(AFX_APPMANAGERDLG_H__F15F522F_2200_4B47_9BC3_0F2A13535BAA__INCLUDED_)
#define AFX_APPMANAGERDLG_H__F15F522F_2200_4B47_9BC3_0F2A13535BAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAppManagerDlg dialog

#include "MainView.h"
#include "HTML_UI_API.h"
#include "HTML_page.h"


class CAppManagerDlg : public CDialog
{
// Construction
public:
	CAppManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAppManagerDlg)
	enum { IDD = IDD_APPMANAGER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	HICON m_hIcon;
    CBitmapButton m_XButton;
    CBitmapButton m_MinButton;

	// Generated message map functions
	//{{AFX_MSG(CAppManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnbtnClose();
	afx_msg void OnBtnMiniMize();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    CMainView *m_pMainView;
    HINSTANCE  h;

    // 다이알로그 UI관련
    void ScreenAlphaBlend(int nAlpha);
   
    
    // HTML UI 관련
    void InitWidget();

    // DLL 처리 관련
    int  LoadMainDLL(char* fname);

    // DLL Export Function
    typedef int (*PAGESTART)(char*);
    typedef int (*PAGEEND)(char* );
    typedef int (*APPSTART)(HTMLAPI*);
    typedef int (*APPEND)(void);
    typedef int (*REQUEST)(char* );
        
    PAGESTART fnOnPageStart;
    PAGEEND   fnOnPageEnd;

    APPSTART  fnOnAPPStart;
    APPEND    fnOnAPPEnd;
    REQUEST   fnOnRequestCMD; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPMANAGERDLG_H__F15F522F_2200_4B47_9BC3_0F2A13535BAA__INCLUDED_)
