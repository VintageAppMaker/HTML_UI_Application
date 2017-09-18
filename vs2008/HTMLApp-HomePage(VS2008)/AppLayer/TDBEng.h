/*
    ����  : API ������ Database ���� ������
    �ۼ���: �ڼ���
    �ۼ���: 2001-07-09
    ����  : ȯ�����Ӽ��� ���߾�� ���Ӽ��� ���̱� ���ؼ�
            API ������ Class ������ �������� ��.
*/

#ifndef SNAKE_PSW_TDBEng
#define SNAKE_PSW_TDBEng
#include <sql.h>
#include <sqlext.h>
#include "TDBMaster.h"

/*
    TDBMaster Ŭ������ ���� ���� Ŭ����
    ������ȯ�� �����ϰ� �̷�������� �ϱ� 
    ���� ���
    
*/

class AFX_EXT_CLASS TDBEng : public TDBMaster
{
public:
    TDBEng();
    ~TDBEng();
        
    virtual BOOL  connect(char* conn, styCONN sty = styMDB);   // Database ����
	virtual BOOL  disconnect();                        // Database ����
    
    virtual int   GetRow(int row);            // Row�� ���� �� ��������
	virtual int   GetRow();                   // Row�� ���� �� ��������
    virtual BOOL  SQL(char* qry);             // ���ǹ�   ����
    virtual BOOL  SQL(void);                  // ���ǹ�   ����
    virtual long  getRowCount(void);          // ���ǹ� ���� ��, ����� ���ڵ�� 
    virtual short getColCount(void);          // ���ǹ� ���� ��, ����� �÷���  

    // 2007.04.21 �ڼ��� �߰�
    // ��������ġ�� �ܺο��� �ϴ� ���� ������ ����.
    virtual int   SetColData(int nCol, char** pBuf, int nLength);

private:
    SQLHENV   m_Henv;						// ȯ���ڵ�
    SQLHDBC   m_Hconn;					    // �����ڵ�
    SQLHSTMT  m_Hcommand;                   // ��ɾ��ڵ�
	SQLRETURN m_state;                      // ���� ����  
    

	void CloseRecordSet();
	int  MoveFirst();                                     // Ŀ���� ó������ �̵��ϱ�
	int  MoveLast();                                      // Ŀ���� ���������� �̵��ϱ�

	long  getFieldSize(int col);                          // �ʵ� ����� �Ѱ��ش�.
    BOOL  assert(void);                                   // Error Handling�� �Ѵ�.

};

#endif