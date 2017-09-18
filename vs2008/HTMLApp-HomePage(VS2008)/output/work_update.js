//---------------------------------------------------------------------------
// ���� ����� 
var pIndx_spec = new Array(); // pno �� �迭
var pIndx_proj = new Array(); // pno �� �迭

var g_pNo = -1;  // Primary Key

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
    
    // �������� ȭ�鿡 ǥ����. 
    GetParamInfo();
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
	    

function GetParamInfo()
{
    var rFile = new JFile();
    rFile.Open(API_GetCurFolder() + "\\parameter\\work_update.txt");
    var pno   = rFile.Read();
    g_pNo     = pno;  
    rFile.Close();
    
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "select title, f_spec, f_project, detailinfo,  MakeTime from t_project_data where pno = " + pno;
    
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    while(Db.GetRow() =="continue"){
        P_NAME.value            =  Db.GetValue(0);
        
        for(i =0; i < pIndx_spec.length; i++){
            if( pIndx_spec[i]  == Db.GetValue(1)) P_SPEC.selectedIndex = i;
        }
        for(i =0; i < pIndx_proj.length; i++){
            if( pIndx_proj[i]  == Db.GetValue(2)) P_PROJECT.selectedIndex = i;
        }
        
        P_DETAIL.value          =  Db.GetValue(3);
        P_START_DATE.value      =  Db.GetValue(4);
    }
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
function OnSave()
{
    // MakeFolder
    
    // Ư������ �����ϱ�
    var sDetail   = chkInvalidChar( P_DETAIL.value );
    var sName     = chkInvalidChar( P_NAME.value );
    var sDate     = chkInvalidChar( P_START_DATE.value );
    var nSpec     = pIndx_spec[P_SPEC.selectedIndex];
    var nProj     = pIndx_proj[P_PROJECT.selectedIndex];
    
    
    // DB �Է��ϱ�
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "update t_project_data set " 
              + "title  = '"   + sName     + "', "
              + "f_spec ="     + nSpec     + ",  "
              + "f_project="   + nProj     + ",  "
              + "detailinfo='" + sDetail   + "', "
              
              + "MakeTime = CDate('" + sDate + "') "
              + " where pno = "+ g_pNo; 
    
    Db.SQL(sql);    
    
    alert("�����Ϸ�Ǿ����ϴ�..");
}
	
function OnDelete()
{
    if( prompt("������� yes�� �Է��ϼ���", "no")  != "yes") return;
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "delete from t_project_data  where pno = " + g_pNo; 
    Db.SQL(sql);    
    
    alert("�����Ǿ����ϴ�..");
}


