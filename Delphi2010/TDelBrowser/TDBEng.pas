(*
  제목: IDBManager 구현클래스
  작성자:박성완(adsloader@naver.com)
  작성일:2010.04.27
  목적:  DB 연동실제 구현
  참고: 1개의 폼에서 생성 후[커넥션관리때문..],
  다른곳에서는 Assign 받아 사용한다.
*)
unit TDBEng;

interface

uses
  Classes, Controls, DB, ADODB, iDBEng;

type
  // Interace 상속(구현)을 할 경우, Interface 혼자는 불가능함.
  TDBManager = class(TInterfacedObject, IDBManager)
  public
    // Interface 구현
    function connect(source: String): Integer;
    function disconnect(): Integer;
    function ExcuteSQL(const SQL: String; spec: stySQL): Integer;
    function GetValue(rowID: Integer; colID: Integer): String;
    function GetRowCount() : Integer;

    constructor Create(com: TComponent);
    function MakeConnectionString(fname: String): String;

  private
    m_DBSource: TDataSource;
    m_RS: TADODataSet;
    m_Conn: TADOConnection;
    m_Command: TADOCommand;

    m_AOwner: TComponent;
    m_ConString: String;
  end;

implementation

constructor TDBManager.Create(com: TComponent);
begin
  m_AOwner := com;

  m_Conn := TADOConnection.Create(m_AOwner);
  m_DBSource := TDataSource.Create(m_AOwner);
  m_RS := TADODataSet.Create(m_AOwner);
  m_Command := TADOCommand.Create(m_AOwner);

end;

// Connection String 만들기
function TDBManager.MakeConnectionString(fname: String): String;
var
  m_ConString: String;
begin
  m_ConString :=
    'Provider=MSDataShape.1;Persist Security Info=True;' + 'Data Source=' +
    fname + ';Data Provider=Microsoft.Jet.OLEDB.4.0';

  result := m_ConString;
end;

// DB 연결하기
function TDBManager.connect(source: String): Integer;
begin
  if m_Conn = nil then
    Exit;

  if m_Conn.Connected = false then
  begin
    m_Conn.ConnectionString := MakeConnectionString(source);
    m_Conn.LoginPrompt := false;
  end;

  m_RS.Connection := m_Conn;
  m_Command.Connection := m_Conn;
  m_DBSource.DataSet := m_RS;

  m_Conn.Connected := true;

end;

// DB 연결해제
function TDBManager.disconnect(): Integer;
begin
  if m_Conn = nil then
    Exit;
  m_Conn.Close();

end;

// 질의문 실행하기
function TDBManager.ExcuteSQL(const SQL: String; spec: stySQL): Integer;
begin

  // DML문과 DCL문을 구별하여 실행
  if spec = stDML then
  begin
    m_Command.CommandText := SQL;
    m_Command.Execute();

  end
  else
  begin
    m_RS.Close();
    m_RS.CommandText := SQL;
    m_RS.Open();
  end;

end;

// 결과값을 가져오기
function TDBManager.GetValue(rowID: Integer; colID: Integer): String;
begin
  if m_Conn = nil then
    Exit;
  if m_Conn.Connected = false then
    Exit;

  m_RS.RecNo := rowID;
  result := m_RS.Fields.Fields[colID].AsString;

end;

// Row 개수를 리턴받는다.
function TDBManager.GetRowCount() : Integer;
begin
  result := m_RS.RecordCount;
end;

end.
