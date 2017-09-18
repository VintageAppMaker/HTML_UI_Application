/*
    ����  : ���°�����-FSM
    ����  : ���α׷��� ������ �帧�� ��Ģ������ �����Ѵ�.
    �ۼ���: �ڼ���
    �ۼ���: 2005.04.20

    ����  : 1) ���¿� �̺�Ʈ�� �б����� ������.
            2) Handler ���̺�� ������ �� �ִ�.
            3) �������̿� ���� �޼ҵ带 �����Ѵ�. 
            4) ���´� ���ο��� �����Ѵ�. �̺�Ʈ�� �ܺ� �Է��׸��̴�.
           
*/
#ifndef __PSW_SNAKE_FSM_BASE__
#define __PSW_SNAKE_FSM_BASE__

// �̺�Ʈ�� �Ű�����
// ó�� Ŭ���� 
class FSM_EVT
{
public:
    unsigned EVT;   
    DWORD    pParam; 
};

// �������±��(Finate State Machine)
// BASE Ŭ���� 
class FSM 
{
public:
    typedef void (FSM::*Action)(FSM_EVT);
   
    FSM(Action  *table, unsigned nStates, unsigned nSignals)
       : StateHandler(table), MaxEvent(nSignals), MaxState(nStates), curState(0) 
       {}

    // >>�ܺ� �̺�Ʈ ó�� 
    // ������ �̺�Ʈ�� ���°��� X,Y��
    // �ڵ鷯���̺��� �Լ��� ȣ���Ѵ�.
    void DoEvent(FSM_EVT evt) 
    {
       unsigned const e = evt.EVT;
       if(MaxEvent < e ) return;      
       
       register Action const a = *(StateHandler + curState * MaxEvent + e); 
       (this->*(a))(evt);
    }

    // �ƹ��͵� ���ϴ� �Լ��� ��𼭳� �ʿ��ϴ�.
    void doNothing(FSM_EVT e) {}

protected:
   
    // ���¸� �����Ѵ�.
    inline void SetState(int target) 
    { 
        if(MaxState < target) return; 
        curState = target; 
    }

    // ���¸� ������ �´�.
    inline int GetState() 
    { 
        return curState; 
    }

protected:
    int curState;

private:
    Action  *StateHandler;
    unsigned MaxEvent;
    unsigned MaxState;
};

/*
�ڵ鷯���̺� ��:

"� �����϶�, �̷��̺�Ʈ���..."
�� ���� �ڵ鷯 ���̺��̴�.

StateTable::Action const CXXXX::HadnlerTBL[MAX_STATE][MAX_SIG] = {
       ...

   {
        &FSM::doNothing, 
        &FSM::doNothing, 
        static_cast<FSM::Action>(&C��ӹ���Ŭ����::�����ڵ鷯) 
        ...
   },
        ...

   {
        &FSM::doNothing, 
        &FSM::doNothing, 
        static_cast<FSM::Action>(&C��ӹ���Ŭ����::�����ڵ鷯) 
        ...
   }
};
*/

#endif
