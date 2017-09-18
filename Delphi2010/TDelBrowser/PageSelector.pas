(*
    제목: PageSelector
    작성자:박성완(adsloader@naver.com)
    작성일:2010.04.26
    목적:  페이지 이벤트 발생시, 각 페이지를 Select하는 모듈
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
    // Event 종류정의
    EVENT_TYPE = (EVT_COMPLETE, EVT_LINK);

    // 메시지 파라메터
    TParamMSG = record
      evtID : EVENT_TYPE;  // EventID
      pData : Pointer;     // Data 전송용
      sData : String;      // Data 전송용 2

    end;

    pStateFUNC = function ( msg : TParamMSG ): Integer of Object;

    // URL별 상태 처리
    PageInfo = record
      sPage   : String;
      fnState : pStateFUNC;
    end;

    // 페이지 이름별로 이벤트 처리
    StateSelector = class
    constructor Create;
    public
      function  BeforeURL(url : String; iApp : IBrowserApp) : boolean;
      procedure DocComplete(iApp : IBrowserApp);

      procedure SetUpStateFunc();

      // State 관련 함수들
      function OnTetrisPage( msg : TParamMSG ): Integer;
      function OnTetrisPage_startgame( app : IBrowserApp): Integer;
      function OnTetrisPage_gameover ( app : IBrowserApp): Integer;
      function OnTetrisPage_getscore ( app : IBrowserApp): Integer;

      function OnUserPage  ( msg : TParamMSG ): Integer;

      // 점수출력
      function DisplayScore() :String;
    public

      // 페이지관련 StateHandler 설정값들.
      PAGES   : array [1..2] of PageInfo;
      pCurFunc: pStateFUNC;
      bIsRegisted: boolean;

      // DB 관련
      DB   : IDBManager;
    end;

implementation

constructor StateSelector.Create;
var
  sql : String;
begin
  // 기본값 설정
  SetUpStateFunc();

  // DB 생성(구현상속)
  DB := TDBManager.Create(nil);

  // 1개의 생성후, 클래스를 공유해서 쓰도록한다. (연결설정중복방지)
  DB.connect( ExtractFilePath( ParamStr(0) ) + sDBName );
end;

// 기본정보 세팅
procedure StateSelector.SetUpStateFunc();
begin

  // URL 초기화
  PAGES[1].sPage   := 'Tetris.html';
  PAGES[1].fnState := OnTetrisPage;

  PAGES[2].sPage   := 'user.html';
  PAGES[2].fnState := OnUserPage;

  pCurFunc := OnTetrisPage;
end;

(********************************************************************)
(* Page별 처리 함수*)

// startgame 요청
function StateSelector.OnTetrisPage_startgame( app : IBrowserApp ): Integer;
var
  sResult : String;
begin

  sResult := TimeToStr( Now() );
  sResult := sResult + '에 시작';
  App.OnReqestSetValue('CGIRESULT', sResult);

  App.OnReqestRunScript('WriteHTML()');
  sResult := App.OnReqestGetValue('CGIRESULT');

end;

// game over 요청
function StateSelector.OnTetrisPage_gameover( app : IBrowserApp ): Integer;
var
  sResult : String;
  sSQL    : String;
  sUserID, sScore, sLevel, sLines, sTime, sApm : String;
  nStart, nEnd : Integer;

  // 문자열을 잘라넘겨준다.
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

  // 최고점수를 보여준다.
  sResult := DisplayScore();
  App.OnReqestSetValue('CGIRESULT', sResult);
  App.OnReqestRunScript('WriteHTML()');

end;

// 순위 DB 정보가져오기
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
  // 마지막 문자는 제외한다.
  sResult := copy(sResult,  1, length(sResult) -1 );

  // CGIRESULT2에 저장한다.
  App.OnReqestSetValue('CGIRESULT2', sResult);

end;

// Tetris page의 이벤트핸들러 메인
function StateSelector.OnTetrisPage  ( msg : TParamMSG ): Integer;
type
  pJScriptFUNC = function ( app : IBrowserApp ): Integer of Object;
var
  iApp   : IBrowserApp;
  sResult: String;
  I      : Integer;
  pFunc  : pJScriptFUNC;

  // 등록된 이름별 함수를 리턴하는 내부함수
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

    // JScript에서 호출된 함수 실행
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
    sResult := sResult  + '<tr><td>유저이름:</td><td><b style = "color:#ACEEFF;">'
              + DB.GetValue(I, 0) + '</b></td><tr></tr><td> 게임횟수:</td><td><b style = "color:red;">' + DB.GetValue(I, 1)
              + '</b></td></tr>';

    // 5위까지만 보여주겠다.
    if I = 5 then break;

  end;

  sResult := sResult + '</table>';

  iApp.OnReqestSetValue('CGIRESULT', sResult);
  iApp.OnReqestRunScript('WriteHTML()');

end;
(********************************************************************)

// 화면에 HTML 출력
function StateSelector.DisplayScore() :String;
var
  sResult : String;
begin
   DB.ExcuteSQL('select userid, score, gamelevel, RegDay from t_score order by score desc', stDCL);
   sResult := sResult + '<table><tr><td>최고점수유저:</td><td><b style = "color:#AAEEFF;">'
              + DB.GetValue(1, 0) + '</b></td><tr></tr><td> 점수:</td><td>' + DB.GetValue(1, 1)
              + '</td></tr><tr><td>게임레벨:</td><td>' + DB.GetValue(1, 2) + '</td><tr></table>';

   result := sResult;
end;

// 문자열 분석
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

  (* PAGES 배열의 크기는 어떻게 구하지..High()*)
  for I := 1 to High(PAGES) do begin
    sName := ExtractFilePath( ParamStr(0) );
    sName := sName + PAGES[I].sPage;
    if Pos(sName, url) = 1 then begin
      pCurFunc := pStateFUNC( PAGES[I].fnState );
      bIsRegisted := true;
      exit;
    end;
  end;

  // apps:// 문자열인지 채크한다.
  if Pos(APP_STRING, url) <> 1 then Exit;

  nSizeURL := length(url);
  nSizeAPP := length(APP_STRING);
  sCommand := copy (url,  nSizeAPP + 1, nSizeURL - nSizeAPP - 1 );

  pParam.evtID := EVT_LINK;
  pParam.pData := Pointer(iApp);
  pParam.sData := sCommand;
  pCurFunc(pParam);

  // 네비게이션을 취소한다.
  result:= true;
end;

// 문서완료
procedure StateSelector.DocComplete(iApp : IBrowserApp);
var
  pParam   : TParamMSG;
begin

  // 로딩순서를 나중에 잡아야 한다 그래서 무조건 PASS로 했음.
  //if bIsRegisted = false then exit;
  
  pParam.evtID := EVT_COMPLETE;
  pParam.pData := Pointer(iApp);
  pCurFunc(pParam);
end;

end.
