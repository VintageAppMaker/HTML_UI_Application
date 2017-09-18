/*
    ����  : Main Page ������
    ����  : Page�� Ŭ����ȭ�� �޲۴�.
    �ۼ���: �ڼ���
    �ۼ���: 2006.11.14

    ����  : ���� �ҽ� �������� Page �� Ŭ������ ��ȭ��.

    ������: 2007.08.28
    
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
    // �ڵ鷯 ����  
	void OnPageReadEnd(FSM_EVT e);
    void OnPageClose  (FSM_EVT e);
    void OnPageCMD    (FSM_EVT e);

	int  RunFunctionByCMD(char* fName, char* pParam);

	// DB ���� API 
	void On_API_ConnectDB      (char* pParam);
	void On_API_SQL            (char* pParam);
	void On_API_GetRow         (char* pParam);
	void On_API_GetValue       (char* pParam);

	// File ���� API
	void On_API_OpenFile       (char* pParam);
	void On_API_CreateFile     (char* pParam);
	void On_API_CloseFile      (char* pParam);
	void On_API_ReadFile       (char* pParam);
	void On_API_WriteFile      (char* pParam);

	void On_API_DeleteFile     (char* pParam);
	void On_API_CopyFile       (char* pParam);
	void On_API_GetFileSize    (char* pParam);	

	// System ���� API
	void On_API_System         (char* pParam);
	void On_API_excute         (char* pParam);
	

	// Folder ���� API
	void On_API_GetCurFolder   (char* pParam);
	void On_API_SetFolder      (char* pParam);
	void On_API_SearchFolder   (char* pParam);
	void On_API_CreateFolder   (char* pParam);

	// CGI ���� API
	void On_API_CGICall        (char* pParam);

};

#endif