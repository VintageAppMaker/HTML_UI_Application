//---------------------------------------------------------------------------
// ���� ����� 
var pIndx_spec = new Array(); // pno �� �迭
var pIndx_proj = new Array(); // pno �� �迭


// �����߰��ϱ� 
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
    var sFilePath = chkInvalidChar( sDBRelativeFileName ) ;
    
    var nSpec   = pIndx_spec[P_SPEC.selectedIndex];
    
    // ���� ������� ���� ��� ����Ʈ ȭ��
    var nSize = 0;
    sChkPath = sOrgFile.replace(/ /gi, "");
    nSize = sOrgFile.length;
    if(nSize == 0){  
        sFilePath = "image\\nodisplay.jpg";
    }    
    
    // DB �Է��ϱ�
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "insert into t_scrap_data(title, f_spec, detailinfo, filepath) values( "
              + "'" + sName     + "', "
              + nSpec           + ",  "
              + "'" + sDetail   + "', "
              + "'" + sFilePath + "'"
              +" )"; 
              
    if( Db.SQL(sql) == "true") alert("�Է¿Ϸ�Ǿ����ϴ�.");
}
	


