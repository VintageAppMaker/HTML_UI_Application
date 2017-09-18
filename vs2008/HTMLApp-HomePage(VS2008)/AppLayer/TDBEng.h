/*
    제목  : API 수준의 Database 관련 모듈규현
    작성자: 박성완
    작성일: 2001-07-09
    목적  : 환경종속성과 개발언어 종속성을 줄이기 위해서
            API 수준의 Class 구현을 목적으로 함.
*/

#ifndef SNAKE_PSW_TDBEng
#define SNAKE_PSW_TDBEng
#include <sql.h>
#include <sqlext.h>
#include "TDBMaster.h"

/*
    TDBMaster 클래스의 실제 구현 클래스
    엔진교환을 원할하게 이루어지도록 하기 
    위한 방법
    
*/

class AFX_EXT_CLASS TDBEng : public TDBMaster
{
public:
    TDBEng();
    ~TDBEng();
        
    virtual BOOL  connect(char* conn, styCONN sty = styMDB);   // Database 연결
	virtual BOOL  disconnect();                        // Database 종료
    
    virtual int   GetRow(int row);            // Row에 의한 값 가져오기
	virtual int   GetRow();                   // Row에 의한 값 가져오기
    virtual BOOL  SQL(char* qry);             // 질의문   실행
    virtual BOOL  SQL(void);                  // 질의문   실행
    virtual long  getRowCount(void);          // 질의문 실행 후, 적용된 레코드수 
    virtual short getColCount(void);          // 질의문 실행 후, 적용된 컬럼수  

    // 2007.04.21 박성완 추가
    // 데이터패치를 외부에서 하는 것이 유리한 듯함.
    virtual int   SetColData(int nCol, char** pBuf, int nLength);

private:
    SQLHENV   m_Henv;						// 환경핸들
    SQLHDBC   m_Hconn;					    // 연결핸들
    SQLHSTMT  m_Hcommand;                   // 명령어핸들
	SQLRETURN m_state;                      // 현재 상태  
    

	void CloseRecordSet();
	int  MoveFirst();                                     // 커서를 처음으로 이동하기
	int  MoveLast();                                      // 커서를 마지막으로 이동하기

	long  getFieldSize(int col);                          // 필드 사이즈를 넘겨준다.
    BOOL  assert(void);                                   // Error Handling을 한다.

};

#endif