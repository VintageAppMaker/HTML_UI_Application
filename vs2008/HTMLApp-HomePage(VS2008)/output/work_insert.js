//---------------------------------------------------------------------------
// ���� ����� 

// Main �Լ� - ó������
function OnJMainStart(sParam)
{
    // ���ó�¥ �Է�
    var today = new Date();
    P_START_DATE.value = today.getYear()  + "-" + ( today.getMonth() + 1 ) + "-" + today.getDate();
    P_END_DATE.value = today.getYear()  + "-" + ( today.getMonth() + 1 ) + "-" + today.getDate();
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
    
    var sql = "insert into t_project_name(name, state, StartTime, EndTime, detail_info, f_spec) values( "
              + "'" + sName     + "', "
              + nSpec           + ",  "
              + "CDate('" + sDate  + "'), "
              + "CDate('" + sDate2 + "'), "
              + "'" + sDetail   + "', 0 "
              +")"; 
              
    Db.SQL(sql);    
    
    alert("�Է¿Ϸ�Ǿ����ϴ�.");
}
	


