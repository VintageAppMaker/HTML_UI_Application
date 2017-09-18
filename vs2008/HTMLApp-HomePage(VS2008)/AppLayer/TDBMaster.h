/*
    ����  : API ������ Database ���� ������
    �ۼ���: �ڼ���
    �ۼ���: 2001-07-09
    ����  : ȯ�����Ӽ��� ���߾�� ���Ӽ��� ���̱� ���ؼ�
            API ������ Class ������ �������� ��.
*/
#ifndef SNAKE_PSW_TDBMaster
#define SNAKE_PSW_TDBMaster

#include <stdlib.h>
/*
    Db ��� �����ϴ� Interface Ŭ����
    �ڽ� Ŭ������ ���� Ŭ������ ���ؼ��� �����ǵ��� 
    �ϱ� ���� abstarct �޼ҵ� ������ ����
*/
const int MAXBUF = 1024 * 10 * 8;                      // Max buffer
#define CR ("\n")                                      // ĳ���� ����
class AFX_EXT_CLASS TDBMaster
{
public:
    enum{
        RECORD_NOT_EMPTY = 0,
        RECORD_END       = 100       
    } styRESULT;

protected:
    int   m_row;                                   // Row ��
    short m_col;                                   // �÷���
    char  dsnName[MAX_PATH];                       // dsn�̸�
    char  UserName[MAX_PATH];                      // �����̸�
    char  PassWord[MAX_PATH];                      // ������
    
public:
    TDBMaster(){};
	virtual ~TDBMaster(){};

	char  m_qry[MAXBUF];                                   // ���ǹ� ����� 
	
    enum styCONN{styFILEDSN, styMDB, styEXCEL, styODBC};          // ���ӿ��� ����     
    virtual BOOL  connect(char* conn, styCONN sty = styMDB ) = 0; // Database ����
	virtual BOOL  disconnect() = 0;                               // Database ����
	                                              
    // 2007-08-09 �ڼ��� ���� �߰� (�ӵ�����)
	virtual int   GetRow(int row) = 0;            // Row�� ���� �� ��������(������ġ) - ����
    virtual int   GetRow()        = 0;            // Row�� ���� �� ��������(�����ġ) - ����

    virtual BOOL  SQL(char* qry)    = 0;          // ���ǹ�   ����
    virtual BOOL  SQL(void)         = 0;          // ���ǹ�   ����
    virtual long  getRowCount(void) = 0;          // ���ǹ� ���� ��, ����� ���ڵ�� 
    virtual short getColCount(void) = 0;          // ���ǹ� ���� ��, ����� �÷���  
    
    // 2007.04.21 �ڼ��� �߰�
    // ��������ġ�� �ܺο��� �ϴ� ���� ������ ����.
    virtual int   SetColData(int nCol, char** pBuf, int nLength)  = 0;
    
    // ������ ���ڿ� ó��
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