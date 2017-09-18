(*
  ����: IDBManager ����Ŭ����
  �ۼ���:�ڼ���(adsloader@naver.com)
  �ۼ���:2010.04.27
  ����:  DB �������� ����
  ����: 1���� ������ ���� ��[Ŀ�ؼǰ�������..],
  �ٸ��������� Assign �޾� ����Ѵ�.
*)
unit TDBEng;

interface

uses
  Classes, Controls, DB, ADODB, iDBEng;

type
  // Interace ���(����)�� �� ���, Interface ȥ�ڴ� �Ұ�����.
  TDBManager = class(TInterfacedObject, IDBManager)
  public
    // Interface ����
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

// Connection String �����
function TDBManager.MakeConnectionString(fname: String): String;
var
  m_ConString: String;
begin
  m_ConString :=
    'Provider=MSDataShape.1;Persist Security Info=True;' + 'Data Source=' +
    fname + ';Data Provider=Microsoft.Jet.OLEDB.4.0';

  result := m_ConString;
end;

// DB �����ϱ�
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

// DB ��������
function TDBManager.disconnect(): Integer;
begin
  if m_Conn = nil then
    Exit;
  m_Conn.Close();

end;

// ���ǹ� �����ϱ�
function TDBManager.ExcuteSQL(const SQL: String; spec: stySQL): Integer;
begin

  // DML���� DCL���� �����Ͽ� ����
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

// ������� ��������
function TDBManager.GetValue(rowID: Integer; colID: Integer): String;
begin
  if m_Conn = nil then
    Exit;
  if m_Conn.Connected = false then
    Exit;

  m_RS.RecNo := rowID;
  result := m_RS.Fields.Fields[colID].AsString;

end;

// Row ������ ���Ϲ޴´�.
function TDBManager.GetRowCount() : Integer;
begin
  result := m_RS.RecordCount;
end;

end.
