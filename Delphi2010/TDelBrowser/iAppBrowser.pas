(*
    ����: IBrowserApp �������̽� ����
    �ۼ���:�ڼ���(adsloader@naver.com)
    �ۼ���:2010.04.24
    ����:  HTML API�� ������ Interface Ŭ���� ����
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
