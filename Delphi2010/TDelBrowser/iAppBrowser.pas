(*
    제목: IBrowserApp 인터페이스 구현
    작성자:박성완(adsloader@naver.com)
    작성일:2010.04.24
    목적:  HTML API를 연동할 Interface 클래스 구현
*)
unit iAppBrowser;

interface

type
  IBrowserApp = interface
    function  OnReqestRunScript(source : String): String;
    function  OnReqestGetValue (const name : String): String;
    procedure OnReqestSetValue (const name : String; val : String);

  end;
implementation

end.
