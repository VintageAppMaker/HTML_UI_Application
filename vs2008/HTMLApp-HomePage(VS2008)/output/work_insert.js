//---------------------------------------------------------------------------
// 정보 만들기 

// Main 함수 - 처음실행
function OnJMainStart(sParam)
{
    // 오늘날짜 입력
    var today = new Date();
    P_START_DATE.value = today.getYear()  + "-" + ( today.getMonth() + 1 ) + "-" + today.getDate();
    P_END_DATE.value = today.getYear()  + "-" + ( today.getMonth() + 1 ) + "-" + today.getDate();
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
    
    var sql = "insert into t_project_name(name, state, StartTime, EndTime, detail_info, f_spec) values( "
              + "'" + sName     + "', "
              + nSpec           + ",  "
              + "CDate('" + sDate  + "'), "
              + "CDate('" + sDate2 + "'), "
              + "'" + sDetail   + "', 0 "
              +")"; 
              
    Db.SQL(sql);    
    
    alert("입력완료되었습니다.");
}
	


