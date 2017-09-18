/*
    제목  : PAGE UI
    목적  : HTML UI의 흐름을 제어한다.
    작성자: 박성완
    작성일: 2005.04.20
    수정일: 2006.04.13

    참고  : 1) 상태와 이벤트로 분기점을 가진다.
            2) Handler 테이블로 관리할 수 있다.
            3) 상태전이에 대한 메소드를 제공한다. 
            4) 상태는 내부에서 제어한다. 이벤트는 외부 입력항목이다.
            5) 되도록 API 형식으로 외부 함수를 끌어다가 쓴다.
            6) 크게 Page 관련 상태와 Data 통신 - HSP - 관련 상태로 구분된다.
    
    참고2: HTML Page를 사용하기에 귀찮은 면이 있었다.
          HTML 사용에 편리하게 FSM 규격 보다는 
          HTML UI Application의 편리성에 중점을 둠.
           
*/
#ifndef __PSW_SNAKE_FSM_CPAGE__
#define __PSW_SNAKE_FSM_CPAGE__

#include "fsm.h"
#include "UTIL_API.h"

// 화면 UI(웹)에
// 상태 머신
#define MAX_STATE 255
#define MAX_CMD   255

class CPageUI : public FSM 
{

public:


    // Event 정의
    enum EVENT_CPAGEUI 
    {                        
        PAGE_BEGIN_EVT     = 0, 

        PAGE_READEND_EVT,
        PAGE_CLOSE_EVT,
		PAGE_REQUEST_EVT, 
		INPUT_CMD_EVT,

        MAX_EVT       /* 자동카운트용 */
    };
    
    typedef struct tagSTATEINFO{
        char     PAGE_NAME[MAX_PATH];
        unsigned STATE; 
    } STATEINFO;
    STATEINFO html_state_table[MAX_STATE];
    
    CPageUI();
    
    int FindStateByName(char* name);
protected:                                    
    
    void OnPageRequest(FSM_EVT e);   
    // 상태 등록 API
    int RegisterHTMLState(
        Action fnEndPage, 
        Action fnClosePage, 
        Action fnCMDPage, 
        char* htmlname
    );
    
    
    int GetParamString(char* str, char** cmdPage, char** cmdFunc, char** cmdParam);
    
    
private:
    
    int m_state_cnt;    
   
public:
    static FSM::Action CPageUI_Handler[MAX_STATE][MAX_EVT];
};

#endif
