/*
    제목  : UI 관련 API 영역
    목적  : 포팅가능한 API 영역으로 구현
    작성자: 박성완
    작성일: 2005.04.20

    참고  : 1) 되도록 교체가능한 Layer 형태로 개발한다.
            2) 실제 함수와 API와의 포팅을 관장한다. 
            3) UI외의 함수들은 변경가능이 희박하다. 그러므로 API 영역으로 구조를 가지지 않는다.            
           
*/

#define __UTIL_HTML__

#ifndef __PSW_SNAKE_UTIL_API__
#define __PSW_SNAKE_UTIL_API__


// HTML MODE를 선택했을 경우
#ifdef __UTIL_HTML__
    #include "HTML_UI_API.h"
    
    
    #define UI_DISPLAY(a_)             HTML_API_TABLE.fnDisplayPage( a_ )
    #define UI_WRITE_BOARD(a_, b_)     HTML_API_TABLE.fnWrite_MessageToPage(a_, b_)
    #define UI_WRITE_LIST(b_)          HTML_API_TABLE.fnWrite_ListToPage( b_)

    #define UI_ERASE_BOARD(a_)         HTML_API_TABLE.fnErase_MessageOnPage(a_)
    #define UI_ERASE_LIST( )           HTML_API_TABLE.fnErase_ListOnPage()
    
    #define UI_READ_ITEM(a_, b_)       HTML_API_TABLE.fnRead_ValueItem(a_, b_)
    #define UI_WRITE_ITEM(a_, b_, c_)  HTML_API_TABLE.fnWrite_ValueItem(a_, b_, c_)

    #define UI_ATTACH_BOARD(a_)        HTML_API_TABLE.fnAttachTextToBoard( a_)
    #define UI_ADD_HTML(a_)            HTML_API_TABLE.fnAddHTMLText( a_)
    #define UI_CLEAR_HTML()            HTML_API_TABLE.fnClearHTMLText(  )
    #define UI_EXCUTE_SCRIPT(a_, b_)   HTML_API_TABLE.fnExcuteJScript(a_, b_)

#else
    #include "stdafx.h"
    #define UI_DISPLAY(a_)             OutputDebugString(a_)               
    #define UI_WRITE_BOARD(a_, b_)     OutputDebugString(a_, b_)
    #define UI_WRITE_LIST(a_, b_)      OutputDebugString(a_, b_)

    #define UI_ERASE_BOARD(a_)         OutputDebugString(a_)
    #define UI_ERASE_LIST(a_)          OutputDebugString(a_)
    
    #define UI_READ_ITEM(a_, b_)       OutputDebugString(a_, b_)
    #define UI_WRITE_ITEM(a_, b_, c_)  OutputDebugString(a_, b_, c_)

    #define UI_ATTACH_BOARD(a_)        OutputDebugString( a_)
    #define UI_ADD_HTML(a_)            OutputDebugString( a_)
    #define UI_CLEAR_HTML()      
    #define UI_EXCUTE_SCRIPT(a_, b_)   OutputDebugString(a_, b_);

#endif


#endif
