/*
    ����  : PAGE UI
    ����  : HTML UI�� �帧�� �����Ѵ�.
    �ۼ���: �ڼ���
    �ۼ���: 2005.04.20
    ������: 2006.04.13

    ����  : 1) ���¿� �̺�Ʈ�� �б����� ������.
            2) Handler ���̺�� ������ �� �ִ�.
            3) �������̿� ���� �޼ҵ带 �����Ѵ�. 
            4) ���´� ���ο��� �����Ѵ�. �̺�Ʈ�� �ܺ� �Է��׸��̴�.
            5) �ǵ��� API �������� �ܺ� �Լ��� ����ٰ� ����.
            6) ũ�� Page ���� ���¿� Data ��� - HSP - ���� ���·� ���еȴ�.
    
    ����2: HTML Page�� ����ϱ⿡ ������ ���� �־���.
          HTML ��뿡 ���ϰ� FSM �԰� ���ٴ� 
          HTML UI Application�� ������ ������ ��.
           
*/
#ifndef __PSW_SNAKE_FSM_CPAGE__
#define __PSW_SNAKE_FSM_CPAGE__

#include "fsm.h"
#include "UTIL_API.h"

// ȭ�� UI(��)��
// ���� �ӽ�
#define MAX_STATE 255
#define MAX_CMD   255

class CPageUI : public FSM 
{

public:


    // Event ����
    enum EVENT_CPAGEUI 
    {                        
        PAGE_BEGIN_EVT     = 0, 

        PAGE_READEND_EVT,
        PAGE_CLOSE_EVT,
		PAGE_REQUEST_EVT, 
		INPUT_CMD_EVT,

        MAX_EVT       /* �ڵ�ī��Ʈ�� */
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
    // ���� ��� API
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
