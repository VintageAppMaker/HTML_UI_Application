//---------------------------------------------------------------------------
var g_pNo = -1;
// 정보 만들기 
function GetParamInfo()
{
    var rFile = new JFile();
    rFile.Open(API_GetCurFolder() + "\\parameter\\work_update2.txt");
    var pno   = rFile.Read();
    g_pNo     = pno;  
    rFile.Close();
    
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "select name, StartTime, EndTime, detail_info,  state from t_project_name where p_no = " + pno;
    
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    while(Db.GetRow() =="continue"){
        P_NAME.value            =  Db.GetValue(0);
        P_START_DATE.value      =  Db.GetValue(1);
        P_END_DATE.value        =  Db.GetValue(2);
        P_DETAIL.value          =  Db.GetValue(3);
        P_SPEC.selectedIndex    =  Db.GetValue(4);
    }
}

// Main 함수 - 처음실행
function OnJMainStart(sParam)
{
    // 오늘날짜 입력
    GetParamInfo();
}
    
function chkInvalidChar(str)
{
    var str2;
    // \ 문자 처리하기 
    str2 = str.replace(/\\/gi, "\\\\");
    str = str2; 
    
    // ' 문자 처리하기 
    str2 = str.replace(/\'/gi, "\'\'");
    str = str2;    
    
    // ' 문자 처리하기 
    //str2 = str.replace(/\"/gi, "\'");
    //str = str2; 
    
    return str; // call by ref을 어떻게 처리하지..?
}
	    
//---------------------------------------------------------------------------
// main 함수
// nState: 상태 
// sParam: 파라메터

function JMain(nState, sParam)
{
    if(nState == 0){ OnJMainStart(sParam) };
}

//---------------------------------------------------------------------------
// callback 함수(Search, 기타등등)
function OnSave()
{
    // 특수문자 제거하기
    var sDetail   = chkInvalidChar( P_DETAIL.value );
    var sName     = chkInvalidChar( P_NAME.value );
    var sDate     = chkInvalidChar( P_START_DATE.value );
    var sDate2    = chkInvalidChar( P_END_DATE.value );
    var nSpec   = P_SPEC.selectedIndex;
    
    
    // DB 입력하기
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "update t_project_name set " //(name, state, StartTime, EndTime, detail_info, f_spec) values(
              + "name = '" + sName     + "', "
              + "state=  " + nSpec     + ",  "
              + "StartTime = CDate('" + sDate  + "'), "
              + "EndTime = CDate('" + sDate2 + "'), "
              + "detail_info = '" + sDetail   + "' "
              +"where p_no =" + g_pNo; 
              
    Db.SQL(sql);    
    
    alert("입력완료되었습니다.");
}
	


