/***********************************************************
       �ۼ���: 2000/09/01
       �ۼ���: �ڼ���
       ����:   Dataó���� ���� Master Ŭ����
       ���:   ����� Ŭ������ ��ӹ޾�(����� ADO)
               ������ ����� �ܺο� �������ִ� ����� �Ѵ�.
               ���� DB �������̽��� ������ ����� �ϴ�
               Ŭ�����̴�.
***********************************************************/
#ifndef PSW_SNAKE_DBMaster
#define PSW_SNAKE_DBMaster
#include <Classes.hpp>
#include <Controls.hpp>
#include <comobj.hpp>
#include <Dialogs.hpp>
#include <Db.hpp>
#include <ADODB.hpp>

#include "TDBEng.h"
//---------------------------------------------------------------------------
class TDBMaster : public TDBEng
{
public:

    virtual TDataSource* DataSource();
    virtual int SQL(AnsiString qry, sqlSTY sty = styNormal, bool debug = false);
    virtual void connect(TADOConnection* Korn);

    void       removeField (AnsiString fName);
    AnsiString getFieldName(int col);


    TDBMaster(TComponent* AOwner, AnsiString fname = "");
    virtual ~TDBMaster();
    __property AnsiString query  = { read=Getquery };
    __property int recordNO  = { read=GetrecordNO, write=SetrecordNO };
    __property TADODataSet* DataSet  = { read=GetDataSet };

protected:
private:
    AnsiString setConnString(AnsiString fname);
    TStringList* m_SQL;
    TComponent*  m_AOwner;
    AnsiString   m_ConnString;
    AnsiString __fastcall Getquery();
    int __fastcall GetrecordNO();
    void __fastcall SetrecordNO(int no);
    TADODataSet* __fastcall GetDataSet();
};
//---------------------------------------------------------------------------
#endif
