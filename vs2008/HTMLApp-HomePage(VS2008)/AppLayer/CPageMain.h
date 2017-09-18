/*
    제목  : Main Page 구현부
    목적  : Page별 클래스화를 꿈꾼다.
    작성자: 박성완
    작성일: 2006.11.14

    참고  : 이전 소스 구조에서 Page 별 클래스를 강화함.

    수정일: 2007.08.28
    
*/
#ifndef __PSW_SNAKE_FSM_CPAGEMAIN__
#define __PSW_SNAKE_FSM_CPAGEMAIN__

#include "TDBEng.h"
#include "TDBMaster.h"

#include "CPage.h"
class CPageMain : public CPageUI 
{

public:    
    CPageMain();
   
    /*************************************/
    // 핸들러 선언  
	void OnPageReadEnd(FSM_EVT e);
    void OnPageClose  (FSM_EVT e);
    void OnPageCMD    (FSM_EVT e);

	int  RunFunctionByCMD(char* fName, char* pParam);

	// DB 관련 API 
	void On_API_ConnectDB      (char* pParam);
	void On_API_SQL            (char* pParam);
	void On_API_GetRow         (char* pParam);
	void On_API_GetValue       (char* pParam);

	// File 관련 API
	void On_API_OpenFile       (char* pParam);
	void On_API_CreateFile     (char* pParam);
	void On_API_CloseFile      (char* pParam);
	void On_API_ReadFile       (char* pParam);
	void On_API_WriteFile      (char* pParam);

	void On_API_DeleteFile     (char* pParam);
	void On_API_CopyFile       (char* pParam);
	void On_API_GetFileSize    (char* pParam);	

	// System 관련 API
	void On_API_System         (char* pParam);
	void On_API_excute         (char* pParam);
	

	// Folder 관련 API
	void On_API_GetCurFolder   (char* pParam);
	void On_API_SetFolder      (char* pParam);
	void On_API_SearchFolder   (char* pParam);
	void On_API_CreateFolder   (char* pParam);

	// CGI 관련 API
	void On_API_CGICall        (char* pParam);

};

#endif