/*
    제목  : API 수준의 Database 관련 모듈규현
    작성자: 박성완
    작성일: 2001-07-09
    목적  : 환경종속성과 개발언어 종속성을 줄이기 위해서
            API 수준의 Class 구현을 목적으로 함.
*/
#include "stdafx.h"  // MFC용 해더
#include "TDBEng.h"
/********************************
   초기화
********************************/
TDBEng::TDBEng() 
{
	ZeroMemory(m_qry, MAXBUF);
	SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&m_Henv);
    SQLSetEnvAttr(m_Henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);

}

/********************************
   파괴자
********************************/
TDBEng::~TDBEng()
{
    if (m_Hcommand) SQLFreeHandle(SQL_HANDLE_STMT, m_Hcommand);
    if (m_Hconn)    SQLDisconnect(m_Hconn);
    if (m_Hconn)    SQLFreeHandle(SQL_HANDLE_DBC,  m_Hconn);
    if (m_Henv)     SQLFreeHandle(SQL_HANDLE_ENV,  m_Henv);
}

/********************************
   디비 커넥트
********************************/
BOOL TDBEng::connect(char* conn, styCONN sty)
{
    //"DSN=MySQLServer;SERVER=green;UID=Smith;PWD=Sesame;DATABASE=pubs;"
    const int MAXBUF = 255;
    
    // 커넥션 스트링
    char* CONSTR[] = {
        "FILEDSN=%s",
        "DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s;",
        "DRIVER={Microsoft Excel Driver  (*.xls)};DBQ=%s;",
        "%s"                
    };
    
    SQLCHAR     In[MAXBUF];
    SQLCHAR     Out[MAXBUF];
    SQLSMALLINT cbOut;

    // DB에 연결 및 핸들을 가져온다.
    SQLAllocHandle(SQL_HANDLE_DBC, m_Henv, &m_Hconn);
    wsprintf((char *)In, CONSTR[sty], conn);
    
    if(sty != styODBC){
        m_state = SQLDriverConnect(m_Hconn,NULL,(SQLCHAR *)In,sizeof(In),Out,
                                   sizeof(Out),&cbOut, SQL_DRIVER_NOPROMPT);
    } else{
        m_state = SQLConnect(m_Hconn, (SQLCHAR*) dsnName, SQL_NTS,
                  (SQLCHAR*) UserName,  SQL_NTS,
                  (SQLCHAR*) PassWord, SQL_NTS);

        
    }
    
    // 2006-08-23 박성완 추가
    // 초기화 실패시 False 리턴 
    if (m_state < 0) return FALSE;

    if(assert() == FALSE) return FALSE;
        
    // 커맨드 핸들을 가져온다.
    m_state = SQLAllocHandle(SQL_HANDLE_STMT, m_Hconn, &m_Hcommand);
    if(assert() == FALSE) return FALSE;

	// STATEMENT 상태를 설정한다.
	m_state = SQLSetStmtAttr(m_Hcommand, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER) SQL_CURSOR_DYNAMIC , 0);
    if(assert() == FALSE) return FALSE;

    return TRUE;
}

/********************************
   디스 커넥트
********************************/
BOOL TDBEng::disconnect(void)
{
    return (m_state == SQL_SUCCESS && SQL_SUCCESS_WITH_INFO);
}


/********************************
   질의문 실행
********************************/
BOOL TDBEng::SQL(char* qry)
{
    
	strcpy(m_qry, qry);

    // 이전 레코드 셋 날리기
	CloseRecordSet();
    
	// 질의문 던지기
	m_state = SQLExecDirect(m_Hcommand, (SQLCHAR *)qry, SQL_NTS);
    
    if(assert() == FALSE) return FALSE;

    // 컬럼, Row수 저장
	m_col = getColCount();
	//m_row = getRowCount();
    
    return TRUE;
}

/********************************
   질의문 실행
********************************/
BOOL TDBEng::SQL(void)
{
    return SQL(m_qry);
}

/********************************
   커서를 처음으로 이동
********************************/
int TDBEng::MoveFirst()
{
    if(assert() == FALSE) return -1;
	SQLFetchScroll(m_Hcommand, SQL_FETCH_FIRST, 0);
	return 0;
}

/********************************
   커서를 마지막으로 이동
********************************/
int TDBEng::MoveLast()
{
    if(assert() == FALSE) return -1;
	SQLFetchScroll(m_Hcommand, SQL_FETCH_LAST, 0);
	return 0;
}

/********************************
   Row수 얻기
********************************/
long TDBEng::getRowCount(void)
{
    if(assert() == FALSE) return -1;
	long cnt = 0;
    
    // 이것 재대로 안돌아간다. 나중에 파악하자.    
    //while( SQLFetch(m_Hcommand) != SQL_NO_DATA) cnt++;
	return cnt;
}

/********************************
   컬럼수 얻기
********************************/
short TDBEng::getColCount(void)
{
    if(assert() == FALSE) return 0;
	
    short cnt;
	SQLNumResultCols(m_Hcommand, &cnt);
	return cnt;
}

/********************************
   레코드 셋 해제
********************************/
void TDBEng::CloseRecordSet()
{
    if(assert() == FALSE) return;

	SQLCloseCursor(m_Hcommand);
    SQLFreeStmt(m_Hcommand, SQL_UNBIND);
}

/********************************
   레코드 값을 넘긴다. - 절대 
********************************/
int TDBEng::GetRow(int row)
{
    if(assert() == FALSE) return -1;
    
    m_state = SQLFetchScroll(m_Hcommand, SQL_FETCH_ABSOLUTE, row);
	
	if(assert() == FALSE) return -1;

	return m_state;
}

/********************************
   레코드 값을 넘긴다. - 상대 
********************************/
int TDBEng::GetRow()
{
    if(assert() == FALSE) return -1;
    
    m_state = SQLFetchScroll(m_Hcommand, SQL_FETCH_RELATIVE, 1);
	
	if(assert() == FALSE) return -1;

	return m_state;
}

/********************************
   해당 필드의 크기를 넘긴다.
********************************/
long TDBEng::getFieldSize(int col)
{
    /*if(assert() == FALSE) return -1;
	return m_colInfo[col];
    */
    // 사용안함
    return 0;
}

/********************************
   에러 핸들링
********************************/
BOOL  TDBEng::assert(void)
{
    SQLCHAR     StaMsg[1024];
    SQLCHAR     ErrMsg[1024];
    SQLINTEGER  ErrNo;
    SQLSMALLINT stringLen;

    if ((m_state != SQL_SUCCESS) && (m_state != SQL_SUCCESS_WITH_INFO) && (m_state != SQL_NO_DATA)){
        SQLError(m_Henv, m_Hconn, m_Hcommand, StaMsg,  &ErrNo, ErrMsg,  1024, &stringLen);
        MessageBox(NULL, (char*)ErrMsg, "디비 엔진 에러!!", MB_OK);
        return FALSE;
    }
    
    return TRUE;
}

/********************************
   받을 데이터 바인딩 -> Char형으로 받는다. 
********************************/
int  TDBEng::SetColData(int nCol, char** pBuf, int nLength)
{
    long m_colInfo;
    return SQLBindCol(m_Hcommand, nCol, SQL_C_CHAR, pBuf, nLength, &m_colInfo);
}

