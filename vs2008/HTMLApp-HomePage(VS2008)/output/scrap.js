//---------------------------------------------------------------------------
// 정보 만들기 
function ViewDetail(no)
{
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    var sql = "SELECT a.title AS 제목, a.filepath AS 경로명, a.detailinfo AS 상세설명, b.title as 종류 " 
               +"FROM t_scrap_data a, t_basic b "
               +"WHERE a.pno = " + no
               +"      and a.f_spec = b.pno " 
               +" order by a.pno desc";
      
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    var sOutput = "<HTML><HEAD><BODY  style = 'background-color: #FFFFFA; color: black; font-familiy:굴림; font-size: 10pt;'>";
    while(Db.GetRow() =="continue"){
        sOutput += "<td><div style = \"font-size:9pt; color: black; width: 600; font-familiy:굴림;\"> "; 
        sOutput += "제목:" + Db.GetValue(0) + "-" + Db.GetValue(3) +"<hr>"; 
        sOutput += "<img src = '" + API_GetCurFolder() + "\\" + Db.GetValue(1)  +"'><br>";
        
        var str     = Db.GetValue(2)
        str         = str.replace(/\r\n/gi, "<br>");
        str         = str.replace(/ /gi, "&nbsp"); 
        str         = str.replace(/\t/gi, "&nbsp&nbsp&nbsp&nbsp"); 
        
        sOutput += " " + str  + " " +"<hr>";
    }
    
    sOutput += "</BODY></HTML>"

    var win = window.open('','test','width=700m,height=450,status=no, scrollbars=yes, resizable=yes');
    win.document.write(sOutput);
}
	
// GetScrapInfo 
function GetScrapInfo()
{
    UI_CLEAR_HTML();
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "select count(title) from t_scrap_data";
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    var nCount = 0;
    while(Db.GetRow() =="continue"){
        UI_ADD_HTML("<tr>");
       
        UI_ADD_HTML("<td width = '40'><div style = \"font-size:9pt;\"> <img src = \"image/041.gif\" border = 0> "); 
        UI_ADD_HTML("총 스크랩수: " + Db.GetValue(0) ); 
        
        UI_ADD_HTML("</div></td>"); 
        UI_ADD_HTML( "</tr>" );
        nCount++;
        
    }
    
    
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
    
    var sWhere = (pIndx == -1) ? " " : (" and pno < " + pIndx + " " );
    var sql = "SELECT pno AS 번호, title AS 제목, filepath AS 경로명, detailinfo AS 상세설명 " 
               +"FROM t_scrap_data "
               +"WHERE (title      like '%" + sPattern + "%' or  "
               +"       filepath   like '%" + sPattern + "%' or  "
               +"       detailinfo like '%" + sPattern + "%')  "
               + sWhere
               +"order by pno desc";
    
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
        UI_ADD_HTML("<img width = 50 height = 50 src='" + API_GetCurFolder() + "\\" + Db.GetValue(2) + "' border = 0>"); 
        UI_ADD_HTML("</div></TD>"); 
        
        
        UI_ADD_HTML("<td><div style = \"font-size:9pt;\"> "); 
        UI_ADD_HTML("<a href ='#'  onclick='ViewDetail(" + Db.GetValue(0) + ")'>"    ); 
        UI_ADD_HTML(Db.GetValue(1)); 
        UI_ADD_HTML("</a></div></TD>"); 
        
        UI_ADD_HTML( "</tr>" );
        
        UI_ADD_HTML( "<tr><td colspan=3 background=\"image/list_back.gif\"></td></tr>" );  
        
        // 크기넘어가면 출력안함.
        if( nRowCNT > step_navi - 1) break;                
    }
        

}

function GetScrapData(pIndx, bDierction)
{
    UI_CLEAR_HTML();

    UI_ADD_HTML("<table border=\"0\" width=\"560\">");
    UI_ADD_HTML("<tr bgcolor=\"#555555\">");
    UI_ADD_HTML("<td width=\"30\">    <font face=\"굴림체\"  color = white><span style=\"font-size:9pt;\">번호</span></font></td>");
    UI_ADD_HTML("<td width=\"80\">    <font face=\"굴림체\"  color = white><span style=\"font-size:9pt;\">스샷</span></font></td>");
    UI_ADD_HTML("<td width=\"450\">   <font face=\"굴림체\"  color = white><span style=\"font-size:9pt;\">제목</span></font></td>");
    UI_ADD_HTML("</tr>");
    
    // 화면출력
    SearchResultDisplay(query.value, pIndx, bDierction);

    UI_ADD_HTML("</table>");
    
    // Navigation 출력
    var prev = pNavi[nNaviIndx - 2];
    var next = pNavi[nNaviIndx]; 
    if(prev) 
        UI_ADD_HTML("<a href = '#' onclick = 'GetScrapData("+ pNavi[nNaviIndx - 2] +  ", 0);'><</a>");
    if(next && next != -1) 
        UI_ADD_HTML("<a href = '#' onclick = 'GetScrapData("+ pNavi[nNaviIndx]     +  ", 1);'>></a>");
    
    UI_ATTACH_BOARD(2);           
    
}

// Main 함수 - 처음실행
function OnJMainStart(sParam)
{
    GetScrapInfo(); 
    GetScrapData(-1, 1);    
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


