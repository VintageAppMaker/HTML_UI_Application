//---------------------------------------------------------------------------
// ���� ����� 
function UpdateInfo(pno)
{
    var wFile = new JFile();
    wFile.Create(API_GetCurFolder() + "\\parameter\\work_update.txt");
    wFile.Write(pno);
    wFile.Close();
    
    location.href ="work_update.html";
}

// Project�� 
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
    
    UI_ADD_HTML(" <a href = 'project.html'>...��</a>");             
    
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
    
    var sWhere = (pIndx == -1) ? " " : (" b.pno < " + pIndx + " and " );
    var sql = "SELECT b.pno AS ��ȣ, a.name AS ������Ʈ��, b.title AS ����, c.title AS ����, b.filepath AS ��θ�, b.detailinfo AS �󼼼���, b.MakeTime " 
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
        
        // �׺���̼� �� ��ġ�� ����( ���ļ����� ���� ���� �޶�����. desc, order by)
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
        
        // ������ ���� �����ֱ� 
        var str     = Db.GetValue(5)
        str         = str.replace(/\r\n/gi, "<br>");
        str         = str.replace(/ /gi, "&nbsp"); 
        
        var str2    = Db.GetValue(4);
        str2        = str2.replace(/'/gi, " ");

        
        var sUpdateLink  = "<a href =\"#\" onclick = \"UpdateInfo(" + Db.GetValue(0) + ");\">-�����ϱ�</a>";
        var sContentInfo = "<div style = 'color:black; text-decoration: BOLD;'>"
                           +"<B>����:"  + Db.GetValue(2) + "(" + Db.GetValue(3) + ")</B>" + sUpdateLink + "</div> "
                           +"����:"  + Db.GetValue(6)           
                           +  "<br><br>"+ str + "<br>"
                           
                           + "<br>file:<a href= \"#\" onclick='API_excute(\"" + str2 +"\")'> "
                           +  Db.GetValue(4) + "</a><br>";
                           
        
        UI_ADD_HTML(sContentInfo); 
        UI_ADD_HTML("</div></td>"); 
        
        UI_ADD_HTML( "</tr>" );
        
        UI_ADD_HTML( "<tr><td colspan=3 background=\"image/list_back.gif\"></td></tr>" );  
        
        // ũ��Ѿ�� ��¾���.
        if( nRowCNT > step_navi - 1) break;                
    }
        

}

function GetProjectData(pIndx, bDierction)
{
    UI_CLEAR_HTML();

    UI_ADD_HTML("<table border=\"0\" width=\"560\">");
    UI_ADD_HTML("<tr bgcolor=\"#555555\">");
    UI_ADD_HTML("<td width=\"30\">    <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">��ȣ</span></font></td>");
    UI_ADD_HTML("<td width=\"130\">   <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">Project</span></font></td>");
    UI_ADD_HTML("<td width=\"300\">   <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">����</span></font></td>");
    UI_ADD_HTML("</tr>");
    
    // ȭ�����
    SearchResultDisplay(query.value, pIndx, bDierction);

    UI_ADD_HTML("</table>");
    
    // Navigation ���
    var prev = pNavi[nNaviIndx - 2];
    var next = pNavi[nNaviIndx]; 
    if(prev) 
        UI_ADD_HTML("<a href = '#' onclick = 'GetProjectData("+ pNavi[nNaviIndx - 2] +  ", 0);'><</a>");
    if(next && next != -1) 
        UI_ADD_HTML("<a href = '#' onclick = 'GetProjectData("+ pNavi[nNaviIndx]     +  ", 1);'>></a>");
    
    UI_ATTACH_BOARD(2);           
    
}

// Main �Լ� - ó������
function OnJMainStart(sParam)
{
    GetProjectName(); 
    GetProjectData(-1, 1);  
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


