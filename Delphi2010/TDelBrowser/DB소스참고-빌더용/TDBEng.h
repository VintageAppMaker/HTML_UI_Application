/***********************************************************
       �ۼ���: 2000/08/28
       �ۼ���: �ڼ���
       ����:   Dataó���� ���� ADO Ŭ����
       ���:   DB������ �Ǵ� ADO Ŭ������ ���
               ���� DB ��ü���� �ʿ��� �����
               �����Ѵ�.
***********************************************************/
#ifndef PSW_SNAKE_ADO
#define PSW_SNAKE_ADO
#include <Classes.hpp>
#include <Controls.hpp>
#include <comobj.hpp>
#include <Dialogs.hpp>
#include <Db.hpp>
#include <ADODB.hpp>
//---------------------------------------------------------------------------
enum sqlSTY{styDML, styNormal};
enum dbErrorCode{
    qryPK_Error = - 21471097,
};

class TDBEng
{
public:

    int connect(AnsiString src);
    int disconnect();
    TDataSource* getSource();
    int excuteSQL(const AnsiString& SQL, sqlSTY sty = styNormal);

    int getRecordCount();
    int getFieldCount();

    AnsiString getValue(int row, int col);
    TStringList* getRow();

    AnsiString getSQL() const {return m_SQL;};
    inline void setSQL(AnsiString qry) { m_SQL = qry;};

    bool IsConnected();

    TDBEng(TComponent* AOwner);
    ~TDBEng();
    __property TADOConnection* Connection  = { read=GetConnection, write=SetConnection };

protected:
    TADODataSet*    m_Rs;
    TDataSource*    m_DataSource;

private:
    TADOConnection* m_Conn;
    TADOCommand*    m_Command;
    TComponent* m_AOwner;  // �����̳� ��ü
    AnsiString  m_SQL;
    void __fastcall SetConnection(TADOConnection* value);
    TADOConnection* __fastcall GetConnection();     // Query

};
//---------------------------------------------------------------------------
#endif
