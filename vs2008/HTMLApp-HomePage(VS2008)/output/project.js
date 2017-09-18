//---------------------------------------------------------------------------
// ���� ����� 
var nTotalData = 0;// ��ü ������
var nTotalProj = 0;// ��ü ������Ʈ ����

function UpdateInfo(pno)
{
    var wFile = new JFile();
    wFile.Create(API_GetCurFolder() + "\\parameter\\work_update2.txt");
    wFile.Write(pno);
    wFile.Close();
    
    location.href ="project_update.html";
}

// Project�� 
function GetProjectInfo()
{
    UI_CLEAR_HTML();
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    // �� ī��Ʈ - ������Ʈ
    var sql = "select count(name) from t_project_name";
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;

    while(Db.GetRow() =="continue"){
        nTotalProj = Db.GetValue(0);
    }
    
    // �� ī��Ʈ - data
    sql = "select count(pno) from t_project_data";
    sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    while(Db.GetRow() =="continue"){
        nTotalData = Db.GetValue(0);
    }
    
    UI_ADD_HTML("<tr>");
    UI_ADD_HTML("<td width = '40'><div style = \"font-size:9pt;\"> <img src = \"image/041.gif\" border = 0> "); 
    UI_ADD_HTML("��ü Project: " + nTotalProj); 
    UI_ADD_HTML("</div></td>"); 
    UI_ADD_HTML( "</tr>" );        

    UI_ADD_HTML("<tr>");
    UI_ADD_HTML("<td width = '40'><div style = \"font-size:9pt;\"> <img src = \"image/041.gif\" border = 0> "); 
    UI_ADD_HTML("��ü  Data: " + nTotalData); 
    UI_ADD_HTML("</div></td>"); 
    UI_ADD_HTML( "</tr>" );   
            
    UI_ATTACH_BOARD(1);
}

var sTitle = new Array("�Ϸ�", "������", "�̿Ϸ�(����)");
var sColor = new Array("red",  "green",  "blue");
function SearchResultDisplay()
{
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    // outer join�� �ؾ� �Ѵ�.
    var sql = "SELECT  a.p_no, a.name, a.detail_info, a.StartTime, a.EndTime, a.state, count(b.pno) as ���� "
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
        
        UI_ADD_HTML("������:" + Db.GetValue(3) + "<BR>������:" + Db.GetValue(4));
        UI_ADD_HTML("<br>����:<b>" + sTitle[Db.GetValue(5)] + "</b><a href = '#' onclick = 'UpdateInfo(" + Db.GetValue(0) + ");'>->�����ϱ�</a><br><br>");  
        
        // graph ó��
        var nPercent  = 0.001; // �ҽ��� ó���ϱ� ���ؼ�
        nPercent      = (Db.GetValue(6) / nTotalData) * 100;
        
        // �ڸ��� ó��
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
        
        UI_ADD_HTML("��ü�� " + sPercent + "% " 
                    +"<div id = 'graph' style = 'font-familiy: ����; font-size: 10pt; color: #CAAAEE; "
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
    UI_ADD_HTML("<td width=\"30\">    <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">��ȣ</span></font></td>");
    UI_ADD_HTML("<td width=\"130\">   <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">Project</span></font></td>");
    UI_ADD_HTML("<td width=\"300\">   <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">����</span></font></td>");
    UI_ADD_HTML("</tr>");
    
    // ȭ�����
    SearchResultDisplay();

    UI_ADD_HTML("</table>");
    UI_ATTACH_BOARD(2);           
    
}

// Main �Լ� - ó������
function OnJMainStart(sParam)
{
    GetProjectInfo();
    GetProjectName();        
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


