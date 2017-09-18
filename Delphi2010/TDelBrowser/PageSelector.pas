(*
    ����: PageSelector
    �ۼ���:�ڼ���(adsloader@naver.com)
    �ۼ���:2010.04.26
    ����:  ������ �̺�Ʈ �߻���, �� �������� Select�ϴ� ���
*)
unit PageSelector;

interface
uses
  iAppBrowser, Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, OleCtrls , TDBEng, iDBEng;

const
  sURLTemplate : String = 'apps://';
  sDBName      : String = 'TodayDB.mdb';

type
    // Event ��������
    EVENT_TYPE = (EVT_COMPLETE, EVT_LINK);

    // �޽��� �Ķ����
    TParamMSG = record
      evtID : EVENT_TYPE;  // EventID
      pData : Pointer;     // Data ���ۿ�
      sData : String;      // Data ���ۿ� 2

    end;

    pStateFUNC = function ( msg : TParamMSG ): Integer of Object;

    // URL�� ���� ó��
    PageInfo = record
      sPage   : String;
      fnState : pStateFUNC;
    end;

    // ������ �̸����� �̺�Ʈ ó��
    StateSelector = class
    constructor Create;
    public
      function  BeforeURL(url : String; iApp : IBrowserApp) : boolean;
      procedure DocComplete(iApp : IBrowserApp);

      procedure SetUpStateFunc();

      // State ���� �Լ���
      function OnTetrisPage( msg : TParamMSG ): Integer;
      function OnTetrisPage_startgame( app : IBrowserApp): Integer;
      function OnTetrisPage_gameover ( app : IBrowserApp): Integer;
      function OnTetrisPage_getscore ( app : IBrowserApp): Integer;

      function OnUserPage  ( msg : TParamMSG ): Integer;

      // �������
      function DisplayScore() :String;
    public

      // ���������� StateHandler ��������.
      PAGES   : array [1..2] of PageInfo;
      pCurFunc: pStateFUNC;
      bIsRegisted: boolean;

      // DB ����
      DB   : IDBManager;
    end;

implementation

constructor StateSelector.Create;
var
  sql : String;
begin
  // �⺻�� ����
  SetUpStateFunc();

  // DB ����(�������)
  DB := TDBManager.Create(nil);

  // 1���� ������, Ŭ������ �����ؼ� �������Ѵ�. (���ἳ���ߺ�����)
  DB.connect( ExtractFilePath( ParamStr(0) ) + sDBName );
end;

// �⺻���� ����
procedure StateSelector.SetUpStateFunc();
begin

  // URL �ʱ�ȭ
  PAGES[1].sPage   := 'Tetris.html';
  PAGES[1].fnState := OnTetrisPage;

  PAGES[2].sPage   := 'user.html';
  PAGES[2].fnState := OnUserPage;

  pCurFunc := OnTetrisPage;
end;

(********************************************************************)
(* Page�� ó�� �Լ�*)

// startgame ��û
function StateSelector.OnTetrisPage_startgame( app : IBrowserApp ): Integer;
var
  sResult : String;
begin

  sResult := TimeToStr( Now() );
  sResult := sResult + '�� ����';
  App.OnReqestSetValue('CGIRESULT', sResult);

  App.OnReqestRunScript('WriteHTML()');
  sResult := App.OnReqestGetValue('CGIRESULT');

end;

// game over ��û
function StateSelector.OnTetrisPage_gameover( app : IBrowserApp ): Integer;
var
  sResult : String;
  sSQL    : String;
  sUserID, sScore, sLevel, sLines, sTime, sApm : String;
  nStart, nEnd : Integer;

  // ���ڿ��� �߶�Ѱ��ش�.
  function ParsingCMD() : String;
  begin
    nStart  := 1;
    nEnd    := pos('|', sResult) - 1;
    result  := copy(sResult, nStart, nEnd);
    sResult := copy(sResult, nEnd + 2, 1000);
  end;

begin

  sResult := App.OnReqestGetValue('CGIRESULT');

  sScore := ParsingCMD();
  sLines := ParsingCMD();
  sLevel := ParsingCMD();
  sApm   := ParsingCMD();
  sTime  := ParsingCMD();
  sUserID:= ParsingCMD();

  sSQL := 'insert into T_SCORE(userid, score, gamelevel, lines, gametime, apm) values(' +
          '"' + sUserID + '",'
          + sScore  + ','
          + sLevel  + ','
          + sLines  + ','
          + sTime   + ','
          + sApm    + ')' ;

  DB.ExcuteSQL(sSQL, stDML);

  // �ְ������� �����ش�.
  sResult := DisplayScore();
  App.OnReqestSetValue('CGIRESULT', sResult);
  App.OnReqestRunScript('WriteHTML()');

end;

// ���� DB ������������
function StateSelector.OnTetrisPage_getscore ( app : IBrowserApp): Integer;
const
  MAXCNT : Integer = 10;
var
  sSQL : String;
  I    : Integer;

  sResult: String;
  nMax   : Integer;

