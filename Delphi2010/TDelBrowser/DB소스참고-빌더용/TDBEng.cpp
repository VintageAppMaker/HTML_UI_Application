/***********************************************************
       작성일: 2000/08/28
       작성자: 박성완
       목적:   Data처리를 위한 ADO 클래스
       기능:   데이터베이스 연결 및 종료(Connect/disconnect),
               외부와 연결될 소스 리턴(getSource),
               질의문 실행(excuteSQL)
       수정일: 2001/01/05
       목적:   예외처리 디버깅
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
// 데이터베이스 연결
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
//        MessageDlg("[DB 연결에 실패했습니다]\n" + e->Message,
        MessageDlg("[Failed to link to DB]\n" + e->Message,
                    mtConfirmation,
                    TMsgDlgButtons() << mbYes, 0);
        return 0;
    }
}

//---------------------------------------------------------------------------
// 디비연결 해제
int TDBEng :: disconnect()
{
    if(m_Conn == NULL)  return 0;
    try{
        m_Conn->Close();
        return 1;

    } catch(EOleException* e ){
//        MessageDlg("[DB 끊기를 실패했습니다]\n" + e->Message,
        MessageDlg("[Failed to be disconnect from DB]\n" + e->Message,
                    mtConfirmation,
                    TMsgDlgButtons() << mbYes, 0);
        return 0;
    }
}

//---------------------------------------------------------------------------
// 레코드 개수 반환
int TDBEng :: getRecordCount()
{
     return m_Rs->RecordCount;
}

//---------------------------------------------------------------------------
// 필드 개수 반환
int TDBEng :: getFieldCount()
{
     return m_Rs->FieldCount;
}


//---------------------------------------------------------------------------
// 레코드셋 개체의 레퍼런스를 반환한다.
TDataSource* TDBEng :: getSource()
{
     return m_DataSource;
}

//---------------------------------------------------------------------------
// 질의문 실행
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
        MessageDlg( (String)"\n[질의문(SQL)에 문제가 발생했습니다]"
                    + "\n------------------------------------\n"
                    +  getSQL()
                    + "\n------------------------------------\n"
                    + IntToStr(e->ErrorCode),
                    mtConfirmation,
                    TMsgDlgButtons() << mbYes, 0);
        */

        return 0;
    }catch(...){
        // DB Engine error는 무시한다(DML쪽 메시지)
        return 0;
    }
}

//---------------------------------------------------------------------------
// 레코드 셋의 행/열의 좌표값으로 값을 가지고 온다.
AnsiString TDBEng :: getValue(int row, int col)
{
    if(m_Conn == NULL)             return 0;
    if(m_Conn->Connected == false) return 0;
    try{
        m_Rs->RecNo = row;                           // Record 이동
        return m_Rs->Fields->Fields[col]->AsString;  // 필드값 스트링으로 리턴
    } catch( ... ){
//        MessageDlg( "\n[잘못된 결과값을 요청했습니다]\n",
        MessageDlg( "\n[Requested Wrong]\n",
                    mtConfirmation,
                    TMsgDlgButtons() << mbYes, 0);
        return "";
    }
}

//---------------------------------------------------------------------------
// Rs 개체의 레코드 단위의 값을 스트링으로 리턴한다.
TStringList* TDBEng :: getRow()
{
    TStringList* Rs = new TStringList();
    try{
        m_Rs->Next();
        for(int i = 0; i < getFieldCount(); i++){
            Rs->Add(m_Rs->Fields->Fields[i]->AsString);
        }
    } catch(...){
//        MessageDlg("Row값을 읽어오는데 문제가 생겼습니다" ,
        MessageDlg("Problem occurred while reading Row value" ,
                   mtConfirmation,
                   TMsgDlgButtons() << mbYes, 0);
        return Rs;
    }

    return Rs;
}

//---------------------------------------------------------------------------
// Connection String 세팅
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

