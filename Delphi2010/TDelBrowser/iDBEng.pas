(*
    ����: IDBManager �������̽�
    �ۼ���:�ڼ���(adsloader@naver.com)
    �ۼ���:2010.04.27
    ����:  DB ������ Interface Ŭ���� ����
*)
unit iDBEng;

interface

type
  (*DB Interface*)
  stySQL = (stDML, stDCL);

  IDBManager = interface
    function  connect   (source : String): Integer;
    function  disconnect(): Integer;
    function  ExcuteSQL (const SQL : String; spec: stySQL): Integer;
    function  GetValue  (rowID : Integer; colID : Integer): String;
    function  GetRowCount() : Integer;
  end;

implementation

end.
