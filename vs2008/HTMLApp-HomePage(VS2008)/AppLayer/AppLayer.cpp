// AppLayer.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "AppLayer.h"
#include "HTML_UI_API.h"
#include "CHTMLPage.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CAppLayerApp

BEGIN_MESSAGE_MAP(CAppLayerApp, CWinApp)
	//{{AFX_MSG_MAP(CAppLayerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAppLayerApp construction
CAppLayerApp::CAppLayerApp()
{
    // DLL 초기화 코드 
    
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAppLayerApp object
CAppLayerApp theApp;

// 페이지 상태관리 매니저 (구현 클래스를 Assign 한다.)
CPageUI*    m_StateManager = new CHTMLPage();
static bool m_IsRegistered = true;

/////////////////////////////////////////////////////////////////////////////
//  Event Function List


// 페이지를 읽기전의 URL
extern "C" __declspec(dllexport)
int OnPageReadStart(char* PageURL)
{

    if(m_StateManager->FindStateByName (PageURL)  == -1){
        m_IsRegistered = false;
    } else {
        m_IsRegistered = true;
    }

    FSM_EVT e;
    e.EVT    = CPageUI::PAGE_REQUEST_EVT;
	e.pParam = (DWORD)PageURL;   
    m_StateManager->DoEvent(e);

    return 0;
}

// 페이지 Read 완료
extern "C" __declspec(dllexport)
int OnPageReadEnd(char* PageURL)
{
    if( !m_IsRegistered ) return 1;
    
    FSM_EVT e;
    e.EVT    = CPageUI::PAGE_READEND_EVT;
	e.pParam = (DWORD)PageURL;   
    m_StateManager->DoEvent(e);
    
    return 0;
}

// Request CMD 발생
extern "C" __declspec(dllexport)
int OnRequestCMD(char* cmd)
{
    FSM_EVT e;
    e.EVT    = CPageUI::INPUT_CMD_EVT;
    e.pParam = (DWORD)cmd;   
    m_StateManager->DoEvent(e);

    return 0;
}


// Application 시작
extern "C" __declspec(dllexport)
int OnApplicationStart(HTMLAPI* tbl)
{
    // HTML API관련 초기화 작업
    CopyMemory( &HTML_API_TABLE, tbl, sizeof(HTML_API_TABLE) );
    return 0;
}

// Application 종료
extern "C" __declspec(dllexport)
int OnApplicationTerminate()
{
    return 0;
}


