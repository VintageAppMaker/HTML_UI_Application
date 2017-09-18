// AppManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AppManager.h"
#include "AppManagerDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// 색상 및 UI 관련
#define WS_EX_LAYERED           0x00080000
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppManagerDlg dialog

CAppManagerDlg::CAppManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppManagerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppManagerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAppManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppManagerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAppManagerDlg, CDialog)
	//{{AFX_MSG_MAP(CAppManagerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnbtnClose)
	ON_BN_CLICKED(IDC_BUTTON2, OnBtnMiniMize)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppManagerDlg member function

// 투명효과인데..?
void CAppManagerDlg::ScreenAlphaBlend(int nAlpha)
{

	HWND hwnd = this->m_hWnd;

	OSVERSIONINFO vi;
	vi.dwOSVersionInfoSize = sizeof(vi);
	GetVersionEx(&vi);
	if ( vi.dwPlatformId == VER_PLATFORM_WIN32_NT && vi.dwMajorVersion >= 5 ) 
	{
		SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		HMODULE mh;
		mh = GetModuleHandle("user32.dll");
		typedef bool (__stdcall *SLWA)(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
		SLWA SetLWA = reinterpret_cast<SLWA>(GetProcAddress(mh, "SetLayeredWindowAttributes"));
		SetLWA(hwnd, 0, nAlpha, LWA_ALPHA);
	}
}

// 윈도우 위젯 초기화
void CAppManagerDlg::InitWidget()
{
    m_pMainView = CMainView::GetHtmlView();

    // 크기 설정
    CRect rcDlgs;
	GetDlgItem(IDC_STATIC2)->GetWindowRect(rcDlgs);
	ScreenToClient(rcDlgs);
        
	m_pMainView = CMainView::GetHtmlView();
	
    if (!m_pMainView->CreateWnd(rcDlgs, this)) {
		TRACE0("Error\n");
		return;
	}

    ScreenAlphaBlend(234);
    
    CString strNavigate; 
    strNavigate = CString("res://AppLayer.dll/") + CString("START.HTML");
    m_pMainView->Navigate2(strNavigate);
    
}


// DLL 처리 관련
int CAppManagerDlg::LoadMainDLL(char* fname)
{
    h = LoadLibrary(fname);
            
    fnOnPageStart  = NULL;
    fnOnPageEnd    = NULL;

    fnOnAPPStart   = NULL;
    fnOnAPPEnd     = NULL;
    fnOnRequestCMD = NULL; 

    if(h == NULL) 
        return 0;
    
    fnOnPageStart = (PAGESTART)GetProcAddress(h, "OnPageReadStart");
    if( fnOnPageStart == NULL) 
        return 0;
    
    fnOnPageEnd = (PAGEEND)GetProcAddress(h, "OnPageReadEnd");
    if( fnOnPageEnd == NULL) 
        return 0;
    
    fnOnAPPStart = (APPSTART)GetProcAddress(h, "OnApplicationStart");
    if( fnOnAPPStart == NULL) 
        return 0;

    fnOnAPPEnd = (APPEND)GetProcAddress(h, "OnApplicationTerminate");
    if( fnOnAPPEnd == NULL) 
        return 0;

    fnOnRequestCMD = (REQUEST)GetProcAddress(h, "OnRequestCMD");
    if( fnOnRequestCMD == NULL) 
        return 0;
 
    // HTML API 초기화
    HTMLAPI HTML_API_TABLE;
    HTML_API_TABLE.fnDisplayPage         = NULL;
    HTML_API_TABLE.fnErase_MessageOnPage = Erase_MessageOnPage;
    HTML_API_TABLE.fnErase_ListOnPage    = Erase_ListOnPage;  
    HTML_API_TABLE.fnRead_ValueItem      = Read_ValueItem;
    HTML_API_TABLE.fnWrite_MessageToPage = Write_MessageToPage;
    HTML_API_TABLE.fnWrite_ValueItem     = Write_ValueItem;
    HTML_API_TABLE.fnWrite_ListToPage    = Write_ListToPage;
    
    HTML_API_TABLE.fnAddHTMLText         = AddHTMLText;
    HTML_API_TABLE.fnAttachTextToBoard   = AttachHTMLTextToBoard;
    HTML_API_TABLE.fnClearHTMLText       = ClearHTMLText; 
    HTML_API_TABLE.fnExcuteJScript       = ExcuteJScript; 
     
    fnOnAPPStart(&HTML_API_TABLE);
    
    return 1;
}

/////////////////////////////////////////////////////////////////////////////
// CAppManagerDlg message handlers

BOOL CAppManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_XButton.AutoLoad(IDC_BUTTON1, this);
    m_MinButton.AutoLoad(IDC_BUTTON2, this);

    SetWindowText("Application Browser");
        
    char* DLL_NAME = "AppLayer.dll";
    if ( !LoadMainDLL(DLL_NAME) ) {
        AfxMessageBox("DLL이 없습니다. 프로그램을 종료합니다.");
        EndDialog( 0 );

        return TRUE;
    }
    InitWidget();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAppManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAppManagerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAppManagerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAppManagerDlg::OnbtnClose() 
{
    EndDialog(0);	
}

void CAppManagerDlg::OnBtnMiniMize() 
{
    this->CloseWindow();	
}

void CAppManagerDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
    ReleaseCapture();
    DefWindowProc(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	
	CDialog::OnMouseMove(nFlags, point);
}
