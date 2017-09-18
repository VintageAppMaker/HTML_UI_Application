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

// 현재 경로명 추가 처리>2007-08-28
static CString GetCurPath()
{
    const char* WATCH_MODULENAME = "AppLayer.dll";
    HMODULE hh = GetModuleHandle((CString)WATCH_MODULENAME);
	if ( hh == NULL ) return "";
        
    // 핸들값을 가져오면 NULL 대신 핸들값을 입력
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

    // 요청페이지 파싱
	url.MakeUpper();
	nIndx = url.Find(".DLL");
    
	if(nIndx != -1) {
	    CString s;
	    s = url.Mid(nIndx + 5);
        s.Replace(".HTML", "");

        // 커맨드 이벤트 처리
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnPageEnd( (char*)s.GetBuffer(0) );
    }

    // DLL 있는 경로의 파일도 처리 
	url.MakeUpper();
	nIndx = url.Find( GetCurPath() );
    
	if(nIndx != -1) {
	    CString s;
		url.Replace(GetCurPath(), "");
	    s = url;
        s.Replace(".HTML", "");
        
        // 커맨드 이벤트 처리
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnPageEnd( (char*)s.GetBuffer(0) );
    }

        

    CHtmlView::OnDocumentComplete(lpszURL);
}

void CMainView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel) 
{
	
    //////////////////////////////////////////////
    // 문자열 구성:
    // APP_CMD|페이지명|평션|파라메터
    //////////////////////////////////////////////
    const char* TOKEN = "APP_CMD|";
    CString url     = lpszURL;
    CString cmd     = "";
    
    int nIndx = url.Find( TOKEN );
	
    if (nIndx != -1 ){
		
        // 브라우징 취소
        *pbCancel = true;
        
        // 커맨드 파싱
        cmd = url.Right( 
            url.GetLength() - ( nIndx +  strlen(TOKEN) ) 
        );                         
        
        // 커맨드 이벤트 처리
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnRequestCMD ( (char*)cmd.GetBuffer(0) );
        return;
    }

    // 요청페이지 파싱
	url.MakeUpper();
	nIndx = url.Find(".DLL");
    
	if(nIndx != -1) {
	    CString s;
	    s = url.Mid(nIndx + 5);
        s.Replace(".HTML", "");

        // 커맨드 이벤트 처리
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnPageStart( (char*)s.GetBuffer(0) );
    }
    
	// DLL 있는 경로의 파일도 처리 
	nIndx = url.Find( GetCurPath() );
    if(nIndx != -1) {
	    CString s;
		url.Replace(GetCurPath(), "");
	    s = url;
        s.Replace(".HTML", "");
        
        // 커맨드 이벤트 처리
        CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	    dlg->fnOnPageStart( (char*)s.GetBuffer(0) );
    }
        

    CHtmlView::OnBeforeNavigate2(lpszURL, nFlags,	
        lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel
    );

}
