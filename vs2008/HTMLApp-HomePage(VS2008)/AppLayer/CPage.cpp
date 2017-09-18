#include "stdafx.h"
#include "CPage.h"

//----------------------------------------------------------------------
// ���¿� ���� �ڵ鷯 ���̺�
// 
FSM::Action CPageUI::CPageUI_Handler[MAX_STATE][MAX_EVT];

// ���¸ӽ� �ʱ�ȭ 
CPageUI::CPageUI() : FSM (&CPageUI_Handler[0][0], MAX_STATE, MAX_EVT)
{
    m_state_cnt = 0;  
    ZeroMemory(html_state_table, sizeof(STATEINFO) * MAX_STATE);

    // ���� �ʱ�ȭ 
    for(int i = 0; i < MAX_STATE; i++){
        strcpy(html_state_table->PAGE_NAME, "");
        
        // �� ��Ȳ�����.. ���� ������ �ε��� ó���� ..
        // Release mode���� Internal compiler Error�� ���.
        // Debug ��� ������
        int j  = 0;
        while(1){
            CPageUI_Handler[i][j] = &FSM::doNothing;
            j++;
            if(j >= MAX_EVT) break;
        }        
    }    
}

//-----------------------------------------------------------------------------
// ����Լ� ����
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

// �������� �´� ���°��� �����Ѵ�.
// �޴���� ���°��� ��� ���̺��� �����Ѵ�.
int CPageUI::FindStateByName(char* name)
{   
    for(int i = 0; i < sizeof(html_state_table) / sizeof(html_state_table[0]); i++ ){
        if ( strlen(name) > 0 && strcmp(html_state_table[i].PAGE_NAME, name) == 0 ) 
            return i;
    }

    return -1;
}

// ���ڿ����� ���� �и���Ų��.
int CPageUI::GetParamString(char* str, char** cmdPage, char** cmdFunc, char** cmdParam)
{    
    int rst  = 0;

    char* TOKEN     = "|";    // ���ڿ� ��ū
    
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
// request �ڵ鷯
void CPageUI::OnPageRequest(FSM_EVT e)
{
    // ��û�� Ŀ�ǵ� �м� �� �Ľ�
    char* menuname = (char*)e.pParam; 

    // ������ �̵��� ���
	int state = FindStateByName(menuname);
    if(state != GetState() ){
        
        FSM_EVT e;
        e.EVT    = CPageUI::PAGE_CLOSE_EVT;
	    DoEvent( e );
    }
    if(state == -1 ) {
        // ��ϵ��� ���� ������ HTML ����¡��
        // �ϴ��� ������ �����ش�.
        CString str;
        str.Format("[%s] ��ϵ��� ���� �����Դϴ�.", menuname);
        OutputDebugString( str.GetBuffer(0) );
    }
    SetState( state );	
}
  
//-----------------------------------------------------------------------------
// �ڵ鷯 ���� (��������� ����)
//-----------------------------------------------------------------------------

