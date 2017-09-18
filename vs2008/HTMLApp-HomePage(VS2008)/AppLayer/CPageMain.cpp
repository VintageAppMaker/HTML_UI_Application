#include "stdafx.h"
#include "CPageMain.h"
#include "util.h"
/*
    참고: 모든 Page의 Handler class를 CPageMain으로 했다. 
	이유는 ...

    JScript를 메인으로 하고 DLL에서는 API를 제공하기 위해서임이다.
	(JavaScript Main Program)
*/

//-----------------------------------------------------------------------------
// 메인엔진 클래스들
static TDBMaster* m_Db = NULL;
static bool m_DB_State = false;  
static char m_DBName[MAX_PATH];

// COL의 맥스사이즈를 Fix해놓았다. 50K 정도면 될것이다. 
const int MAX_TEXT_SIZE = 1024 * 50;
const int MAX_COL_SIZE  = 30;
char col[MAX_COL_SIZE][MAX_TEXT_SIZE];


// 현재 경로명 추가 처리 2007-08-28
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

//-----------------------------------------------------------------------------
// 핸들러 등록
//-----------------------------------------------------------------------------
CPageMain::CPageMain()
{
    CPageUI::CPageUI();   
    
	// DB 생성
	// vs2008로포팅하면서 생성자가 무의미해짐.
	//m_Db = new TDBEng();
}
   
//-----------------------------------------------------------------------------
// 핸들러 정의 (사용자정의 영역)
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// END 핸들러
void CPageMain::OnPageReadEnd(FSM_EVT e)
{
    // 요청한 커맨드 분석
    char* cmdParam = (char*)e.pParam;

	// 메인페이지에서 전역적인 엔진을 초기화 한다. - 좋지 아니하다. 
    // InitSessionModule();

	//
	if(m_Db == NULL) m_Db = new TDBEng();

	if(strcmp(cmdParam, "START") == 0){
		CString str = "file://";
		str = str + GetCurPath() + "main.html";
		UI_EXCUTE_SCRIPT("GoURL", str.GetBuffer( 0 ));
    } 	
 
}
//-----------------------------------------------------------------------------
// Page Close 핸들러
void CPageMain::OnPageClose(FSM_EVT e)
{

}

//-----------------------------------------------------------------------------
// CMD 핸들러
void CPageMain::OnPageCMD(FSM_EVT e)
{
    // 다른 페이지일 경우, 요청페이지 상태로 이동
	char* cmdPage  = NULL;
	char* cmdFunc  = NULL;
	char* cmdParam = NULL;

    // 문자열 파싱
    int rst = GetParamString( 
        (char*)e.pParam,
        &cmdPage,
        &cmdFunc,
        &cmdParam
    );   
    if( !rst ) return;

    RunFunctionByCMD(cmdFunc, cmdParam);
}

// 커맨드 문자열와 매칭되는 함수를 실행시켜준다.
int  CPageMain::RunFunctionByCMD(char* fName, char* pParam)
{
    int indx = -1;
    typedef void (CPageMain::*TFUNC )(char*);
    typedef struct tagFUNCINFO{
        char*    PAGE_NAME;
        TFUNC    fnState; 
    } FUNCINFO;
    
	
	// RES:// 처리 추가
	int nLen = strlen(pParam);
	if(pParam[nLen -  1] == '/') 
		pParam[nLen - 1] = ' ';

	// 문자열별 함수를 실행시킨다.
	// API 테이블
    FUNCINFO st[] ={
        
		// DB API
		{"ConnectDB",    &CPageMain::On_API_ConnectDB},
		{"SQL",          &CPageMain::On_API_SQL},
		{"GetRow",       &CPageMain::On_API_GetRow},
		{"GetValue",     &CPageMain::On_API_GetValue},
        
		// File API
		{"OpenFile",     &CPageMain::On_API_OpenFile},
		{"CreateFile",   &CPageMain::On_API_CreateFile},
		{"CloseFile",    &CPageMain::On_API_CloseFile},
		{"ReadFile",     &CPageMain::On_API_ReadFile},
		{"WriteFile",    &CPageMain::On_API_WriteFile},
		{"DeleteFile",   &CPageMain::On_API_DeleteFile},
		{"CopyFile",     &CPageMain::On_API_CopyFile},
		{"GetFileSize",  &CPageMain::On_API_GetFileSize},

		// system
		{"System",       &CPageMain::On_API_System},
		{"excute",       &CPageMain::On_API_excute},


		// Folder API
		{"GetCurFolder", &CPageMain::On_API_GetCurFolder},
		{"SetFolder",    &CPageMain::On_API_SetFolder},
		{"SearchFolder", &CPageMain::On_API_SearchFolder},
		{"CreateFolder", &CPageMain::On_API_CreateFolder},

		// CGI API
		{"CGICall", &CPageMain::On_API_CGICall}		

    };

    for(int i = 0; i < sizeof(st) / sizeof(st[0]); i++ ){
        if ( strcmp(st[i].PAGE_NAME, fName) == 0 ){
            TFUNC a = st[i].fnState;
            ( this->*(a) )(pParam);
        }
    }   



    return 0;
}

