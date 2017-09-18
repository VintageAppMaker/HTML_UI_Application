# Microsoft Developer Studio Project File - Name="AppLayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AppLayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AppLayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AppLayer.mak" CFG="AppLayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AppLayer - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AppLayer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AppLayer - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\output\AppLayer.dll"

!ELSEIF  "$(CFG)" == "AppLayer - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\output\AppLayer.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AppLayer - Win32 Release"
# Name "AppLayer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AppLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\AppLayer.def
# End Source File
# Begin Source File

SOURCE=.\AppLayer.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppLayer.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\a.jpg
# End Source File
# Begin Source File

SOURCE=.\res\AppLayer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bt.gif
# End Source File
# Begin Source File

SOURCE=.\res\btn1.gif
# End Source File
# Begin Source File

SOURCE=.\res\burst.gif
# End Source File
# Begin Source File

SOURCE=.\res\CDebugMonitor.ico
# End Source File
# Begin Source File

SOURCE=.\res\close.gif
# End Source File
# Begin Source File

SOURCE=.\res\crack90.JPG
# End Source File
# Begin Source File

SOURCE=.\res\Folder.ico
# End Source File
# Begin Source File

SOURCE=.\res\folderclose.gif
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\list_back.gif
# End Source File
# Begin Source File

SOURCE=.\res\max.gif
# End Source File
# Begin Source File

SOURCE=.\res\min.gif
# End Source File
# Begin Source File

SOURCE=.\res\minus.gif
# End Source File
# Begin Source File

SOURCE=.\res\plus.gif
# End Source File
# Begin Source File

SOURCE=.\res\resize.gif
# End Source File
# Begin Source File

SOURCE=.\res\search.gif
# End Source File
# Begin Source File

SOURCE=.\res\zipicon.gif
# End Source File
# End Group
# Begin Group "상태관리"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CPage.cpp
# End Source File
# Begin Source File

SOURCE=.\CPage.h
# End Source File
# Begin Source File

SOURCE=.\FSM.h
# End Source File
# End Group
# Begin Group "UI 관련(HTML)"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\HTML_UI_API.cpp
# End Source File
# Begin Source File

SOURCE=.\HTML_UI_API.h
# End Source File
# Begin Source File

SOURCE=.\UTIL_API.H
# End Source File
# End Group
# Begin Group "기능구현(실제구현부)"

# PROP Default_Filter ""
# Begin Group "기능구현(Utility)"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Util.cpp
# End Source File
# Begin Source File

SOURCE=.\Util.h
# End Source File
# End Group
# Begin Group "기능구현(Page구현클래스)"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CPageMain.cpp
# End Source File
# Begin Source File

SOURCE=.\CPageMain.h
# End Source File
# End Group
# Begin Group "기능구현(페이지등록클래스)"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CHTMLPage.cpp
# End Source File
# Begin Source File

SOURCE=.\CHTMLPage.h
# End Source File
# End Group
# End Group
# Begin Group "외부엔진"

# PROP Default_Filter ""
# Begin Group "HTML리소스"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\api.js
# End Source File
# Begin Source File

SOURCE=.\res\popup.js
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\start.html
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=..\PSWLib\PSWCommonLib.lib
# End Source File
# End Target
# End Project
