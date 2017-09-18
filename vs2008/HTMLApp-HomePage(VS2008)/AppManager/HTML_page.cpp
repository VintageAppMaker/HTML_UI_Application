#include "stdafx.h"
#include "HTML_page.h"
#include "AppManager.h"
#include "AppManagerDlg.h"

static int nLines = 0;
    
void  Read_MessageFromPage(int nPage, char* msg)
{

}

void  Read_ListFromPage(int nPage, char* msg)
{

}

void  Write_MessageToPage (int nPage, char* msg)
{
    // BOARD_%d �������� HTML���� �������� ����Ѵ�.
	CString BoardName;
	BoardName.Format("BOARD_%d", nPage );
    CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	CWebPage page = dlg->m_pMainView->m_CurPage;

    page.FindElement ( BoardName.GetBuffer(0), 0 );
	page.WriteElement(msg);	
    
}

// Line ������ Text�� �߰���Ų��.
static CString sWriteBuffer = "";

int ClearHTMLText()
{
    sWriteBuffer = "";
    return 0;
}

int AddHTMLText(char* msg)
{
    sWriteBuffer += msg;
    sWriteBuffer += "\r\n";

    return 0;	    
}

// �Էµ� ���ڿ��� Board�� �߰��Ѵ�.
int AttachHTMLTextToBoard(int nPage)
{
    Write_MessageToPage(nPage, sWriteBuffer.GetBuffer( 0 ) );
    sWriteBuffer = "";
    return 0;
}

void  Write_ListToPage(char* msg)
{
	// HTML ITem ������ �� ���Ƶ� ������ �� ���̴�.
    const int MAX_COUNT = 5000;
	if(nLines > MAX_COUNT)	Erase_ListOnPage( ); // nLines�� ����ƴ϶�.. DIV�� ó�� �̸��̴�.
	if(nLines == 0)	        nLines += 1;
		
	// LIST_%d �������� HTML���� �������� ����Ѵ�.
	CString BoardName;
	BoardName.Format("LIST_%d", nLines );
    CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	CWebPage page = dlg->m_pMainView->m_CurPage;

    page.FindElement ( BoardName.GetBuffer(0), 0 );

	CString str;
		
	str += "<LI>";
    str += CString(msg);
	str += "</LI>";
    
	nLines++;
	CString str2;
    str2.Format("<DIV id = 'LIST_%d'></DIV>", nLines);
	str += str2;
    
	page.WriteElement(str);    		
}

void  Erase_MessageOnPage (int nPage)
{
    
}


void  Erase_ListOnPage()
{
    int nPage = 1;
    // LIST_%d �������� HTML���� �������� ����Ѵ�.
	CString BoardName;
	BoardName.Format("LIST_%d", nPage );
    CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	CWebPage page = dlg->m_pMainView->m_CurPage;

    page.FindElement ( BoardName.GetBuffer(0), 0 );
	page.WriteElement(" "); 
	nLines = 0;
	
}

// �б� ũ�⸦ 1�ް��� �����Ѵ�.
const int MAX_BUF_READ = 1024 * 500;
char value[MAX_BUF_READ] = {0,};    
char* Read_ValueItem(int nPage, char* Item)
{
    CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	CWebPage page = dlg->m_pMainView->m_CurPage;

    page.FindElement ( Item, 0 );

    CString str = "";
    if (nPage){
	    str = page.ReadInputElement();
    } else {
        str = page.ReadTextElement();
    } 
	
    strcpy(value, str.GetBuffer(0));
    return value;
}

int   Write_ValueItem (int nPage, char* Item, char* msg)
{
    
    CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	CWebPage page = dlg->m_pMainView->m_CurPage;

    page.FindElement ( Item, 0 );
	
    if(nPage){
        page.WriteInputElement(msg);	        
    } else {
        page.WriteTextElement(msg
        );
    }

	return 0;
}
 
int   Erase_ValueItem (int nPage, char* Item)
{
    CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	CWebPage page = dlg->m_pMainView->m_CurPage;

    page.FindElement ( Item, 0 );
	page.WriteInputElement(" ");	

	return 0;
} 

int  ExcuteJScript(char* fnName, char* pParam)
{
    
	CAppManagerDlg* dlg = (CAppManagerDlg*)AfxGetApp()->m_pMainWnd;
	CWebPage page = dlg->m_pMainView->m_CurPage;
	
	CStringArray args;
	CString strArgs(pParam),strArg;
	while(!(strArg = GetNextToken(strArgs,",")).IsEmpty())
	{
		args.Add(strArg);
	}
	
	if(!page.CallJScript(fnName ,args))
	{
		AfxMessageBox("JScript Excution Error");
        return 0;
	}

	return 1;
}
