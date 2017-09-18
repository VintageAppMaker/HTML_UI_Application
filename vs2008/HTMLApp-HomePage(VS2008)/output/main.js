//---------------------------------------------------------------------------
// ���� ����� 
function MakeTxtAndRun(num)
{
    var Db = new JDBMaster();

    var sRst = Db.Connect("AppManager.mdb");    
    if(sRst != "true"){alert("DB Error"); return;}
    
    var sql = "select detailinfo from t_program_tips where pno = " + num;
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    // ���ϳ����� ����� �����ϱ� 
    while(Db.GetRow() =="continue"){
        var str = Db.GetValue(0); 
        var sFolder = API_GetCurFolder();
        var sFile   = sFolder + "\\" + num + ".txt";
        
        var fWrite = new JFile();
        fWrite.Create(sFile);
        fWrite.Write (str);
        fWrite.Close (str);
        
        // ����� �����ϱ� 
        API_DeleteFile(sFile);
        API_excute(sFile);        
    }

}

function GetTipList()
{
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("AppManager.mdb");    
    if(sRst != "true") return;
    
    var sql = "select title, pno from t_program_tips";
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    
    while(Db.GetRow() =="continue"){
        UI_ADD_HTML("<tr>");
       
        UI_ADD_HTML("<td width = '40'><div style = \"font-size:9pt;\"> <img src = \"image/plus.gif\" border = 0>"); 
        UI_ADD_HTML(Db.GetValue(1)); 
        UI_ADD_HTML("</div></td>"); 
        
        UI_ADD_HTML("<td width = '300'><div style = \"font-size:9pt;\"> "); 
        UI_ADD_HTML("<a href = '#' onclick =\"" );
        UI_ADD_HTML("MakeTxtAndRun('" +Db.GetValue(1) +"')");
        UI_ADD_HTML("\">");

        UI_ADD_HTML(Db.GetValue(0)); 
        
        UI_ADD_HTML("</a></div></td>"); 
        
        UI_ADD_HTML( "</tr>" );
        
        UI_ADD_HTML( "<tr><td colspan=3 background=\"image/list_back.gif\"></td></tr>" );         
        
    }
    
}

// Table �����
function MakeProgramInfoTable()
{
    UI_CLEAR_HTML();
    
    UI_ADD_HTML("<br><center> ");
    UI_ADD_HTML("<H1>Programming Tip..</H1>");
    UI_ADD_HTML("<br>");
    UI_ADD_HTML("</center>"); 
    
    UI_ADD_HTML("<table border=\"0\" width=\"403\">");
    UI_ADD_HTML("<tr bgcolor=\"#AAAAFF\">");
    UI_ADD_HTML("<td width=\"40\">   <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">��ȣ</span></font></td>");
    UI_ADD_HTML("<td width=\"300\">   <font face=\"����ü\"  color = white><span style=\"font-size:9pt;\">����</span></font></td>");
    UI_ADD_HTML("</tr>");
    
    GetTipList();
    
    UI_ADD_HTML("</table>");
    
    UI_ATTACH_BOARD(1);
}

// Folder ������ ..�����ش�.
function GetCurentFolderInfo()
{
    UI_CLEAR_HTML();
    var sFolder = API_GetCurFolder();
    
    UI_ADD_HTML("<br>");
    UI_ADD_HTML("<center><h1> �������������ֱ� </h1></center>");
    UI_ADD_HTML("�����θ�:><br>"+ sFolder);
    UI_ADD_HTML("<br>");
   
    sFolder+= "\\";
    API_SearchFolder(sFolder);
}

// �����ٲٰ� �����ֱ�
function ChangeFolder(sName)
{
    var sFolder = API_GetCurFolder();
    sFolder+= "\\" + sName;
    API_SetFolder(sFolder);
    
    GetCurentFolderInfo();   
}


// CGI ���α׷� �����ֱ�
function CallCGIProgram(fName)
{
    var sOutput = API_CGICall(fName);
   
    UI_CLEAR_HTML();
    UI_ADD_HTML("<br>");
    UI_ADD_HTML("<center><h1> CGI Output </h1></center>");
    UI_ADD_HTML("<pre>");
    UI_ADD_HTML(sOutput);
    UI_ADD_HTML("</pre>");
    UI_ADD_HTML("<br>");
    
    UI_ATTACH_BOARD(3);
}

// �����б�
function ReadExample(fName)
{
    var rFile = new JFile();
    rFile.Open(fName);
    
    //alert(rFile.m_fHandle);
    
    var sOutput = rFile.Read();
    rFile.Close();
    
    UI_CLEAR_HTML();
    UI_ADD_HTML("<br>");
    UI_ADD_HTML("<center><h1> ���� </h1></center>");
    UI_ADD_HTML("<pre>");
    UI_ADD_HTML(sOutput);
    UI_ADD_HTML("</pre>");
    UI_ADD_HTML("<br>");
    
    UI_ATTACH_BOARD(4);
    
}

// Main �Լ� - ó������
function OnJMainStart(sParam)
{
    //APITest();
    
    // DB �˻�
    MakeProgramInfoTable();    
    
    // CGI ��ɿ���
    var sFname = API_GetCurFolder()+ "\\" + "test.bat";
    CallCGIProgram(sFname);
    
    //Folder ���� �����ֱ�
    GetCurentFolderInfo();
    
    // ���� �����ֱ�
    var sFname2 = API_GetCurFolder()+ "\\" + "tutorial.txt";
    ReadExample(sFname2);

    var wFile = new JFile();
    
    var fName3= API_GetCurFolder() + "\\" + "run.bat";
    
    API_DeleteFile(fName3);    
    
    // API Create Folder
    API_CreateFolder(API_GetCurFolder()+ "\\A00000");    
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

// Folder Info Receive
function OnFolderRead(type, pFileName)
{
    var msg = "";
    if(type == 0){
        msg += "<a href = '#' onclick=\"ChangeFolder('"  
            + pFileName 
            +"')\">";
        msg += "Folder>" + pFileName + "</a><br>";        
        
    } else if(type == 1){
        // API_excute()�� ���� ���
        msg += "<a href = '#' onclick=\"API_excute('"  
            + pFileName 
            +"')\">";
        msg += "file>" + pFileName + "</a><br>";
    } else if(type == 100){
        // �˻������ 
        UI_ATTACH_BOARD(2);   
    }
    UI_ADD_HTML(msg);    
};


