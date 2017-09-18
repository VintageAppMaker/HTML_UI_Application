//---------------------------------------------------------------------------
// 정보 만들기 
var pIndx_spec = new Array(); // pno 용 배열
var pIndx_proj = new Array(); // pno 용 배열

var g_pNo = -1;  // Primary Key

// 프로젝트명 추가하기 
function AddProjectNameInfo()
{
    UI_CLEAR_HTML();
    
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "select p_no, name from t_project_name";
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    var i = 0;
    UI_ADD_HTML("<select id = \"P_PROJECT\" style='width:197px;font-size:12px;font-family:돋움;' name=rcsection>");
    while(Db.GetRow() =="continue"){
        UI_ADD_HTML("<option value=>" + Db.GetValue(1) +"</option>");
        pIndx_proj[i] = Db.GetValue(0);    
        i++;        
    }
    UI_ADD_HTML("</select>");
    UI_ATTACH_BOARD(2);
}

// 종류추가하기 
function AddSpecNameInfo()
{
    UI_CLEAR_HTML();
    
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "select pno, title from t_basic where type = 0";
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    var i = 0;
    UI_ADD_HTML("<select id = \"P_SPEC\" style='width:197px;font-size:12px;font-family:돋움;' name=rcsection>");
    while(Db.GetRow() =="continue"){
        UI_ADD_HTML("<option value=>" + Db.GetValue(1) +"</option>");
        pIndx_spec[i] = Db.GetValue(0);    
        i++;        
    }
    UI_ADD_HTML("</select>");
    UI_ATTACH_BOARD(1);
}


// Main 함수 - 처음실행
function OnJMainStart(sParam)
{
    // 기본정보 처리
    AddSpecNameInfo();
    AddProjectNameInfo();    
    
    // 기준정보 화면에 표시함. 
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
	    

function GetParamInfo()
{
    var rFile = new JFile();
    rFile.Open(API_GetCurFolder() + "\\parameter\\work_update.txt");
    var pno   = rFile.Read();
    g_pNo     = pno;  
    rFile.Close();
    
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "select title, f_spec, f_project, detailinfo,  MakeTime from t_project_data where pno = " + pno;
    
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    while(Db.GetRow() =="continue"){
        P_NAME.value            =  Db.GetValue(0);
        
        for(i =0; i < pIndx_spec.length; i++){
            if( pIndx_spec[i]  == Db.GetValue(1)) P_SPEC.selectedIndex = i;
        }
        for(i =0; i < pIndx_proj.length; i++){
            if( pIndx_proj[i]  == Db.GetValue(2)) P_PROJECT.selectedIndex = i;
        }
        
        P_DETAIL.value          =  Db.GetValue(3);
        P_START_DATE.value      =  Db.GetValue(4);
    }
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
function OnSave()
{
    // MakeFolder
    
    // 특수문자 제거하기
    var sDetail   = chkInvalidChar( P_DETAIL.value );
    var sName     = chkInvalidChar( P_NAME.value );
    var sDate     = chkInvalidChar( P_START_DATE.value );
    var nSpec     = pIndx_spec[P_SPEC.selectedIndex];
    var nProj     = pIndx_proj[P_PROJECT.selectedIndex];
    
    
    // DB 입력하기
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "update t_project_data set " 
              + "title  = '"   + sName     + "', "
              + "f_spec ="     + nSpec     + ",  "
              + "f_project="   + nProj     + ",  "
              + "detailinfo='" + sDetail   + "', "
              
              + "MakeTime = CDate('" + sDate + "') "
              + " where pno = "+ g_pNo; 
    
    Db.SQL(sql);    
    
    alert("수정완료되었습니다..");
}
	
function OnDelete()
{
    if( prompt("지우려면 yes를 입력하세요", "no")  != "yes") return;
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "delete from t_project_data  where pno = " + g_pNo; 
    Db.SQL(sql);    
    
    alert("삭제되었습니다..");
}