//-----------------------------------------------------------------------------
// DB API 구현

// DB 연결
void CPageMain::On_API_ConnectDB(char* pParam)
{
    CString sDBNAME = GetCurPath() + pParam;
	int nRst = 1;
	
	// connect 반복시 락업걸림. diconnect 자동처리함.
	if( strcmp(m_DBName, sDBNAME) != 0){ 
	    if(m_DB_State) 
			m_Db->disconnect();
		nRst =  m_Db->connect(sDBNAME.GetBuffer(0));
	    strcpy(m_DBName, sDBNAME);
        m_DB_State = true;
    }
    
    CString sRst;
	if(nRst){
	    sRst = "true";
	} else{
		sRst = "false";     
	}

	UI_WRITE_ITEM(0 , "RESULT", sRst.GetBuffer(0) );
}

// SQL 실행 
void CPageMain::On_API_SQL(char* pParam)
{
    
	/* URL 형식으로 하니 엔터값이 사라지더라..*/
	// RESULT.value = Query; 처리함.
	CString str  = UI_READ_ITEM(0, "RESULT");
	CString qry  = str;

	//CString qry  = pParam;
	//qry.Replace("%20", " ");

	ZeroMemory(col, sizeof(col));
	
	m_Db->Clear();
    *m_Db << qry.GetBuffer(0);
    int nRst =  m_Db->SQL();
    
	for(int i = 0; i <MAX_COL_SIZE; i++ ){
	    m_Db->SetColData(i + 1, (char**)(&col[i]), MAX_TEXT_SIZE);    
	}

	CString sRst;
	if(nRst){
	    sRst = "true";
	} else{
		sRst = "false";     
	}

	UI_WRITE_ITEM(0 , "RESULT", sRst.GetBuffer(0) );
}


// Row 값 가져오기 
void CPageMain::On_API_GetRow(char* pParam)
{
    int nRst = m_Db->GetRow();

	CString sRst;
	if(nRst == TDBMaster::RECORD_END){
	    sRst = "end";
	} else{
		sRst = "continue";     
	}

	UI_WRITE_ITEM(0 , "RESULT", sRst.GetBuffer(0) );
}

// 컬럼 인덱스로 값가져오기 
void CPageMain::On_API_GetValue(char* pParam)
{
	int nIndx = atoi(pParam);
	if(nIndx > MAX_COL_SIZE - 1 ) return;
	if(nIndx < 0                ) return;

    UI_WRITE_ITEM(0 , "RESULT", col[nIndx] );
}

//-----------------------------------------------------------------------------
// File API 구현

// 읽기위해 열기
void CPageMain::On_API_OpenFile(char* pParam)
{
    CString str = pParam;
    str.Replace("%20", " ");
    
	CFile* f = new CFile();
	int nRst = f->Open(str, CFile::modeReadWrite);

	char sFilePointerAddr [30];
    if(!nRst){  
		strcpy(sFilePointerAddr, "0");
    } else {
	    ltoa((long)f, sFilePointerAddr, 10);
	}	
    
	UI_WRITE_ITEM(0 , "FileRESULT", sFilePointerAddr );	    
}

