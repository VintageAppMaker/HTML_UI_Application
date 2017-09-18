/***********************************************************
       작성일: 2000/09/01
       작성자: 박성완
       목적:   Data처리를 위한 Master 클래스
       기능:   디비엔진 클래스를 상속받아(현재는 ADO)
               구현된 기능을 외부에 제공해주는 기능을 한다.
               실제 DB 인터페이스의 마스터 기능을 하는
               클래스이다.
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
// 연결하기(레퍼런스 얻어와서)
void TDBMaster :: connect(TADOConnection* Korn)
{
    TDBEng::Connection = Korn;
    if (!m_ConnString.AnsiPos("MSDASQL")){
        TDBEng::connect(setConnString(m_ConnString));
    } else{
        TDBEng::connect(m_ConnString);   // PCLINK에는 이럴일 없다.
    }
}

//---------------------------------------------------------------------------
// Connection 스트링을 만든다
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
// 레코드 셋의 포인터를 반환한다.
TDataSource* TDBMaster :: DataSource()
{
    return getSource();
}

//---------------------------------------------------------------------------
// SQL을 실행한다.
int TDBMaster :: SQL(AnsiString qry, sqlSTY sty, bool debug)
{
    // SQL 파일로 저장
    if(debug == true){
    //if(debug == false){
        String name  = m_AOwner->Name;
        m_SQL->Add("");
        m_SQL->Add("/**********************************");
        m_SQL->Add("[실행:" + name + " 시각: " + DateTimeToStr(Now()) + "]");
        m_SQL->Add("**********************************/");
        m_SQL->Add(qry);
        m_SQL->SaveToFile("data/sqlhistory.log");
    }

    return (sty == styNormal) ? excuteSQL(qry) : excuteSQL(qry, sty);
}

//---------------------------------------------------------------------------
// 특정 필드의 이름을 리턴한다.
AnsiString TDBMaster :: getFieldName(int col)
{
    return m_Rs->Fields->Fields[col]->FieldName;
}

//---------------------------------------------------------------------------
// 리턴된 레코드의 특정 필드를 삭제한다.
void TDBMaster :: removeField(AnsiString fName)
{
    try{
        m_Rs->Fields->Remove(m_Rs->FindField(fName));
    } catch( ... ){
//        MessageDlg(fName + " 필드를 삭제하는데 오류가 발생했습니다." ,
        MessageDlg(fName + " Error occurred while deleting a field." ,
                   mtConfirmation,
                   TMsgDlgButtons() << mbYes, 0);
    }
}

//---------------------------------------------------------------------------
// 질의문을 리턴한다.
AnsiString __fastcall TDBMaster::Getquery()
{
    return m_SQL->Text;
}

//---------------------------------------------------------------------------
// 현재의 레코드 번호를 리턴한다.
int __fastcall TDBMaster::GetrecordNO()
{
    return m_Rs->RecNo;
}

//---------------------------------------------------------------------------
// 현재의 레코드 번호를 세팅한다.
void __fastcall TDBMaster::SetrecordNO(int no)
{
    m_Rs->RecNo = no;
}

//---------------------------------------------------------------------------
// 데이터셋을 리턴한다.
TADODataSet* __fastcall TDBMaster::GetDataSet()
{
    return m_Rs;
}
