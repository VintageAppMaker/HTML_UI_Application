/*
    제목  : HTML PAGE 관련 함수
    목적  : 외부모듈에서 PAGE 작성용 UTIL API
    작성자: 박성완
    작성일: 2005.04.20

    참고  : 1) HTML 상태에서 API 구현을 위한 함수를 제공한다.
            2) 되도록 교체가능한 Layer 형태로 개발한다.
            
           
*/


#ifndef __PSW_SNAKE_HTML_API_PAGE__
#define __PSW_SNAKE_HTML_API_PAGE__


// HTML 관련 API 테이블
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