// 파일생성(쓰기용)
void CPageMain::On_API_CreateFile(char* pParam)
{
    CString str = pParam;
    str.Replace("%20", " ");

	CFile* f = new CFile();
	f->Open(str, CFile::modeWrite | CFile::modeCreate);

    char sFilePointerAddr [30];
    ltoa((long)f, sFilePointerAddr, 10);
	UI_WRITE_ITEM(0 , "FileRESULT", sFilePointerAddr );	
}

// 파일닫기
void CPageMain::On_API_CloseFile(char* pParam)
{
    CFile* f = NULL;
	f = (CFile*)atol(pParam);
	if(f != NULL){
		f->Close();
	}
}

// File 읽기
void CPageMain::On_API_ReadFile(char* pParam)
{
    CFile* f = NULL;
    CString str = "";

	const int nReadSize = 1024 *5;
	char pReadBuf[nReadSize];
	f = (CFile*)atol(pParam);
	if(f != NULL){
	    int nRead = 0;
		while(1){
			ZeroMemory(pReadBuf, nReadSize);
			nRead= f->Read(pReadBuf, nReadSize);
			if(nRead < 1) break;
			str += pReadBuf;
		}	
	}

    UI_WRITE_ITEM(0 , "FileREAD", str.GetBuffer(0) );	
}

// File 쓰기
void CPageMain::On_API_WriteFile(char* pParam)
{
    CFile* f = NULL;
    CString str  = UI_READ_ITEM(0, "FileWrite");

	f = (CFile*)atol(pParam);
	if(f != NULL){
	    f->Write(str.GetBuffer(0), str.GetLength());		
	}
}

// File 지우기 
void CPageMain::On_API_DeleteFile(char* pParam)
{
    CString str  = UI_READ_ITEM(0, "FileTarget");
	DeleteFile(str);	
}

// File 복사 
void CPageMain::On_API_CopyFile(char* pParam)
{
    CString str   = UI_READ_ITEM(0, "FileTarget");
	CString str2  = UI_READ_ITEM(0, "FileSource");

	CopyFile(str2, str, true);
}

// File 크기 얻기 
void CPageMain::On_API_GetFileSize(char* pParam)
{
    CFile* f = NULL;
    
	f = (CFile*)atol(pParam);

	int nSize = 0;
	if(f != NULL){
	    nSize = f->GetLength();
	}

	CString str;
	str.Format("%d", nSize);
	UI_WRITE_ITEM(0 , "FileResult", str.GetBuffer(0) );	
}

//-----------------------------------------------------------------------------
// System API 구현
void CPageMain::On_API_System(char* pParam)
{
    system(pParam);	
}

void CPageMain::On_API_excute(char* pParam)
{
    
	char CurDir[MAX_PATH];
    GetCurrentDirectory (MAX_PATH, CurDir);
    
	CString str = pParam;
    str.Replace("%20", " ");
	ShellExecute(NULL, "open", str.GetBuffer(0), CurDir, NULL, SW_SHOW);    
}


//-----------------------------------------------------------------------------
// Folder API 구현
void CPageMain::On_API_GetCurFolder(char* pParam)
{
    char CurDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, CurDir);
	UI_WRITE_ITEM(0 , "FolderRESULT", CurDir );	
}

void CPageMain::On_API_SetFolder(char* pParam)
{
	CString str  = UI_READ_ITEM(0, "FolderIn");
	SetCurrentDirectoryA(str.GetBuffer(0));
	UI_WRITE_ITEM(0 , "FolderRESULT", str.GetBuffer(0) );	
}


// File Search와 화면 출력하기 
static void SearchFileOrFolder(char* CurDir, int type)
{
    enum {
        SRC_FOLDER = 0,
        SRC_FILES
	};

    HANDLE hSrch;
    WIN32_FIND_DATA wfd;
	
    BOOL bResult=TRUE;
	char Path[MAX_PATH];

	CString sCurDir = CurDir;
	sCurDir.Replace("%20", " ");
    
    strcpy(Path, sCurDir.GetBuffer(0));
    strcat(Path, "*.*");    
    strcpy(wfd.cFileName, "");
    
	hSrch=FindFirstFile(Path, &wfd);
    if( !strcmp(wfd.cFileName, "") ) return ; 
	
    // 요청 파일수 저장
    int cnt = 0;
    while (bResult) {
        bool IsFolder = wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        if( (type == SRC_FOLDER &  IsFolder ) ||
            (type == SRC_FILES  &  !IsFolder) ){
            
			CString str; 
			str.Format("%d,%s",  type, wfd.cFileName);
            UI_EXCUTE_SCRIPT("OnFolderRead", str.GetBuffer( 0 ));            
        }   
        
        bResult=FindNextFile(hSrch, &wfd);
	}
    
	FindClose(hSrch);
}

