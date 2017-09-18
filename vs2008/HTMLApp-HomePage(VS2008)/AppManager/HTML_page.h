/*
    제목  : HTML PAGE 관련 함수
    목적  : 외부모듈에서 PAGE 작성용 UTIL API
    작성자: 박성완
    작성일: 2005.04.20

    참고  : 1) HTML 상태에서 API 구현을 위한 함수를 제공한다.
            2) 되도록 교체가능한 Layer 형태로 개발한다.
            
           
*/


#ifndef __PSW_SNAKE_HTML_PAGE__
#define __PSW_SNAKE_HTML_PAGE__

extern  "C" 
{
    
    void   Write_MessageToPage (int nPage, char* msg);
    void   Write_ListToPage    (char* msg);
    void   Erase_MessageOnPage (int nPage);
    void   Erase_ListOnPage    ();
    
    char*  Read_ValueItem      (int nPage, char* Item); 
    int    Write_ValueItem     (int nPage, char* Item, char* msg);       
    
    int    AttachHTMLTextToBoard (int nPage);
    int    AddHTMLText           (char* msg);
    int    ClearHTMLText();

	int    ExcuteJScript(char* fnName, char* pParam);
      
}

#endif
