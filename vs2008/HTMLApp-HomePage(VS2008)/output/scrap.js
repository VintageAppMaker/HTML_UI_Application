//---------------------------------------------------------------------------
// ���� ����� 
function ViewDetail(no)
{
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    var sql = "SELECT a.title AS ����, a.filepath AS ��θ�, a.detailinfo AS �󼼼���, b.title as ���� " 
               +"FROM t_scrap_data a, t_basic b "
               +"WHERE a.pno = " + no
               +"      and a.f_spec = b.pno " 
               +" order by a.pno desc";
      
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    var sOutput = "<HTML><HEAD><BODY  style = 'background-color: #FFFFFA; color: black; font-familiy:����; font-size: 10pt;'>";
    while(Db.GetRow() =="continue"){
        sOutput += "<td><div style = \"font-size:9pt; color: black; width: 600; font-familiy:����;\"> "; 
        sOutput += "����:" + Db.GetValue(0) + "-" + Db.GetValue(3) +"<hr>"; 
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
        UI_ADD_HTML("�� ��ũ����: " + Db.GetValue(0) ); 
        
        UI_ADD_HTML("</div></td>"); 
        UI_ADD_HTML( "</tr>" );
        nCount++;
        
    }
    
    
    UI_ATTACH_BOARD(1);
}

// �׺���̼��� ��ǥ�� �Ǵ� ��
var step_navi = 5;
var pNavi     = new Array();
var nNaviIndx = 0;
function SearchResultDisplay(sPattern, pIndx, bDierction)
{
    
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sWhere = (pIndx == -1) ? " " : (" and pno < " + pIndx + " " );
    var sql = "SELECT pno AS ��ȣ, title AS ����, filepath AS ��θ�, detailinfo AS �󼼼��� " 
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
        
        // �׺���̼� �� ��ġ�� ����( ���ļ����� ���� ���� �޶�����. desc, order by)
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
        
        // ũ��Ѿ�� ��¾���.
        if( nRowCNT > step_navi - 1) break;                
    }
        

}

function GetScrapData(pIndx, bDierction)
{
    UI_CLEAR_HTML();

    UI_ADD_HTML("<table border=\"0\" width=\"560\">");
    UI_ADD_HTML("<tr bgcolor=\"#555555\">");
    UI_ADD_HTML("<td width=\"30\">    <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">��ȣ</span></font></td>");
    UI_ADD_HTML("<td width=\"80\">    <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">����</span></font></td>");
    UI_ADD_HTML("<td width=\"450\">   <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">����</span></font></td>");
    UI_ADD_HTML("</tr>");
    
    // ȭ�����
    SearchResultDisplay(query.value, pIndx, bDierction);

    UI_ADD_HTML("</table>");
    
    // Navigation ���
    var prev = pNavi[nNaviIndx - 2];
    var next = pNavi[nNaviIndx]; 
    if(prev) 
        UI_ADD_HTML("<a href = '#' onclick = 'GetScrapData("+ pNavi[nNaviIndx - 2] +  ", 0);'><</a>");
    if(next && next != -1) 
        UI_ADD_HTML("<a href = '#' onclick = 'GetScrapData("+ pNavi[nNaviIndx]     +  ", 1);'>></a>");
    
    UI_ATTACH_BOARD(2);           
    
}

// Main �Լ� - ó������
function OnJMainStart(sParam)
{
    GetScrapInfo(); 
    GetScrapData(-1, 1);    
}
    
//---------------------------------------------------------------------------
// main �Լ�
// nState: ���� 
// sParam: �Ķ����

function JMain(nState, sParam)
{
    if(nState == 0){ OnJMainStart(sParam) };
}

//---------------------------------------------------------------------------
// callback �Լ�(Search, ��Ÿ���)


