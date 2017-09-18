//---------------------------------------------------------------------------
var g_pNo = -1;
// ���� ����� 
function GetParamInfo()
{
    var rFile = new JFile();
    rFile.Open(API_GetCurFolder() + "\\parameter\\work_update2.txt");
    var pno   = rFile.Read();
    g_pNo     = pno;  
    rFile.Close();
    
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "select name, StartTime, EndTime, detail_info,  state from t_project_name where p_no = " + pno;
    
    var sRst = Db.SQL(sql);
    if(sRst != "true") return;
    
    while(Db.GetRow() =="continue"){
        P_NAME.value            =  Db.GetValue(0);
        P_START_DATE.value      =  Db.GetValue(1);
        P_END_DATE.value        =  Db.GetValue(2);
        P_DETAIL.value          =  Db.GetValue(3);
        P_SPEC.selectedIndex    =  Db.GetValue(4);
    }
}

// Main �Լ� - ó������
function OnJMainStart(sParam)
{
    // ���ó�¥ �Է�
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
    // Ư������ �����ϱ�
    var sDetail   = chkInvalidChar( P_DETAIL.value );
    var sName     = chkInvalidChar( P_NAME.value );
    var sDate     = chkInvalidChar( P_START_DATE.value );
    var sDate2    = chkInvalidChar( P_END_DATE.value );
    var nSpec   = P_SPEC.selectedIndex;
    
    
    // DB �Է��ϱ�
    var Db = new JDBMaster();
    
    var sRst = Db.Connect("P-Intra.mdb");    
    if(sRst != "true") return;
    
    var sql = "update t_project_name set " //(name, state, StartTime, EndTime, detail_info, f_spec) values(
              + "name = '" + sName     + "', "
              + "state=  " + nSpec     + ",  "
              + "StartTime = CDate('" + sDate  + "'), "
              + "EndTime = CDate('" + sDate2 + "'), "
              + "detail_info = '" + sDetail   + "' "
              +"where p_no =" + g_pNo; 
              
    Db.SQL(sql);    
    
    alert("�Է¿Ϸ�Ǿ����ϴ�.");
}
	


