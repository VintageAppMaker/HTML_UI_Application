//---------------------------------------------------------------------------
// 정보 만들기 
var pIndx_spec = new Array(); // pno 용 배열
var pIndx_proj = new Array(); // pno 용 배열


// 종류추가하기 
function AddSpecNameInfo()
{
    UI_CLEAR_HTML();
    
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "select pno, title from t_basic where type = 1";
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
    // MakeFolder
    var today = new Date();
    var sDbPath = "PDS\\"
                  + today.getYear()  + "-" 
                  + today.getMonth() + "-" 
                  + today.getDate() +  "["
                  + today.getHours() +  " "
                  + today.getMinutes() +  " "
                  + today.getSeconds() + "]";
                  
    var sFolderName     = API_GetCurFolder() + "\\" + sDbPath;
    
    API_CreateFolder(sFolderName);
    
    // FileCopy
    var sCurFolder = API_GetCurFolder();
    var sOrgFile   = P_FILE_PATH.value;
    var nIdx       = sOrgFile.lastIndexOf("\\");
    var sfileName  = sOrgFile.substring(nIdx + 1,  1000); // 자바스크립트는 알아서 해결해주더라..ㅋㅋ
    
    // ' 문자  스페이스로 처리 & 복사 
    sfileName        = sfileName.replace(/'/gi, " ");
    API_CopyFile(sOrgFile, sFolderName + "\\" + sfileName);
    
    var sDBRelativeFileName = sDbPath + "\\" + sfileName;
    // 특수문자 제거하기
    var sDetail   = chkInvalidChar( P_DETAIL.value );
    var sName     = chkInvalidChar( P_NAME.value );
    var sFilePath = chkInvalidChar( sDBRelativeFileName ) ;
    
    var nSpec   = pIndx_spec[P_SPEC.selectedIndex];
    
    // 파일 등록하지 않을 경우 디폴트 화면
    var nSize = 0;
    sChkPath = sOrgFile.replace(/ /gi, "");
    nSize = sOrgFile.length;
    if(nSize == 0){  
        sFilePath = "image\\nodisplay.jpg";
    }    
    
    // DB 입력하기
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "insert into t_scrap_data(title, f_spec, detailinfo, filepath) values( "
              + "'" + sName     + "', "
              + nSpec           + ",  "
              + "'" + sDetail   + "', "
              + "'" + sFilePath + "'"
              +" )"; 
              
    if( Db.SQL(sql) == "true") alert("입력완료되었습니다.");
}
	


