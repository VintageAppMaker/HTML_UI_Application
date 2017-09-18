/***********************************************************
       �ۼ���: 2000/09/01
       �ۼ���: �ڼ���
       ����:   Dataó���� ���� Master Ŭ����
       ���:   ����� Ŭ������ ��ӹ޾�(����� ADO)
               ������ ����� �ܺο� �������ִ� ����� �Ѵ�.
               ���� DB �������̽��� ������ ����� �ϴ�
               Ŭ�����̴�.
***********************************************************/
#include "TDBMaster.h"
//---------------------------------------------------------------------------
TDBMaster :: TDBMaster(TComponent* AOwner, AnsiString fname)
          : TDBEng(AOwner)
{
    m_ConnString = fname;
    m_AOwner = AOwner;
    m_SQL = new TStringList();
}

//---------------------------------------------------------------------------
TDBMaster :: ~TDBMaster()
{
    delete m_SQL;
}

//---------------------------------------------------------------------------
// �����ϱ�(���۷��� ���ͼ�)
void TDBMaster :: connect(TADOConnection* Korn)
{
    TDBEng::Connection = Korn;
    if (!m_ConnString.AnsiPos("MSDASQL")){
        TDBEng::connect(setConnString(m_ConnString));
    } else{
        TDBEng::connect(m_ConnString);   // PCLINK���� �̷��� ����.
    }
}

//---------------------------------------------------------------------------
// Connection ��Ʈ���� �����
AnsiString TDBMaster :: setConnString(AnsiString fname)
{
    AnsiString sql;
    sql += "Provider=MSDataShape.1;Persist Security Info=True;";
    sql += "Data Source=";
    sql += fname;
    sql += ";Data Provider=Microsoft.Jet.OLEDB.4.0";

    return sql;
}

//---------------------------------------------------------------------------
// ���ڵ� ���� �����͸� ��ȯ�Ѵ�.
TDataSource* TDBMaster :: DataSource()
{
    return getSource();
}

//---------------------------------------------------------------------------
// SQL�� �����Ѵ�.
int TDBMaster :: SQL(AnsiString qry, sqlSTY sty, bool debug)
{
    // SQL ���Ϸ� ����
    if(debug == true){
    //if(debug == false){
        String name  = m_AOwner->Name;
        m_SQL->Add("");
        m_SQL->Add("/**********************************");
        m_SQL->Add("[����:" + name + " �ð�: " + DateTimeToStr(Now()) + "]");
        m_SQL->Add("**********************************/");
        m_SQL->Add(qry);
        m_SQL->SaveToFile("data/sqlhistory.log");
    }

    return (sty == styNormal) ? excuteSQL(qry) : excuteSQL(qry, sty);
}

//---------------------------------------------------------------------------
// Ư�� �ʵ��� �̸��� �����Ѵ�.
AnsiString TDBMaster :: getFieldName(int col)
{
    return m_Rs->Fields->Fields[col]->FieldName;
}

//---------------------------------------------------------------------------
// ���ϵ� ���ڵ��� Ư�� �ʵ带 �����Ѵ�.
void TDBMaster :: removeField(AnsiString fName)
{
    try{
        m_Rs->Fields->Remove(m_Rs->FindField(fName));
    } catch( ... ){
//        MessageDlg(fName + " �ʵ带 �����ϴµ� ������ �߻��߽��ϴ�." ,
        MessageDlg(fName + " Error occurred while deleting a field." ,
                   mtConfirmation,
                   TMsgDlgButtons() << mbYes, 0);
    }
}

//---------------------------------------------------------------------------
// ���ǹ��� �����Ѵ�.
AnsiString __fastcall TDBMaster::Getquery()
{
    return m_SQL->Text;
}

//---------------------------------------------------------------------------
// ������ ���ڵ� ��ȣ�� �����Ѵ�.
int __fastcall TDBMaster::GetrecordNO()
{
    return m_Rs->RecNo;
}

//---------------------------------------------------------------------------
// ������ ���ڵ� ��ȣ�� �����Ѵ�.
void __fastcall TDBMaster::SetrecordNO(int no)
{
    m_Rs->RecNo = no;
}

//---------------------------------------------------------------------------
// �����ͼ��� �����Ѵ�.
TADODataSet* __fastcall TDBMaster::GetDataSet()
{
    return m_Rs;
}
