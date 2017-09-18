/*
    ����  : HTML PAGE ��Ϻ� 
    ����  : HTML Page�� �����.
    �ۼ���: �ڼ���
    ������: 2006.08.14

    ����  : ���� �ҽ��� ���׷��̵� ��. 
    
*/
#ifndef __PSW_SNAKE_FSM_CHTMLPAGE__
#define __PSW_SNAKE_FSM_CHTMLPAGE__

//-----------------------------------------------------------
// Macro ����

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
    ����: ��� Page�� Handler class�� CPageMain���� �ߴ�. 
	������ ...

    JScript�� �������� �ϰ� DLL������ API�� �����ϱ� ���ؼ����̴�.
	(JavaScript Main Program)
*/

protected:
    // �߰��� ������ 
    //CPageMain         m_PageMain;	
        
//--------------------------------------------
// Page ��� ��ũ�� 
DEF_PAGE_START
    REG_PAGE_CLASS(CPageMain,          "START") 
	REG_PAGE_CLASS(CPageMain,          "MAIN") 
DEF_PAGE_END            
//--------------------------------------------
//void RegisterPageClass();
                                    
};
#endif