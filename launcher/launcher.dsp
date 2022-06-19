# Microsoft Developer Studio Project File - Name="launcher" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Application" 0x8601

CFG=launcher - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "launcher.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "launcher.mak" CFG="launcher - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "launcher - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "launcher - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Dreamcast"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "launcher - Win32 (WCE SH4) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESH4Rel"
# PROP BASE Intermediate_Dir "WCESH4Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESH4Rel"
# PROP Intermediate_Dir "WCESH4Rel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Ox /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD CPP /nologo /MC /W3 /Zi /Ox /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD BASE RSC /l 0x809 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x809 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# ADD LINK32 coredll.lib winsock.lib corelibc.lib cemm.lib ddraw.lib dinput.lib dxguid.lib floatmath.lib dsound.lib platutil.lib shintr.lib mapledev.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096

!ELSEIF  "$(CFG)" == "launcher - Win32 (WCE SH4) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESH4Dbg"
# PROP BASE Intermediate_Dir "WCESH4Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESH4Dbg"
# PROP Intermediate_Dir "WCESH4Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /c
# ADD CPP /nologo /MC /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /FR /YX /Qsh4r7 /Qs /Qfast /c
# ADD BASE RSC /l 0x809 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x809 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# ADD LINK32 coredll.lib winsock.lib corelibc.lib cemm.lib ddraw.lib dinput.lib dxguid.lib floatmath.lib dsound.lib platutil.lib shintr.lib mapledev.lib /nologo /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096

!ENDIF 

# Begin Target

# Name "launcher - Win32 (WCE SH4) Release"
# Name "launcher - Win32 (WCE SH4) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\launcher.cpp
DEP_CPP_LAUNC=\
	".\launcher.h"\
	{$(INCLUDE)}"ceddcdrm.h"\
	{$(INCLUDE)}"ceddstor.h"\
	{$(INCLUDE)}"mapledev.h"\
	{$(INCLUDE)}"maplusag.h"\
	{$(INCLUDE)}"netinfo.h"\
	{$(INCLUDE)}"perstore.h"\
	{$(INCLUDE)}"platutil.h"\
	{$(INCLUDE)}"segagdrm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\main.cpp
DEP_CPP_MAIN_=\
	".\launcher.h"\
	{$(INCLUDE)}"ceddcdrm.h"\
	{$(INCLUDE)}"ceddstor.h"\
	{$(INCLUDE)}"mapledev.h"\
	{$(INCLUDE)}"maplusag.h"\
	{$(INCLUDE)}"netinfo.h"\
	{$(INCLUDE)}"perstore.h"\
	{$(INCLUDE)}"platutil.h"\
	{$(INCLUDE)}"segagdrm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\launcher.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\fontlgr.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\fontlgw.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\fontsm.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\M_doom.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\M_skull1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn033.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn034.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn035.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn036.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn037.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn038.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn039.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn040.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn041.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn042.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn043.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn044.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn045.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn046.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn047.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn048.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn049.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn050.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn051.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn052.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn053.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn054.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn055.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn056.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn057.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn058.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn059.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn060.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn061.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn062.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn063.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn064.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn065.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn066.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn067.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn068.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn069.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn070.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn071.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn072.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn073.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn074.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn075.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn076.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn077.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn078.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn079.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn080.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn081.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn082.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn083.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn084.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn085.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn086.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn087.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn088.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn089.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn090.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn091.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn092.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn093.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn094.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn095.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Stcfn121.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Res\Dspistol.wav
# End Source File
# Begin Source File

SOURCE=.\Res\Dsswtchn.wav
# End Source File
# Begin Source File

SOURCE=.\Res\Dsswtchx.wav
# End Source File
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# End Target
# End Project