begin
  sSQL := 'select userid, score from t_score order by score desc' ;
  DB.ExcuteSQL(sSQL, stDCL);

  nMax := DB.GetRowCount();
  if nMax > MAXCNT then begin
    nMax := MAXCNT;
  end;

  for I := 1 to nMax do begin
    sResult := sResult + DB.GetValue(I, 0) + ':' + DB.GetValue(I, 1) + '|';
  end;
  // ������ ���ڴ� �����Ѵ�.
  sResult := copy(sResult,  1, length(sResult) -1 );

  // CGIRESULT2�� �����Ѵ�.
  App.OnReqestSetValue('CGIRESULT2', sResult);

end;

// Tetris page�� �̺�Ʈ�ڵ鷯 ����
function StateSelector.OnTetrisPage  ( msg : TParamMSG ): Integer;
type
  pJScriptFUNC = function ( app : IBrowserApp ): Integer of Object;
var
  iApp   : IBrowserApp;
  sResult: String;
  I      : Integer;
  pFunc  : pJScriptFUNC;

  // ��ϵ� �̸��� �Լ��� �����ϴ� �����Լ�
  function SearcbyByName(fname : String) : pJScriptFUNC;
  begin
    result := nil;

    if pos(fname, 'startgame') = 1 then begin
      result := OnTetrisPage_startgame;
    end;

    if pos(fname, 'gameover')  = 1 then begin
      result := OnTetrisPage_gameover;
    end;

    if pos(fname, 'getscore')  = 1 then begin
      result := OnTetrisPage_getscore;
    end;
  end;

begin

  iApp := IBrowserApp(msg.pData);

  if msg.evtID = EVT_COMPLETE then begin
    sResult := DisplayScore();
    iApp.OnReqestSetValue('CGIRESULT', sResult);
    iApp.OnReqestRunScript('WriteHTML()');

  end else
  begin
    pFunc := SearcbyByName(msg.sData);
    if @pFunc = nil then begin Exit end;

    // JScript���� ȣ��� �Լ� ����
    pFunc(iApp);

  end;

end;

function StateSelector.OnUserPage( msg : TParamMSG ): Integer;
var
  iApp    : IBrowserApp;
  sResult : String;
  I       : Integer;
begin
  iApp := IBrowserApp(msg.pData);

  DB.ExcuteSQL('select userid, count(userid) from t_score group by userid order by count(userid) desc', stDCL);
  sResult := '<table>';
  for I := 1 to DB.GetRowCount()  do begin
    sResult := sResult  + '<tr><td>�����̸�:</td><td><b style = "color:#ACEEFF;">'
              + DB.GetValue(I, 0) + '</b></td><tr></tr><td> ����Ƚ��:</td><td><b style = "color:red;">' + DB.GetValue(I, 1)
              + '</b></td></tr>';

    // 5�������� �����ְڴ�.
    if I = 5 then break;

  end;

  sResult := sResult + '</table>';

  iApp.OnReqestSetValue('CGIRESULT', sResult);
  iApp.OnReqestRunScript('WriteHTML()');

end;
(********************************************************************)

// ȭ�鿡 HTML ���
function StateSelector.DisplayScore() :String;
var
  sResult : String;
begin
   DB.ExcuteSQL('select userid, score, gamelevel, RegDay from t_score order by score desc', stDCL);
   sResult := sResult + '<table><tr><td>�ְ���������:</td><td><b style = "color:#AAEEFF;">'
              + DB.GetValue(1, 0) + '</b></td><tr></tr><td> ����:</td><td>' + DB.GetValue(1, 1)
              + '</td></tr><tr><td>���ӷ���:</td><td>' + DB.GetValue(1, 2) + '</td><tr></table>';

   result := sResult;
end;

// ���ڿ� �м�
function  StateSelector.BeforeURL(url : String; iApp : IBrowserApp) : boolean;
const
  APP_STRING : String = 'apps://';
var
  I        : Integer;
  nSize    : Integer;

  nSizeURL, nSizeAPP : Integer;

  sNAME    : String;
  sCommand : String;
  pParam   : TParamMSG;

begin

  result := false;

  bIsRegisted := false;

  (* PAGES �迭�� ũ��� ��� ������..High()*)
  for I := 1 to High(PAGES) do begin
    sName := ExtractFilePath( ParamStr(0) );
    sName := sName + PAGES[I].sPage;
    if Pos(sName, url) = 1 then begin
      pCurFunc := pStateFUNC( PAGES[I].fnState );
      bIsRegisted := true;
      exit;
    end;
  end;

  // apps:// ���ڿ����� äũ�Ѵ�.
  if Pos(APP_STRING, url) <> 1 then Exit;

  nSizeURL := length(url);
  nSizeAPP := length(APP_STRING);
  sCommand := copy (url,  nSizeAPP + 1, nSizeURL - nSizeAPP - 1 );

  pParam.evtID := EVT_LINK;
  pParam.pData := Pointer(iApp);
  pParam.sData := sCommand;
  pCurFunc(pParam);

  // �׺���̼��� ����Ѵ�.
  result:= true;
end;

// �����Ϸ�
procedure StateSelector.DocComplete(iApp : IBrowserApp);
var
  pParam   : TParamMSG;
begin

  // �ε������� ���߿� ��ƾ� �Ѵ� �׷��� ������ PASS�� ����.
  //if bIsRegisted = false then exit;
  
  pParam.evtID := EVT_COMPLETE;
  pParam.pData := Pointer(iApp);
  pCurFunc(pParam);
end;

end.
