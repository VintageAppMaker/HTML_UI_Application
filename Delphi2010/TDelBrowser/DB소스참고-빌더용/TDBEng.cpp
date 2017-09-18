/***********************************************************
       �ۼ���: 2000/08/28
       �ۼ���: �ڼ���
       ����:   Dataó���� ���� ADO Ŭ����
       ���:   �����ͺ��̽� ���� �� ����(Connect/disconnect),
               �ܺο� ����� �ҽ� ����(getSource),
               ���ǹ� ����(excuteSQL)
       ������: 2001/01/05
       ����:   ����ó�� �����
***********************************************************/
#include "TDBEng.h"

//---------------------------------------------------------------------------
TDBEng :: TDBEng(TComponent* AOwner)
{
    m_AOwner = AOwner;

    m_Rs   = new TADODataSet(m_AOwner);
    m_Command = new TADOCommand(m_AOwner);
    m_DataSource = new TDataSource(m_AOwner);

}

//---------------------------------------------------------------------------
TDBEng :: ~TDBEng()
{
    delete m_Rs;
    delete m_DataSource;
}

//---------------------------------------------------------------------------
// �����ͺ��̽� ����
int TDBEng :: connect(AnsiString src)
{

    if(m_Conn == NULL)  return 0;
    try{
        if(m_Conn->Connected != true){
            m_Conn->ConnectionString = src;
            m_Conn->LoginPrompt = false;
        }

        m_Rs->Connection = m_Conn;
        m_Command->Connection = m_Conn;
        m_DataSource->DataSet = m_Rs;

        return 1;

    } catch(EOleException* e ){
//        MessageDlg("[DB ���ῡ �����߽��ϴ�]\n" + e->Message,
        MessageDlg("[Failed to link to DB]\n" + e->Message,
                    mtConfirmation,
                    TMsgDlgButtons() << mbYes, 0);
        return 0;
    }
}

//---------------------------------------------------------------------------
// ��񿬰� ����
int TDBEng :: disconnect()
{
    if(m_Conn == NULL)  return 0;
    try{
        m_Conn->Close();
        return 1;

    } catch(EOleException* e ){
//        MessageDlg("[DB ���⸦ �����߽��ϴ�]\n" + e->Message,
        MessageDlg("[Failed to be disconnect from DB]\n" + e->Message,
                    mtConfirmation,
                    TMsgDlgButtons() << mbYes, 0);
        return 0;
    }
}

//---------------------------------------------------------------------------
// ���ڵ� ���� ��ȯ
int TDBEng :: getRecordCount()
{
     return m_Rs->RecordCount;
}

//---------------------------------------------------------------------------
// �ʵ� ���� ��ȯ
int TDBEng :: getFieldCount()
{
     return m_Rs->FieldCount;
}


//---------------------------------------------------------------------------
// ���ڵ�� ��ü�� ���۷����� ��ȯ�Ѵ�.
TDataSource* TDBEng :: getSource()
{
     return m_DataSource;
}

//---------------------------------------------------------------------------
// ���ǹ� ����
int TDBEng :: excuteSQL(const AnsiString& SQL, sqlSTY sty)
{
    setSQL(SQL);

    try{

        if (sty == styDML){
            m_Command->CommandText = getSQL();
            m_Command->Execute();
        } else{
            m_Rs->Close();
            m_Rs->CommandText = getSQL();
            m_Rs->Open();
        }

        return 1;
    }catch(EOleException* e){

        /*
        MessageDlg( (String)"\n[���ǹ�(SQL)�� ������ �߻��߽��ϴ�]"
                    + "\n------------------------------------\n"
                    +  getSQL()
                    + "\n------------------------------------\n"
                    + IntToStr(e->ErrorCode),
                    mtConfirmation,
                    TMsgDlgButtons() << mbYes, 0);
        */

        return 0;
    }catch(...){
        // DB Engine error�� �����Ѵ�(DML�� �޽���)
        return 0;
    }
}

//---------------------------------------------------------------------------
// ���ڵ� ���� ��/���� ��ǥ������ ���� ������ �´�.
AnsiString TDBEng :: getValue(int row, int col)
{
    if(m_Conn == NULL)             return 0;
    if(m_Conn->Connected == false) return 0;
    try{
        m_Rs->RecNo = row;                           // Record �̵�
        return m_Rs->Fields->Fields[col]->AsString;  // �ʵ尪 ��Ʈ������ ����
    } catch( ... ){
//        MessageDlg( "\n[�߸��� ������� ��û�߽��ϴ�]\n",
        MessageDlg( "\n[Requested Wrong]\n",
                    mtConfirmation,
                    TMsgDlgButtons() << mbYes, 0);
        return "";
    }
}

//---------------------------------------------------------------------------
// Rs ��ü�� ���ڵ� ������ ���� ��Ʈ������ �����Ѵ�.
TStringList* TDBEng :: getRow()
{
    TStringList* Rs = new TStringList();
    try{
        m_Rs->Next();
        for(int i = 0; i < getFieldCount(); i++){
            Rs->Add(m_Rs->Fields->Fields[i]->AsString);
        }
    } catch(...){
//        MessageDlg("Row���� �о���µ� ������ ������ϴ�" ,
        MessageDlg("Problem occurred while reading Row value" ,
                   mtConfirmation,
                   TMsgDlgButtons() << mbYes, 0);
        return Rs;
    }

    return Rs;
}

//---------------------------------------------------------------------------
// Connection String ����
void __fastcall TDBEng::SetConnection(TADOConnection* value)
{
    m_Conn = value;
}

//---------------------------------------------------------------------------
TADOConnection* __fastcall TDBEng::GetConnection()
{
    return m_Conn;
}
//---------------------------------------------------------------------------

