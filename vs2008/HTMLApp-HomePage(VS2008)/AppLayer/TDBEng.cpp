/*
    ����  : API ������ Database ���� ������
    �ۼ���: �ڼ���
    �ۼ���: 2001-07-09
    ����  : ȯ�����Ӽ��� ���߾�� ���Ӽ��� ���̱� ���ؼ�
            API ������ Class ������ �������� ��.
*/
#include "stdafx.h"  // MFC�� �ش�
#include "TDBEng.h"
/********************************
   �ʱ�ȭ
********************************/
TDBEng::TDBEng() 
{
	ZeroMemory(m_qry, MAXBUF);
	SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&m_Henv);
    SQLSetEnvAttr(m_Henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);

}

/********************************
   �ı���
********************************/
TDBEng::~TDBEng()
{
    if (m_Hcommand) SQLFreeHandle(SQL_HANDLE_STMT, m_Hcommand);
    if (m_Hconn)    SQLDisconnect(m_Hconn);
    if (m_Hconn)    SQLFreeHandle(SQL_HANDLE_DBC,  m_Hconn);
    if (m_Henv)     SQLFreeHandle(SQL_HANDLE_ENV,  m_Henv);
}

/********************************
   ��� Ŀ��Ʈ
********************************/
BOOL TDBEng::connect(char* conn, styCONN sty)
{
    //"DSN=MySQLServer;SERVER=green;UID=Smith;PWD=Sesame;DATABASE=pubs;"
    const int MAXBUF = 255;
    
    // Ŀ�ؼ� ��Ʈ��
    char* CONSTR[] = {
        "FILEDSN=%s",
        "DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s;",
        "DRIVER={Microsoft Excel Driver  (*.xls)};DBQ=%s;",
        "%s"                
    };
    
    SQLCHAR     In[MAXBUF];
    SQLCHAR     Out[MAXBUF];
    SQLSMALLINT cbOut;

    // DB�� ���� �� �ڵ��� �����´�.
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
    
    // 2006-08-23 �ڼ��� �߰�
    // �ʱ�ȭ ���н� False ���� 
    if (m_state < 0) return FALSE;

    if(assert() == FALSE) return FALSE;
        
    // Ŀ�ǵ� �ڵ��� �����´�.
    m_state = SQLAllocHandle(SQL_HANDLE_STMT, m_Hconn, &m_Hcommand);
    if(assert() == FALSE) return FALSE;

	// STATEMENT ���¸� �����Ѵ�.
	m_state = SQLSetStmtAttr(m_Hcommand, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER) SQL_CURSOR_DYNAMIC , 0);
    if(assert() == FALSE) return FALSE;

    return TRUE;
}

/********************************
   �� Ŀ��Ʈ
********************************/
BOOL TDBEng::disconnect(void)
{
    return (m_state == SQL_SUCCESS && SQL_SUCCESS_WITH_INFO);
}


/********************************
   ���ǹ� ����
********************************/
BOOL TDBEng::SQL(char* qry)
{
    
	strcpy(m_qry, qry);

    // ���� ���ڵ� �� ������
	CloseRecordSet();
    
	// ���ǹ� ������
	m_state = SQLExecDirect(m_Hcommand, (SQLCHAR *)qry, SQL_NTS);
    
    if(assert() == FALSE) return FALSE;

    // �÷�, Row�� ����
	m_col = getColCount();
	//m_row = getRowCount();
    
    return TRUE;
}

/********************************
   ���ǹ� ����
********************************/
BOOL TDBEng::SQL(void)
{
    return SQL(m_qry);
}

/********************************
   Ŀ���� ó������ �̵�
********************************/
int TDBEng::MoveFirst()
{
    if(assert() == FALSE) return -1;
	SQLFetchScroll(m_Hcommand, SQL_FETCH_FIRST, 0);
	return 0;
}

/********************************
   Ŀ���� ���������� �̵�
********************************/
int TDBEng::MoveLast()
{
    if(assert() == FALSE) return -1;
	SQLFetchScroll(m_Hcommand, SQL_FETCH_LAST, 0);
	return 0;
}

/********************************
   Row�� ���
********************************/
long TDBEng::getRowCount(void)
{
    if(assert() == FALSE) return -1;
	long cnt = 0;
    
    // �̰� ���� �ȵ��ư���. ���߿� �ľ�����.    
    //while( SQLFetch(m_Hcommand) != SQL_NO_DATA) cnt++;
	return cnt;
}

/********************************
   �÷��� ���
********************************/
short TDBEng::getColCount(void)
{
    if(assert() == FALSE) return 0;
	
    short cnt;
	SQLNumResultCols(m_Hcommand, &cnt);
	return cnt;
}

/********************************
   ���ڵ� �� ����
********************************/
void TDBEng::CloseRecordSet()
{
    if(assert() == FALSE) return;

	SQLCloseCursor(m_Hcommand);
    SQLFreeStmt(m_Hcommand, SQL_UNBIND);
}

/********************************
   ���ڵ� ���� �ѱ��. - ���� 
********************************/
int TDBEng::GetRow(int row)
{
    if(assert() == FALSE) return -1;
    
    m_state = SQLFetchScroll(m_Hcommand, SQL_FETCH_ABSOLUTE, row);
	
	if(assert() == FALSE) return -1;

	return m_state;
}

/********************************
   ���ڵ� ���� �ѱ��. - ��� 
********************************/
int TDBEng::GetRow()
{
    if(assert() == FALSE) return -1;
    
    m_state = SQLFetchScroll(m_Hcommand, SQL_FETCH_RELATIVE, 1);
	
	if(assert() == FALSE) return -1;

	return m_state;
}

/********************************
   �ش� �ʵ��� ũ�⸦ �ѱ��.
********************************/
long TDBEng::getFieldSize(int col)
{
    /*if(assert() == FALSE) return -1;
	return m_colInfo[col];
    */
    // ������
    return 0;
}

/********************************
   ���� �ڵ鸵
********************************/
BOOL  TDBEng::assert(void)
{
    SQLCHAR     StaMsg[1024];
    SQLCHAR     ErrMsg[1024];
    SQLINTEGER  ErrNo;
    SQLSMALLINT stringLen;

    if ((m_state != SQL_SUCCESS) && (m_state != SQL_SUCCESS_WITH_INFO) && (m_state != SQL_NO_DATA)){
        SQLError(m_Henv, m_Hconn, m_Hcommand, StaMsg,  &ErrNo, ErrMsg,  1024, &stringLen);
        MessageBox(NULL, (char*)ErrMsg, "��� ���� ����!!", MB_OK);
        return FALSE;
    }
    
    return TRUE;
}

/********************************
   ���� ������ ���ε� -> Char������ �޴´�. 
********************************/
int  TDBEng::SetColData(int nCol, char** pBuf, int nLength)
{
    long m_colInfo;
    return SQLBindCol(m_Hcommand, nCol, SQL_C_CHAR, pBuf, nLength, &m_colInfo);
}

