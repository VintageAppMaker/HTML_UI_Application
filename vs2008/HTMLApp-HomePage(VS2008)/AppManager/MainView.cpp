// MainView.cpp : implementation file
//

#include "stdafx.h"
#include "AppManager.h"
#include "AppManagerDlg.h"

#include "MainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainView

IMPLEMENT_DYNCREATE(CMainView, CHtmlView)

CMainView::CMainView()
{
	//{{AFX_DATA_INIT(CMainView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMainView::~CMainView()
{
}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainView, CHtmlView)
	//{{AFX_MSG_MAP(CMainView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainView diagnostics

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CMainView member function
CMainView* CMainView::GetHtmlView()
{
	CMainView* pView = new CMainView;
	return pView;
}


BOOL CMainView::CreateWnd(CRect rcWnd, CWnd *pParent)
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE;
	LPCTSTR lpWndCls;
	lpWndCls = AfxRegisterWndClass(0);
	BOOL bRet = CHtmlView::Create(NULL, lpWndCls, dwStyle, rcWnd, pParent, NULL);
	return bRet;
}

// ���� ��θ� �߰� ó��>2007-08-28
static CString GetCurPath()
{
    const char* WATCH_MODULENAME = "AppLayer.dll";
    HMODULE hh = GetModuleHandle((CString)WATCH_MODULENAME);
	if ( hh == NULL ) return "";
        
    // �ڵ鰪�� �������� NULL ��� �ڵ鰪�� �Է�
    TCHAR FILENAME[MAX_PATH] = {0,};
    GetModuleFileName(hh, FILENAME, MAX_PATH); 
    
	CString str = FILENAME;
	str.MakeUpper();
	str.Replace("APPLAYER.DLL", "");
	return str;
}

/////////////////////////////////////////////////////////////////////////////
// CMainView message handlers

void CMainView::OnDocumentComplete(LPCTSTR lpszURL) 
{
    m_CurPage.SetDocument( GetHtmlDocument() );

    CString url     = lpszURL;
    CString cmd     = "";
	int     nIndx   = 0;

    // ��û������ �Ľ�
	url.MakeUpper();
	nIndx = url.Find(".DLL");
    
	if(nIndx != -1) {
	    CString s;
	    s = url.Mid(nIndx + 5);
        s.Replace(".HTML", "");

        // Ŀ�ǵ� �̺�Ʈ ó��
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnPageEnd( (char*)s.GetBuffer(0) );
    }

    // DLL �ִ� ����� ���ϵ� ó�� 
	url.MakeUpper();
	nIndx = url.Find( GetCurPath() );
    
	if(nIndx != -1) {
	    CString s;
		url.Replace(GetCurPath(), "");
	    s = url;
        s.Replace(".HTML", "");
        
        // Ŀ�ǵ� �̺�Ʈ ó��
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnPageEnd( (char*)s.GetBuffer(0) );
    }

        

    CHtmlView::OnDocumentComplete(lpszURL);
}

void CMainView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel) 
{
	
    //////////////////////////////////////////////
    // ���ڿ� ����:
    // APP_CMD|��������|���|�Ķ����
    //////////////////////////////////////////////
    const char* TOKEN = "APP_CMD|";
    CString url     = lpszURL;
    CString cmd     = "";
    
    int nIndx = url.Find( TOKEN );
	
    if (nIndx != -1 ){
		
        // ����¡ ���
        *pbCancel = true;
        
        // Ŀ�ǵ� �Ľ�
        cmd = url.Right( 
            url.GetLength() - ( nIndx +  strlen(TOKEN) ) 
        );                         
        
        // Ŀ�ǵ� �̺�Ʈ ó��
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnRequestCMD ( (char*)cmd.GetBuffer(0) );
        return;
    }

    // ��û������ �Ľ�
	url.MakeUpper();
	nIndx = url.Find(".DLL");
    
	if(nIndx != -1) {
	    CString s;
	    s = url.Mid(nIndx + 5);
        s.Replace(".HTML", "");

        // Ŀ�ǵ� �̺�Ʈ ó��
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnPageStart( (char*)s.GetBuffer(0) );
    }
    
	// DLL �ִ� ����� ���ϵ� ó�� 
	nIndx = url.Find( GetCurPath() );
    if(nIndx != -1) {
	    CString s;
		url.Replace(GetCurPath(), "");
	    s = url;
        s.Replace(".HTML", "");
        
        // Ŀ�ǵ� �̺�Ʈ ó��
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnPageStart( (char*)s.GetBuffer(0) );
    }
        

    CHtmlView::OnBeforeNavigate2(lpszURL, nFlags,	
        lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel
    );

}
