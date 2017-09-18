// App�� �����ϴ� �Լ� ȣ�� 
function ExcuteAPI(fName, sParam)
{
    location.href = 'res://APP_CMD|ME|' + fName + '|' + sParam;
}

//---------------------------------------------------------------------------
// DB API �����ϱ� 

// DB �����ϱ� 
function API_ConnectDB(DBName)
{
    ExcuteAPI("ConnectDB", DBName);
    return RESULT.value;    
}

function API_SQL(Query)
{
    /* URL �������� �ϴ� ���Ͱ��� ���������..*/
	RESULT.value = Query;
	ExcuteAPI("SQL", "__");
    return RESULT.value;    
}

function API_GetRow()
{
    // HTML Frame API Ư���� �ݵ�� �Ķ���͸� ���̷ε� �־�� ��.
    ExcuteAPI("GetRow", "0");
    return RESULT.value;    
}

function API_GetValue(sIndx)
{
    ExcuteAPI("GetValue", sIndx);
    return RESULT.value;    
}

//---------------------------------------------------------------------------
// Class�� ����
function JDBMaster()
{
}

JDBMaster.prototype.Connect = function(DBName){
    return API_ConnectDB(DBName);    
}

JDBMaster.prototype.SQL = function(Query){
    return API_SQL(Query);    
}

JDBMaster.prototype.GetRow = function(){
    return API_GetRow();    
}

JDBMaster.prototype.GetValue = function(sIndx){
    return API_GetValue(sIndx);    
}

//---------------------------------------------------------------------------
// File API �����ϱ� 

// File Open
function API_OpenFile(fName)
{
    ExcuteAPI("OpenFile", fName);
    return FileRESULT.value;    
}
// File Create
function API_CreateFile(fName)
{
    ExcuteAPI("CreateFile", fName);
    return FileRESULT.value;    
}

// File Close
function API_CloseFile(f)
{
    ExcuteAPI("CloseFile", f);
    return FileRESULT.value;    
}

// File Write
function API_WriteFile(f, pData)
{
    FileWrite.value = pData;
    ExcuteAPI("WriteFile", f);
    
    return FileRESULT.value;    
}

// File Read
function API_ReadFile(f)
{
    ExcuteAPI("ReadFile", f);
    return FileREAD.value;    
}

// File Delete
function API_DeleteFile(fName)
{
    FileTarget.value = fName;
    ExcuteAPI("DeleteFile", fName);    
}

// File Copy
function API_CopyFile(fSrc, fDst)
{
    FileTarget.value = fDst;
    FileSource.value = fSrc;
    ExcuteAPI("CopyFile", "___");    
}

// File Size
function API_GetFileSize(f)
{
    ExcuteAPI("GetFileSize", f);    
    return FileRESULT.value;     
}

//---------------------------------------------------------------------------
// Class�� ����
function JFile()
{
    this.m_fHandle; // FIle �ڵ�
    this.m_fName  ; // File Name
    this.State    ;  // 0:close, 1:����, 2:Create
}

JFile.prototype.Open = function(fName){
    this.State = 1;
    this.m_fHandle = API_OpenFile(fName);    
    return this.m_fHandle;
}

JFile.prototype.Create = function(fName){
    this.State = 2;
    this.m_fHandle = API_CreateFile(fName);
    return this.m_fHandle;    
}

JFile.prototype.Close = function(){
    this.State = 0;
    return API_CloseFile(this.m_fHandle);    
}

JFile.prototype.Write = function(pData){
    return API_WriteFile(this.m_fHandle, pData); 
}

JFile.prototype.Read = function(){
    return API_ReadFile(this.m_fHandle); 
}

JFile.prototype.GetSize = function(){
    return API_GetFileSize(this.m_fHandle); 
}
//---------------------------------------------------------------------------
// SYstem API �����ϱ�
function API_System(pParam)
{
    ExcuteAPI("System", pParam);
}

function API_excute(pParam)
{
    ExcuteAPI("excute", pParam);
}
//---------------------------------------------------------------------------
// Folder API �����ϱ�
function API_GetCurFolder()
{
    ExcuteAPI("GetCurFolder", "__(dummy)");
    return FolderRESULT.value;
}

function API_SetFolder(pParam)
{
    FolderIN.value = pParam;
    ExcuteAPI("SetFolder", pParam);
    return FolderRESULT.value;
}

function API_SearchFolder(pParam)
{
    ExcuteAPI("SearchFolder", pParam);
}

function API_CreateFolder(pParam)
{
    FolderIN.value = pParam;
	ExcuteAPI("CreateFolder", pParam);
	return FolderRESULT.value;
}

//---------------------------------------------------------------------------
// Folder API �����ϱ�
function API_CGICall(pParam)
{
    ExcuteAPI("CGICall", pParam);
    return CGIRESULT.value;
}

//---------------------------------------------------------------------------
// �Ϲ���ƿ�Լ�
function WriteMessgage(sMsg)
{
    document.write(sMsg);
    document.write("<br>");    
}

//---------------------------------------------------------------------------
// HTML ����� ����

// HTML Code Add
var g_sOutText = "";

function UI_CLEAR_HTML()
{
    g_sOutText = "";
}

function UI_ADD_HTML(sText)
{
    g_sOutText += sText;
}

// HTML Code Attach
function UI_ATTACH_BOARD(num)
{
    document.getElementById('BOARD_'+ num).innerHTML = g_sOutText;
}

//---------------------------------------------------------------------------
// Cookie���� ����
function setCookie( name, value, expiredays ) 
{
    var todayDate = new Date();
    todayDate.setDate( todayDate.getDate() + expiredays );
    document.cookie = name + "=" + escape( value ) + "; path=/; expires=" + todayDate.toGMTString() + ";"
} 

function getCookie( name )
{
    var nameOfCookie = name + "=";
    var x = 0;
    
	while ( x <= document.cookie.length )
    {
        var y = (x+nameOfCookie.length);
        if ( document.cookie.substring( x, y ) == nameOfCookie ) {
            if ( (endOfCookie=document.cookie.indexOf( ";", y )) == -1 )
                endOfCookie = document.cookie.length;
            return unescape( document.cookie.substring( y, endOfCookie ) );
        }
        x = document.cookie.indexOf( " ", x ) + 1;
        if ( x == 0 )
            break;
    }
    
	return "";
} 