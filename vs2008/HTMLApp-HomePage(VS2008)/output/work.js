//---------------------------------------------------------------------------
// 정보 만들기 
function UpdateInfo(pno)
{
    var wFile = new JFile();
    wFile.Create(API_GetCurFolder() + "\\parameter\\work_update.txt");
    wFile.Write(pno);
    wFile.Close();
    
    location.href ="work_update.html";
}

// Project명 
function GetProjectName()
{
    UI_CLEAR_HTML();
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "select name, detail_info from t_project_name order by p_no desc";
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    var nCount = 0;
    while(Db.GetRow() =="continue"){
        UI_ADD_HTML("<tr>");
       
        UI_ADD_HTML("<td width = '40'><div style = \"font-size:9pt;\"> <img src = \"image/041.gif\" border = 0> "); 
        UI_ADD_HTML(Db.GetValue(0)); 
        
        if(nCount > 1){
            break;
        }
        
        UI_ADD_HTML("</div></td>"); 
        UI_ADD_HTML( "</tr>" );
        nCount++;
        
    }
    
    UI_ADD_HTML(" <a href = 'project.html'>...▶</a>");             
    
    UI_ATTACH_BOARD(1);
}

// 네비게이션의 지표가 되는 값
var step_navi = 5;
var pNavi     = new Array();
var nNaviIndx = 0;
function SearchResultDisplay(sPattern, pIndx, bDierction)
{
    
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sWhere = (pIndx == -1) ? " " : (" b.pno < " + pIndx + " and " );
    var sql = "SELECT b.pno AS 번호, a.name AS 프로젝트명, b.title AS 제목, c.title AS 종류, b.filepath AS 경로명, b.detailinfo AS 상세설명, b.MakeTime " 
               +"FROM t_project_name AS a, t_project_data AS b, t_basic AS c "
               +"WHERE (b.title      like '%" + sPattern + "%' or  "
               +"       b.filepath   like '%" + sPattern + "%' or  "
               +"       b.detailinfo like '%" + sPattern + "%') and "
               + sWhere
               +"a.p_no=b.f_project And b.f_spec=c.pno order by b.pno desc";
    
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    if(bDierction == 1){
        pNavi[nNaviIndx++] = pIndx;     
        pNavi[nNaviIndx]   = -1;
    } else {
        if(nNaviIndx > 0) nNaviIndx--; 
    }		 
    
    var nRowCNT = 0;
    while(Db.GetRow() =="continue"){
        
        // 네비게이션 용 위치값 저장( 정렬순서에 따라 값이 달라진다. desc, order by)
        if(nRowCNT == step_navi - 1 )   pNavi[nNaviIndx] = Db.GetValue(0);
        
        nRowCNT++;
        
        UI_ADD_HTML("<tr>");
       
        UI_ADD_HTML("<td width = '40'><div style = \"font-size:9pt;\">"); 
        UI_ADD_HTML(Db.GetValue(0)); 
        UI_ADD_HTML("</div></td>"); 
        
        UI_ADD_HTML("<td><div style = \"font-size:9pt;\"> "); 
        UI_ADD_HTML(Db.GetValue(1)); 
        UI_ADD_HTML("</div></td>"); 
        
        UI_ADD_HTML("<td><div style = \"font-size:9pt;\"> "); 
        
        // 컨텐츠 정보 보여주기 
        var str     = Db.GetValue(5)
        str         = str.replace(/\r\n/gi, "<br>");
        str         = str.replace(/ /gi, "&nbsp"); 
        
        var str2    = Db.GetValue(4);
        str2        = str2.replace(/'/gi, " ");

        
        var sUpdateLink  = "<a href =\"#\" onclick = \"UpdateInfo(" + Db.GetValue(0) + ");\">-수정하기</a>";
        var sContentInfo = "<div style = 'color:black; text-decoration: BOLD;'>"
                           +"<B>제목:"  + Db.GetValue(2) + "(" + Db.GetValue(3) + ")</B>" + sUpdateLink + "</div> "
                           +"시작:"  + Db.GetValue(6)           
                           +  "<br><br>"+ str + "<br>"
                           
                           + "<br>file:<a href= \"#\" onclick='API_excute(\"" + str2 +"\")'> "
                           +  Db.GetValue(4) + "</a><br>";
                           
        
        UI_ADD_HTML(sContentInfo); 
        UI_ADD_HTML("</div></td>"); 
        
        UI_ADD_HTML( "</tr>" );
        
        UI_ADD_HTML( "<tr><td colspan=3 background=\"image/list_back.gif\"></td></tr>" );  
        
        // 크기넘어가면 출력안함.
        if( nRowCNT > step_navi - 1) break;                
    }
        

}

function GetProjectData(pIndx, bDierction)
{
    UI_CLEAR_HTML();

    UI_ADD_HTML("<table border=\"0\" width=\"560\">");
    UI_ADD_HTML("<tr bgcolor=\"#555555\">");
    UI_ADD_HTML("<td width=\"30\">    <font face=\"굴림체\"  color = white><span style=\"font-size:9pt;\">번호</span></font></td>");
    UI_ADD_HTML("<td width=\"130\">   <font face=\"굴림체\"  color = white><span style=\"font-size:9pt;\">Project</span></font></td>");
    UI_ADD_HTML("<td width=\"300\">   <font face=\"굴림체\"  color = white><span style=\"font-size:9pt;\">설명</span></font></td>");
    UI_ADD_HTML("</tr>");
    
    // 화면출력
    SearchResultDisplay(query.value, pIndx, bDierction);

    UI_ADD_HTML("</table>");
    
    // Navigation 출력
    var prev = pNavi[nNaviIndx - 2];
    var next = pNavi[nNaviIndx]; 
    if(prev) 
        UI_ADD_HTML("<a href = '#' onclick = 'GetProjectData("+ pNavi[nNaviIndx - 2] +  ", 0);'><</a>");
    if(next && next != -1) 
        UI_ADD_HTML("<a href = '#' onclick = 'GetProjectData("+ pNavi[nNaviIndx]     +  ", 1);'>></a>");
    
    UI_ATTACH_BOARD(2);           
    
}

// Main 함수 - 처음실행
function OnJMainStart(sParam)
{
    GetProjectName(); 
    GetProjectData(-1, 1);  
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


