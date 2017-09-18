#include "stdafx.h"
#include "util.h"
#include "UTIL_API.h"

// 모뎀상태를 화면에 보여준다.
void DisplayUSBModemState()
{
    HKEY  hKey;
    LONG  lResult;
	DWORD dwIndex = 0;
    DWORD dwType = REG_SZ;
    DWORD dwRegSize, dwDataSize;
	char sRegBuff[MAX_PATH], sValueBuff[MAX_PATH];

	CString sType;
	CString sKey = "HARDWARE\\DEVICEMAP\\SERIALCOMM\\";

	memset(sValueBuff, '\0', MAX_PATH);
	memset(sRegBuff, '\0', MAX_PATH);

    lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, 
							sKey.GetBuffer(1024),
							0,  
							KEY_READ, 
							&hKey);

    if (lResult != ERROR_SUCCESS ){
		RegCloseKey(hKey);
		return;
	}
    
	UI_ERASE_LIST();

    while(1){
		dwRegSize  = MAX_PATH;
		dwDataSize = MAX_PATH;

		lResult = RegEnumValue( hKey, 
								dwIndex,
								sRegBuff,
								&dwRegSize,
								NULL,
								&dwType, 
								(unsigned char*)sValueBuff,
								&dwDataSize);
		
		if(lResult == ERROR_NO_MORE_ITEMS){
			RegCloseKey(hKey);
			break;
		}
        
		sType = sRegBuff;
		sType.Replace("\\Device\\", "");
		sType.Replace("\\DEVICE\\", "");

		strcat(sValueBuff, " (");
		strcat(sValueBuff, sType.GetBuffer(20));
		strcat(sValueBuff, ")");
		
		UI_WRITE_LIST( sValueBuff );

		dwIndex++;

	}

     
}