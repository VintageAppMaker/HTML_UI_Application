/*
    ����  : HTML PAGE ���� �Լ� import TABLE
    ����  : �ܺθ�⿡�� PAGE �ۼ��� UTIL API
    �ۼ���: �ڼ���
    �ۼ���: 2005.11.18

    ����  : 1) HTML �Լ��� ���̺��� �����Ѵ�.
            2) ���������� EXE�� �����̳ʿ��� �����Ѵ�.          
*/


#ifndef __PSW_SNAKE_HTML_API_PAGE__
#define __PSW_SNAKE_HTML_API_PAGE__



// HTML ���� API ���̺�
typedef struct {
    void   (*fnDisplayPage)         (int nPage);
    
    void   (*fnWrite_MessageToPage) (int nPage, char* msg);
    void   (*fnWrite_ListToPage)    (char* msg);
    void   (*fnErase_MessageOnPage) (int nPage);
    void   (*fnErase_ListOnPage)    (void);
    
    char*  (*fnRead_ValueItem)      (int nPage, char* Item); 
    int    (*fnWrite_ValueItem)     (int nPage, char* Item, char* msg);

    int    (*fnAttachTextToBoard)     (int nPage);
    int    (*fnAddHTMLText      )     (char* msg);

    int    (*fnClearHTMLText)         ();
    int    (*fnExcuteJScript)         (char* fnName, char* pParam);
	
} HTMLAPI;


extern HTMLAPI HTML_API_TABLE;
#endif
