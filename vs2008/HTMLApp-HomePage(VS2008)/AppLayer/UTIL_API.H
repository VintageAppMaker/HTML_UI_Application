/*
    ����  : UI ���� API ����
    ����  : ���ð����� API �������� ����
    �ۼ���: �ڼ���
    �ۼ���: 2005.04.20

    ����  : 1) �ǵ��� ��ü������ Layer ���·� �����Ѵ�.
            2) ���� �Լ��� API���� ������ �����Ѵ�. 
            3) UI���� �Լ����� ���氡���� ����ϴ�. �׷��Ƿ� API �������� ������ ������ �ʴ´�.            
           
*/

#define __UTIL_HTML__

#ifndef __PSW_SNAKE_UTIL_API__
#define __PSW_SNAKE_UTIL_API__


// HTML MODE�� �������� ���
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