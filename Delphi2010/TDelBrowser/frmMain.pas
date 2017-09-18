(*
    제목:   델파이 WebUI Application
    작성자: 박성완(adsloader@naverr.com)
    작성일: 2010.04.23
    목적  : 편리한 델파이를 이용한 UI + Web Application 개발

*)
unit frmMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, OleCtrls, SHDocVw, Buttons, IEBrowser, jpeg, Menus,
  PageSelector;

type
  TFuncPtr = function(arg1: Integer; arg2: PChar): Integer; stdcall;

  (*TWebBrowser를 캐스팅한다.*)
  TWebBrowser = class(IEBrowser.TExtendBrowser)
  end;

  TfrmMainView = class(TForm)
    Panel2: TPanel;
    wbMainView: TWebBrowser;
    mmMain: TMainMenu;
    fiel1: TMenuItem;
    N1: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    about1: TMenuItem;
    procedure wbMainViewBeforeNavigate2(ASender: TObject;
      const pDisp: IDispatch; var URL, Flags, TargetFrameName, PostData,
      Headers: OleVariant; var Cancel: WordBool);
    procedure wbMainViewDocumentComplete(ASender: TObject;
      const pDisp: IDispatch; var URL: OleVariant);
    procedure N1Click(Sender: TObject);
    procedure N2Click(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure about1Click(Sender: TObject);
  private
    { Private declarations }
    pSelector: StateSelector;

  public
    { Public declarations }
  end;

var
  frmMainView: TfrmMainView;

implementation

{$R *.dfm}

// Main Page 이동
procedure TfrmMainView.about1Click(Sender: TObject);
begin
  ShowMessage('TWebBrowser 예제임.');
end;

procedure TfrmMainView.FormActivate(Sender: TObject);
begin
  pSelector := StateSelector.Create;

  N1Click(Sender);
end;

procedure TfrmMainView.N1Click(Sender: TObject);
var
  sName : String;

const
  sFileName : String = 'tetris.html';
  sDNName   : String = 'AppManager.mdb';
begin

  // 처음페이지 이동
  sName := ExtractFilePath( ParamStr(0) );
  sName := sName + sFileName;
  wbMainView.Navigate(sName);
end;

// 업무페이지 이동
procedure TfrmMainView.N2Click(Sender: TObject);
var
  sName : String;
const
  sFileName : String = 'user.html';

begin
  // work 페이지 이동
  sName := ExtractFilePath( ParamStr(0) );
  sName := sName + sFileName;
  wbMainView.Navigate(sName);

end;

// URL 이동전 이벤트
procedure TfrmMainView.wbMainViewBeforeNavigate2(ASender: TObject;
  const pDisp: IDispatch; var URL, Flags, TargetFrameName, PostData,
  Headers: OleVariant; var Cancel: WordBool);
var
  sURL     : String;
begin

  sURL  := URL;
  Cancel := pSelector.BeforeURL(sURL, wbMainView);
end;

// 문서완료후 이벤트
procedure TfrmMainView.wbMainViewDocumentComplete(ASender: TObject;
  const pDisp: IDispatch; var URL: OleVariant);
begin
  pSelector.DocComplete(wbMainView);
end;

end.
