unit IEBrowser;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Controls, Forms,
  ActiveX, OleCtrls, SHDocVw, MSHTML, StdCtrls, idoc, Automation, ActnList
  , iAppBrowser;


type
  TApplicationWrapper = class;

  // Augment TWebBrowser so we can implement IDocHostUIHandler::GetExternal

  TExtendBrowser = class(SHDocVw.TWebBrowser, IDocHostUIHandler, IBrowserApp)
  private
    function GetHTMLWindow2: IHTMLWindow2;
    function GetDocument2: IHTMLDocument2;
  protected
    procedure Loaded; override;
    { IDocHostUIHandler }
    function EnableModeless(fEnable: Integer): HResult; stdcall;
    function FilterDataObject(const pDO: IDataObject; out ppDORet: IDataObject): HResult; stdcall;
    function GetDropTarget(const pDropTarget: IDropTarget; out ppDropTarget: IDropTarget): HResult; stdcall;
    function GetExternal(out ppDispatch: IDispatch): HResult; stdcall;
    function GetHostInfo(var pInfo: _DOCHOSTUIINFO): HResult; stdcall;
    function GetOptionKeyPath(out pchKey: PWideChar; dw: UINT): HResult; stdcall;
    function HideUI: HResult; stdcall;
    function OnDocWindowActivate(fActivate: Integer): HResult; stdcall;
    function OnFrameWindowActivate(fActivate: Integer): HResult; stdcall;
    function ResizeBorder(var prcBorder: tagRECT; const pUIWindow: IOleInPlaceUIWindow;
      fRameWindow: Integer): HResult; stdcall;
    function ShowContextMenu(dwID: UINT; ppt: PtagPOINT; const pcmdtReserved: IUnknown;
       const pdispReserved: IDispatch): HResult; stdcall;
    function ShowUI(dwID: UINT; const pActiveObject: IOleInPlaceActiveObject;
      const pCommandTarget: IOleCommandTarget; const pFrame: IOleInPlaceFrame;
      const pDoc: IOleInPlaceUIWindow): HResult; stdcall;
    function TranslateAccelerator(var lpmsg: tagMSG; var pguidCmdGroup: TGUID; nCmdID: UINT): HResult; stdcall;
    function TranslateUrl(dwTranslate: UINT; pchURLIn: PWideChar; out ppchURLOut: PWideChar): HResult; stdcall;
    function UpdateUI: HResult; stdcall;
  public
    procedure ExecJScript(const Script: string);
    function  GetElementValue(const name : String): String;
    procedure SetElementValue(const name : String; val : String);

    property Document2: IHTMLDocument2 read GetDocument2;
    property HTMLWindow2: IHTMLWindow2 read GetHTMLWindow2;

    // IBrowserApp Interface 구현
    function  OnReqestRunScript(source : String): String;
    function  OnReqestGetValue(const name : String): String;
    procedure OnReqestSetValue(const name : String; val : String);

  end;

  TApplicationWrapper = class(TObjectWrapper)
  private
    function GetApplication: TApplication;
    function GetCaption: string;
    procedure SetCaption(S: string);
  published
    property Application: TApplication read GetApplication;
    property Caption: string read GetCaption write SetCaption;
  end;


implementation

uses ComObj, UrlMon;


{ TExtendBrowser }

// Element의 값을 가져온다.
function TExtendBrowser.GetElementValue(const name : String) : String;
var
  sVal : String;
begin
  if Document2 <> nil then
  begin
    sVal := self.OleObject.Document.all.item(name).value;
  end;

  result := sVal;
end;

// Element의 값을 저장한다.
procedure TExtendBrowser.SetElementValue(const name : String; val : String);
var
  sTest : String;
begin
  if Document2 <> nil then
  begin
    // 일반 Element의 Value값을 저장한다.
    self.OleObject.Document.all.item(name).value := val;
    (*********************************************************************************)
    (*일반 Form이 아닌 <DIV>와 같은 Element의 HTML을 액세스 하고자 한다면 다음과 같이 해야한다.*)
    //sTest := self.OleObject.Document.getElementById('BOARD_1').innerHTML;
    (*********************************************************************************)

  end;
end;

function TExtendBrowser.EnableModeless(fEnable: Integer): HResult;
begin
  Result := E_NOTIMPL;
end;

procedure TExtendBrowser.ExecJScript(const Script: string);
begin
  HTMLWindow2.execScript(Script, 'JavaScript');
end;

function TExtendBrowser.FilterDataObject(const pDO: IDataObject;
  out ppDORet: IDataObject): HResult;
begin
  Result := E_NOTIMPL;
end;

function TExtendBrowser.GetDocument2: IHTMLDocument2;
begin
  Supports(Document, IHTMLDocument2, Result);
end;

function TExtendBrowser.GetDropTarget(const pDropTarget: IDropTarget;
  out ppDropTarget: IDropTarget): HResult;
begin
  Result := E_NOTIMPL;
end;

function TExtendBrowser.GetExternal(out ppDispatch: IDispatch): HResult;
var
  W: TApplicationWrapper;
begin
  W := TApplicationWrapper.Connect(Forms.Application);
  ppDispatch := TAutoObjectDispatch.Create(W) as IDispatch;
  Result := S_OK;
end;

