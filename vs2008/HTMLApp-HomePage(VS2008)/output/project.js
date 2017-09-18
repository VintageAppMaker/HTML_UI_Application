//---------------------------------------------------------------------------
// 정보 만들기 
var nTotalData = 0;// 전체 데이터
var nTotalProj = 0;// 전체 프로젝트 개수

function UpdateInfo(pno)
{
    var wFile = new JFile();
    wFile.Create(API_GetCurFolder() + "\\parameter\\work_update2.txt");
    wFile.Write(pno);
    wFile.Close();
    
    location.href ="project_update.html";
}

// Project명 
function GetProjectInfo()
{
    UI_CLEAR_HTML();
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    // 총 카운트 - 프로젝트
    var sql = "select count(name) from t_project_name";
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;

    while(Db.GetRow() =="continue"){
        nTotalProj = Db.GetValue(0);
    }
    
    // 총 카운트 - data
    sql = "select count(pno) from t_project_data";
    sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    while(Db.GetRow() =="continue"){
        nTotalData = Db.GetValue(0);
    }
    
    UI_ADD_HTML("<tr>");
    UI_ADD_HTML("<td width = '40'><div style = \"font-size:9pt;\"> <img src = \"image/041.gif\" border = 0> "); 
    UI_ADD_HTML("전체 Project: " + nTotalProj); 
    UI_ADD_HTML("</div></td>"); 
    UI_ADD_HTML( "</tr>" );        

    UI_ADD_HTML("<tr>");
    UI_ADD_HTML("<td width = '40'><div style = \"font-size:9pt;\"> <img src = \"image/041.gif\" border = 0> "); 
    UI_ADD_HTML("전체  Data: " + nTotalData); 
    UI_ADD_HTML("</div></td>"); 
    UI_ADD_HTML( "</tr>" );   
            
    UI_ATTACH_BOARD(1);
}

var sTitle = new Array("완료", "진행중", "미완료(종료)");
var sColor = new Array("red",  "green",  "blue");
function SearchResultDisplay()
{
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    // outer join을 해야 한다.
    var sql = "SELECT  a.p_no, a.name, a.detail_info, a.StartTime, a.EndTime, a.state, count(b.pno) as 개수 "
             +"FROM t_project_name AS a left outer join t_project_data AS b on a.p_no=b.f_project"
             +" GROUP BY a.p_no, a.name, a.detail_info, a.StartTime, a.EndTime, a.state "
             +" ORDER BY a.p_no DESC; "
             
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    while(Db.GetRow() =="continue"){
        UI_ADD_HTML("<tr>");
       
        UI_ADD_HTML("<td width = '40'><div style = \"font-size:9pt;\">"); 
        UI_ADD_HTML(Db.GetValue(0)); 
        UI_ADD_HTML("</div></td>"); 
        
        UI_ADD_HTML("<td><div style = \"font-size:9pt;\"> "); 
        UI_ADD_HTML(Db.GetValue(1)); 
        UI_ADD_HTML("</div></td>"); 
        
        UI_ADD_HTML("<td><div style = \"font-size:9pt;\"> "); 
        
        UI_ADD_HTML("<pre>"); 
        UI_ADD_HTML(Db.GetValue(2)); 
        UI_ADD_HTML("</pre>");
        
        UI_ADD_HTML("시작일:" + Db.GetValue(3) + "<BR>종료일:" + Db.GetValue(4));
        UI_ADD_HTML("<br>상태:<b>" + sTitle[Db.GetValue(5)] + "</b><a href = '#' onclick = 'UpdateInfo(" + Db.GetValue(0) + ");'>->수정하기</a><br><br>");  
        
        // graph 처리
        var nPercent  = 0.001; // 소스값 처리하기 위해서
        nPercent      = (Db.GetValue(6) / nTotalData) * 100;
        
        // 자리수 처리
        var sPercent = "";
        sPercent += nPercent;
        var nSize = (sPercent.length > 4) ?  4 : sPercent.length;
        sPercent  = sPercent.substr(0, nSize);
        
        var nIndx = 0;
        if(nPercent < 30 ){
            nIndx = 0;
        } else if(nPercent >= 30 && nPercent < 60){
            nIndx = 1;
        } else{
            nIndx = 2;
        }        
        
        UI_ADD_HTML("전체중 " + sPercent + "% " 
                    +"<div id = 'graph' style = 'font-familiy: 굴림; font-size: 10pt; color: #CAAAEE; "
                    + "background-color: " + sColor[nIndx] + "; width:" 
                    + nPercent
                    + "'></div>"                            
        );
                
        UI_ADD_HTML( "</tr>" );        
        UI_ADD_HTML( "<tr><td colspan=3 background=\"image/list_back.gif\"></td></tr>" );  
        
    }        

}

function GetProjectName()
{
    UI_CLEAR_HTML();

    UI_ADD_HTML("<table border=\"0\" width=\"560\">");
    UI_ADD_HTML("<tr bgcolor=\"#555555\">");
    UI_ADD_HTML("<td width=\"30\">    <font face=\"굴림체\"  color = white><span style=\"font-size:9pt;\">번호</span></font></td>");
    UI_ADD_HTML("<td width=\"130\">   <font face=\"굴림체\"  color = white><span style=\"font-size:9pt;\">Project</span></font></td>");
    UI_ADD_HTML("<td width=\"300\">   <font face=\"굴림체\"  color = white><span style=\"font-size:9pt;\">설명</span></font></td>");
    UI_ADD_HTML("</tr>");
    
    // 화면출력
    SearchResultDisplay();

    UI_ADD_HTML("</table>");
    UI_ATTACH_BOARD(2);           
    
}

// Main 함수 - 처음실행
function OnJMainStart(sParam)
{
    GetProjectInfo();
    GetProjectName();        
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


