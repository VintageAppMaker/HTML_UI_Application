/*
    제목  : HTML PAGE 등록부 
    목적  : HTML Page를 등록함.
    작성자: 박성완
    수정일: 2006.08.14

    참고  : 이전 소스를 업그래이드 함. 
    
*/
#ifndef __PSW_SNAKE_FSM_CHTMLPAGE__
#define __PSW_SNAKE_FSM_CHTMLPAGE__

//-----------------------------------------------------------
// Macro 정의

#define  DEF_PAGE_START void RegisterPageClass(){ \

#define  REG_PAGE_CLASS(_cls_, _html_) \
	RegisterHTMLState(static_cast<FSM::Action>( &_cls_::OnPageReadEnd ), \
	                  static_cast<FSM::Action>( &_cls_::OnPageClose ), \
					  static_cast<FSM::Action>( &_cls_::OnPageCMD ), _html_); \

#define  DEF_PAGE_END   }\

//------------------------------------------------------------

#include "CPage.h"
#include "CPageMain.h"



class CHTMLPage : public CPageUI 
{

public:    
    CHTMLPage()
    {
        CPageUI::CPageUI();
        RegisterPageClass(); 

    }

	
/*
    참고: 모든 Page의 Handler class를 CPageMain으로 했다. 
	이유는 ...

    JScript를 메인으로 하고 DLL에서는 API를 제공하기 위해서임이다.
	(JavaScript Main Program)
*/

protected:
    // 추가된 페이지 
    //CPageMain         m_PageMain;	
        
//--------------------------------------------
// Page 등록 매크로 
DEF_PAGE_START
    REG_PAGE_CLASS(CPageMain,          "START") 
	REG_PAGE_CLASS(CPageMain,          "MAIN") 
DEF_PAGE_END            
//--------------------------------------------
//void RegisterPageClass();
                                    
};
#endif