(*
    제목: IDBManager 인터페이스
    작성자:박성완(adsloader@naver.com)
    작성일:2010.04.27
    목적:  DB 연동할 Interface 클래스 구현
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