void CPageMain::On_API_SearchFolder(char* pParam)
{
	// 끝에 빈문자열이 온다.
	// RES:// 처리하다가 꼬인듯하다.
	CString str = pParam;
	str.TrimRight();
	SearchFileOrFolder(str.GetBuffer(0), 0 );
    SearchFileOrFolder(str.GetBuffer(0), 1 );

	// 끝남을 알림
	UI_EXCUTE_SCRIPT("OnFolderRead", "100,..");   

}

void CPageMain::On_API_CreateFolder(char* pParam)
{
    CString str  = UI_READ_ITEM(0, "FolderIn");
	CreateDirectory(str.GetBuffer(0), NULL);
	UI_WRITE_ITEM(0 , "FolderRESULT", str.GetBuffer(0) );	  
}


//-----------------------------------------------------------------------------
// CGI API 구현

// console 리다이렉션 
static HANDLE SpawnAndRedirect(LPCTSTR commandLine, HANDLE *hStdOutputReadPipe, LPCTSTR lpCurrentDirectory)
{
	HANDLE hStdOutputWritePipe, hStdOutput, hStdError;
	CreatePipe(hStdOutputReadPipe, &hStdOutputWritePipe, NULL, 0);	// create a non-inheritable pipe
	DuplicateHandle(GetCurrentProcess(), hStdOutputWritePipe,
								GetCurrentProcess(), &hStdOutput,	// duplicate the "write" end as inheritable stdout
								0, TRUE, DUPLICATE_SAME_ACCESS);
	DuplicateHandle(GetCurrentProcess(), hStdOutput,
								GetCurrentProcess(), &hStdError,	// duplicate stdout as inheritable stderr
								0, TRUE, DUPLICATE_SAME_ACCESS);
	CloseHandle(hStdOutputWritePipe);								// no longer need the non-inheritable "write" end of the pipe

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
	si.hStdInput  = GetStdHandle(STD_INPUT_HANDLE);	// (this is bad on a GUI app)
	si.hStdOutput = hStdOutput;
	si.hStdError  = hStdError;
	si.wShowWindow = SW_HIDE;						// IMPORTANT: hide subprocess console window
	TCHAR commandLineCopy[1024];					// CreateProcess requires a modifiable buffer
	_tcscpy(commandLineCopy, commandLine);
	if (!CreateProcess(	NULL, commandLineCopy, NULL, NULL, TRUE,
						CREATE_NEW_CONSOLE, NULL, lpCurrentDirectory, &si, &pi))
	{
		CloseHandle(hStdOutput);
		CloseHandle(hStdError);
		CloseHandle(*hStdOutputReadPipe);
		*hStdOutputReadPipe = INVALID_HANDLE_VALUE;
		return NULL;
	}

	CloseHandle(pi.hThread);
	CloseHandle(hStdOutput);
	CloseHandle(hStdError);
	return pi.hProcess;
}

// CGI 관련 처리 
void CPageMain::On_API_CGICall(char* pParam)
{
	HANDLE hOutput, hProcess;
	hProcess = SpawnAndRedirect(pParam, &hOutput, NULL);
	if (!hProcess) return;
	
	CString sOutput = "";

	CHAR buffer[1024 * 2];
	DWORD read;
	while (ReadFile(hOutput, buffer, 64, &read, NULL))
	{
		buffer[read] = '\0';
		sOutput += buffer;		
	}

	CloseHandle(hOutput);
	CloseHandle(hProcess);

	UI_WRITE_ITEM(0 , "CGIRESULT", sOutput.GetBuffer(0) );	
	
}



	
