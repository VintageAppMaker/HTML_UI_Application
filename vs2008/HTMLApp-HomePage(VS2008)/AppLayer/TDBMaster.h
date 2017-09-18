/*
    제목  : API 수준의 Database 관련 모듈규현
    작성자: 박성완
    작성일: 2001-07-09
    목적  : 환경종속성과 개발언어 종속성을 줄이기 위해서
            API 수준의 Class 구현을 목적으로 함.
*/
#ifndef SNAKE_PSW_TDBMaster
#define SNAKE_PSW_TDBMaster

#include <stdlib.h>
/*
    Db 제어를 구현하는 Interface 클래스
    자식 클래스의 서브 클래싱을 통해서만 구현되도록 
    하기 위해 abstarct 메소드 형식을 취함
*/
const int MAXBUF = 1024 * 10 * 8;                      // Max buffer
#define CR ("\n")                                      // 캐리지 리턴
class AFX_EXT_CLASS TDBMaster
{
public:
    enum{
        RECORD_NOT_EMPTY = 0,
        RECORD_END       = 100       
    } styRESULT;

protected:
    int   m_row;                                   // Row 수
    short m_col;                                   // 컬럼수
    char  dsnName[MAX_PATH];                       // dsn이름
    char  UserName[MAX_PATH];                      // 유저이름
    char  PassWord[MAX_PATH];                      // 서버명
    
public:
    TDBMaster(){};
	virtual ~TDBMaster(){};

	char  m_qry[MAXBUF];                                   // 질의문 만들기 
	
    enum styCONN{styFILEDSN, styMDB, styEXCEL, styODBC};          // 접속연결 형태     
    virtual BOOL  connect(char* conn, styCONN sty = styMDB ) = 0; // Database 연결
	virtual BOOL  disconnect() = 0;                               // Database 종료
	                                              
    // 2007-08-09 박성완 수정 추가 (속도문제)
	virtual int   GetRow(int row) = 0;            // Row에 의한 값 가져오기(절대위치) - 느림
    virtual int   GetRow()        = 0;            // Row에 의한 값 가져오기(상대위치) - 빠름

    virtual BOOL  SQL(char* qry)    = 0;          // 질의문   실행
    virtual BOOL  SQL(void)         = 0;          // 질의문   실행
    virtual long  getRowCount(void) = 0;          // 질의문 실행 후, 적용된 레코드수 
    virtual short getColCount(void) = 0;          // 질의문 실행 후, 적용된 컬럼수  
    
    // 2007.04.21 박성완 추가
    // 데이터패치를 외부에서 하는 것이 유리한 듯함.
    virtual int   SetColData(int nCol, char** pBuf, int nLength)  = 0;
    
    // 귀찮은 문자열 처리
	TDBMaster& operator <<(char* qry){strcat(m_qry, qry); return *this; };            
    TDBMaster& operator <<(int value){char number[10] = "";  itoa(value, number, 10 ); 
	                                  strcat(m_qry, number); return *this;};
    void Clear(void){lstrcpy(m_qry, "");};
    void SetODBCInfo(char* dsn, char* user, char* pass)
    {
        lstrcpy(dsnName, dsn); lstrcpy(UserName, user); lstrcpy(PassWord, pass);
    };
        
};
#endif