const
  // Constants from mshtmhst.h
  DOCHOSTUIFLAG_DIALOG    = $1;
  DOCHOSTUIFLAG_DISABLE_HELP_MENU = $2;
  DOCHOSTUIFLAG_NO3DBORDER        = $4;
  DOCHOSTUIFLAG_SCROLL_NO = $8;
  DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE   = $10;
  DOCHOSTUIFLAG_OPENNEWWIN        = $20;
  DOCHOSTUIFLAG_DISABLE_OFFSCREEN = $40;
  DOCHOSTUIFLAG_FLAT_SCROLLBAR    = $80;
  DOCHOSTUIFLAG_DIV_BLOCKDEFAULT  = $100;
  DOCHOSTUIFLAG_ACTIVATE_CLIENTHIT_ONLY   = $200;
  DOCHOSTUIFLAG_OVERRIDEBEHAVIORFACTORY   = $400;
  DOCHOSTUIFLAG_CODEPAGELINKEDFONTS       = $800;
  DOCHOSTUIFLAG_URL_ENCODING_DISABLE_UTF8 = $1000;
  DOCHOSTUIFLAG_URL_ENCODING_ENABLE_UTF8  = $2000;
  DOCHOSTUIFLAG_ENABLE_FORMS_AUTOCOMPLETE = $4000;
  DOCHOSTUIFLAG_ENABLE_INPLACE_NAVIGATION = $10000;
  DOCHOSTUIFLAG_IME_ENABLE_RECONVERSION   = $20000;
  DOCHOSTUIFLAG_THEME     = $40000;
  DOCHOSTUIFLAG_NOTHEME   = $80000;
  DOCHOSTUIFLAG_NOPICS    = $100000;
  DOCHOSTUIFLAG_NO3DOUTERBORDER   = $200000;
  DOCHOSTUIFLAG_DISABLE_EDIT_NS_FIXUP	= $400000;
  DOCHOSTUIFLAG_LOCAL_MACHINE_ACCESS_CHECK	= $800000;
  DOCHOSTUIFLAG_DISABLE_UNTRUSTEDPROTOCOL	= $1000000;
  DOCHOSTUIFLAG_ENABLE_ACTIVEX_BLOCK_MODE = $2000000;
  DOCHOSTUIFLAG_ENABLE_ACTIVEX_PROMPT_MODE = $4000000;
  DOCHOSTUIFLAG_ENABLE_ACTIVEX_DEFAULT_MODE = $8000000;

function TExtendBrowser.GetHostInfo(var pInfo: _DOCHOSTUIINFO): HResult;
begin
  FillChar(pInfo, SizeOf(pInfo), 0);
  pInfo.cbSize := SizeOf(_DOCHOSTUIINFO);
  pInfo.dwFlags := DOCHOSTUIFLAG_SCROLL_NO or DOCHOSTUIFLAG_NO3DBORDER or DOCHOSTUIFLAG_ENABLE_FORMS_AUTOCOMPLETE or DOCHOSTUIFLAG_THEME;

  // 스크롤바를 보이게 수정하려면 다음과 같이 한다.
  //pInfo.dwFlags := DOCHOSTUIFLAG_NO3DBORDER or DOCHOSTUIFLAG_ENABLE_FORMS_AUTOCOMPLETE or DOCHOSTUIFLAG_THEME;
  pInfo.dwDoubleClick := 0;
  Result := S_OK;
end;

function TExtendBrowser.GetHTMLWindow2: IHTMLWindow2;
begin
  Result := Document2.parentWindow;
end;

function TExtendBrowser.GetOptionKeyPath(out pchKey: PWideChar; dw: UINT): HResult;
begin
  Result := E_NOTIMPL;
end;

function TExtendBrowser.HideUI: HResult;
begin
  Result := E_NOTIMPL;
end;

procedure TExtendBrowser.Loaded;
begin
  inherited;
end;

function TExtendBrowser.OnDocWindowActivate(fActivate: Integer): HResult;
begin
  Result := E_NOTIMPL;
end;

function TExtendBrowser.OnFrameWindowActivate(fActivate: Integer): HResult;
begin
  Result := E_NOTIMPL;
end;

function TExtendBrowser.ResizeBorder(var prcBorder: tagRECT;
  const pUIWindow: IOleInPlaceUIWindow; fRameWindow: Integer): HResult;
begin
  Result := S_OK;
end;

function TExtendBrowser.ShowContextMenu(dwID: UINT; ppt: PtagPOINT;
  const pcmdtReserved: IInterface; const pdispReserved: IDispatch): HResult;
begin
  Result := E_NOTIMPL;
end;

function TExtendBrowser.ShowUI(dwID: UINT;
  const pActiveObject: IOleInPlaceActiveObject;
  const pCommandTarget: IOleCommandTarget; const pFrame: IOleInPlaceFrame;
  const pDoc: IOleInPlaceUIWindow): HResult;
begin
  Result := S_FALSE;
end;

function TExtendBrowser.TranslateAccelerator(var lpmsg: tagMSG;
  var pguidCmdGroup: TGUID; nCmdID: UINT): HResult;
begin
  Result := E_NOTIMPL;
end;

function TExtendBrowser.TranslateUrl(dwTranslate: UINT; pchURLIn: PWideChar;
  out ppchURLOut: PWideChar): HResult;
begin
  ppchURLOut := nil;
  Result := S_FALSE;
end;

function TExtendBrowser.UpdateUI: HResult;
begin
  Result := S_FALSE;
end;

(* IBrowserApp Interface 구현부*)

function TExtendBrowser.OnReqestRunScript(source : String): String;
begin
  ExecJScript(source);
end;

function TExtendBrowser.OnReqestGetValue(const name : String) : String;
begin
  result := GetElementValue(name);
end;

procedure TExtendBrowser.OnReqestSetValue(const name : String; val : String);
begin
  SetElementValue(name, val);
end;

{ TApplicationWrapper }

procedure TApplicationWrapper.SetCaption(S: String);
begin

end;

function TApplicationWrapper.GetApplication: TApplication;
begin

end;

function TApplicationWrapper.GetCaption: string;
begin

end;


end.
