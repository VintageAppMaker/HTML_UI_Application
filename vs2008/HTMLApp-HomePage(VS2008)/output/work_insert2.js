//---------------------------------------------------------------------------
// ���� ����� 
var pIndx_spec = new Array(); // pno �� �迭
var pIndx_proj = new Array(); // pno �� �迭

// ������Ʈ�� �߰��ϱ� 
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
    UI_ADD_HTML("<select id = \"P_PROJECT\" style='width:197px;font-size:12px;font-family:����;' name=rcsection>");
    while(Db.GetRow() =="continue"){
        UI_ADD_HTML("<option value=>" + Db.GetValue(1) +"</option>");
        pIndx_proj[i] = Db.GetValue(0);    
        i++;        
    }
    UI_ADD_HTML("</select>");
    UI_ATTACH_BOARD(2);
}

// �����߰��ϱ� 
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
    UI_ADD_HTML("<select id = \"P_SPEC\" style='width:197px;font-size:12px;font-family:����;' name=rcsection>");
    while(Db.GetRow() =="continue"){
        UI_ADD_HTML("<option value=>" + Db.GetValue(1) +"</option>");
        pIndx_spec[i] = Db.GetValue(0);    
        i++;        
    }
    UI_ADD_HTML("</select>");
    UI_ATTACH_BOARD(1);
}


// Main �Լ� - ó������
function OnJMainStart(sParam)
{
    // �⺻���� ó��
    AddSpecNameInfo();
    AddProjectNameInfo();    
    
    // ���ó�¥ �Է�
    var today = new Date();
    P_START_DATE.value = today.getYear()  + "-" + ( today.getMonth() + 1 ) + "-" + today.getDate();
}
    
function chkInvalidChar(str)
{
    var str2;
    // \ ���� ó���ϱ� 
    str2 = str.replace(/\\/gi, "\\\\");
    str = str2; 
    
    // ' ���� ó���ϱ� 
    str2 = str.replace(/\'/gi, "\'\'");
    str = str2;    
    
    // ' ���� ó���ϱ� 
    //str2 = str.replace(/\"/gi, "\'");
    //str = str2; 
    
    return str; // call by ref�� ��� ó������..?
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
    var sfileName  = sOrgFile.substring(nIdx + 1,  1000); // �ڹٽ�ũ��Ʈ�� �˾Ƽ� �ذ����ִ���..����
    
    // ' ����  �����̽��� ó�� & ���� 
    sfileName        = sfileName.replace(/'/gi, " ");
    API_CopyFile(sOrgFile, sFolderName + "\\" + sfileName);
    
    var sDBRelativeFileName = sDbPath + "\\" + sfileName;
    // Ư������ �����ϱ�
    var sDetail   = chkInvalidChar( P_DETAIL.value );
    var sName     = chkInvalidChar( P_NAME.value );
    var sDate     = chkInvalidChar( P_START_DATE.value );
    var sFilePath = chkInvalidChar( sDBRelativeFileName ) ;
    
    var nSpec   = pIndx_spec[P_SPEC.selectedIndex];
    var nProj   = pIndx_proj[P_PROJECT.selectedIndex];
    
    
    // DB �Է��ϱ�
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "insert into t_project_data(title, f_spec, f_project, detailinfo, filepath, MakeTime) values( "
              + "'" + sName     + "', "
              + nSpec           + ",  "
              + nProj           + ",  "
              + "'" + sDetail   + "', "
              + "'" + sFilePath + "', "
              + "CDate('" + sDate + "')"
              +")"; 
              
    Db.SQL(sql);    
    
    alert("�Է¿Ϸ�Ǿ����ϴ�.");
}
	


