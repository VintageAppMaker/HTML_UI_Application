/*
    제목  : 상태관리자-FSM
    목적  : 프로그램의 한정된 흐름을 규칙적으로 제어한다.
    작성자: 박성완
    작성일: 2005.04.20

    참고  : 1) 상태와 이벤트로 분기점을 가진다.
            2) Handler 테이블로 관리할 수 있다.
            3) 상태전이에 대한 메소드를 제공한다. 
            4) 상태는 내부에서 제어한다. 이벤트는 외부 입력항목이다.
           
*/
#ifndef __PSW_SNAKE_FSM_BASE__
#define __PSW_SNAKE_FSM_BASE__

// 이벤트와 매개변수
// 처리 클래스 
class FSM_EVT
{
public:
    unsigned EVT;   
    DWORD    pParam; 
};

// 한정상태기계(Finate State Machine)
// BASE 클래스 
class FSM 
{
public:
    typedef void (FSM::*Action)(FSM_EVT);
   
    FSM(Action  *table, unsigned nStates, unsigned nSignals)
       : StateHandler(table), MaxEvent(nSignals), MaxState(nStates), curState(0) 
       {}

    // >>외부 이벤트 처리 
    // 설정된 이벤트와 상태값을 X,Y로
    // 핸들러테이블의 함수를 호출한다.
    void DoEvent(FSM_EVT evt) 
    {
       unsigned const e = evt.EVT;
       if(MaxEvent < e ) return;      
       
       register Action const a = *(StateHandler + curState * MaxEvent + e); 
       (this->*(a))(evt);
    }

    // 아무것도 안하는 함수는 어디서나 필요하다.
    void doNothing(FSM_EVT e) {}

protected:
   
    // 상태를 전이한다.
    inline void SetState(int target) 
    { 
        if(MaxState < target) return; 
        curState = target; 
    }

    // 상태를 가지고 온다.
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
핸들러테이블 예:

"어떤 상태일때, 이런이벤트라면..."
에 대한 핸들러 테이블이다.

StateTable::Action const CXXXX::HadnlerTBL[MAX_STATE][MAX_SIG] = {
       ...

   {
        &FSM::doNothing, 
        &FSM::doNothing, 
        static_cast<FSM::Action>(&C상속받은클래스::상태핸들러) 
        ...
   },
        ...

   {
        &FSM::doNothing, 
        &FSM::doNothing, 
        static_cast<FSM::Action>(&C상속받은클래스::상태핸들러) 
        ...
   }
};
*/

#endif
