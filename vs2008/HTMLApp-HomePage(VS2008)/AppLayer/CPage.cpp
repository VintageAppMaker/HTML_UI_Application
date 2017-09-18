#include "stdafx.h"
#include "CPage.h"

//----------------------------------------------------------------------
// 상태에 대한 핸들러 테이블
// 
FSM::Action CPageUI::CPageUI_Handler[MAX_STATE][MAX_EVT];

// 상태머신 초기화 
CPageUI::CPageUI() : FSM (&CPageUI_Handler[0][0], MAX_STATE, MAX_EVT)
{
    m_state_cnt = 0;  
    ZeroMemory(html_state_table, sizeof(STATEINFO) * MAX_STATE);

    // 상태 초기화 
    for(int i = 0; i < MAX_STATE; i++){
        strcpy(html_state_table->PAGE_NAME, "");
        
        // 좀 당황스러운데.. 이중 루프와 인덱스 처리시 ..
        // Release mode에서 Internal compiler Error가 뜬다.
        // Debug 모드 괜찮음
        int j  = 0;
        while(1){
            CPageUI_Handler[i][j] = &FSM::doNothing;
            j++;
            if(j >= MAX_EVT) break;
        }        
    }    
}

//-----------------------------------------------------------------------------
// 멤버함수 정의
int CPageUI::RegisterHTMLState(
        Action fnEndPage,
        Action fnClosePage, 
        Action fnCMDPage, 
        char*  htmlname
)
{
    int state = m_state_cnt;

    strcpy(html_state_table[state].PAGE_NAME, htmlname);
    html_state_table[state].STATE            = state;
    CPageUI::CPageUI_Handler[state][PAGE_READEND_EVT] = static_cast<FSM::Action>(fnEndPage);
    CPageUI::CPageUI_Handler[state][PAGE_CLOSE_EVT]   = static_cast<FSM::Action>(fnClosePage);
    CPageUI::CPageUI_Handler[state][INPUT_CMD_EVT]    = static_cast<FSM::Action>(fnCMDPage);
    CPageUI::CPageUI_Handler[state][PAGE_REQUEST_EVT] = static_cast<FSM::Action>(&CPageUI::OnPageRequest);

    m_state_cnt++;

    return 0;
}

// 페이지명에 맞는 상태값을 리턴한다.
// 메뉴명과 상태값의 룩업 테이블을 구현한다.
int CPageUI::FindStateByName(char* name)
{   
    for(int i = 0; i < sizeof(html_state_table) / sizeof(html_state_table[0]); i++ ){
        if ( strlen(name) > 0 && strcmp(html_state_table[i].PAGE_NAME, name) == 0 ) 
            return i;
    }

    return -1;
}

// 문자열에서 값을 분리시킨다.
int CPageUI::GetParamString(char* str, char** cmdPage, char** cmdFunc, char** cmdParam)
{    
    int rst  = 0;

    char* TOKEN     = "|";    // 문자열 토큰
    
    *cmdPage  = strtok(str, TOKEN);
    if(*cmdPage == NULL)  return rst;

    *cmdFunc  = strtok(NULL, TOKEN);
    if(*cmdFunc == NULL)  return rst;

    *cmdParam = strtok(NULL, TOKEN);    
    if(*cmdParam == NULL) return rst;
    
    rst = 1; 
    return rst;
}

//-----------------------------------------------------------------------------
// request 핸들러
void CPageUI::OnPageRequest(FSM_EVT e)
{
    // 요청한 커맨드 분석 및 파싱
    char* menuname = (char*)e.pParam; 

    // 페이지 이동일 경우
	int state = FindStateByName(menuname);
    if(state != GetState() ){
        
        FSM_EVT e;
        e.EVT    = CPageUI::PAGE_CLOSE_EVT;
	    DoEvent( e );
    }
    if(state == -1 ) {
        // 등록되지 않은 상태의 HTML 브라우징을
        // 일단은 실행은 시켜준다.
        CString str;
        str.Format("[%s] 등록되지 않은 상태입니다.", menuname);
        OutputDebugString( str.GetBuffer(0) );
    }
    SetState( state );	
}
  
//-----------------------------------------------------------------------------
// 핸들러 정의 (사용자정의 영역)
//-----------------------------------------------------------------------------

