# Microsoft Developer Studio Project File - Name="DCDoom" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE SH4) Application" 0x8601

CFG=DCDoom - Win32 (WCE SH4) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DCDoom.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DCDoom.mak" CFG="DCDoom - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DCDoom - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Application")
!MESSAGE "DCDoom - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Dreamcast"
# PROP WCE_FormatVersion "6.0"
CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DCDoom - Win32 (WCE SH4) Release"

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
# ADD CPP /nologo /MC /W3 /Zi /O1 /Ob2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_UNICODE" /YX /Qsh4r7 /Qs /Qfast /Qgvp /c
# ADD BASE RSC /l 0x809 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x809 /r /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 coredll.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# ADD LINK32 coredll.lib winsock.lib corelibc.lib cemm.lib ddraw.lib dinput.lib dxguid.lib floatmath.lib dsound.lib platutil.lib shintr.lib mapledev.lib /nologo /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /nodefaultlib /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /map

!ELSEIF  "$(CFG)" == "DCDoom - Win32 (WCE SH4) Debug"

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

# Name "DCDoom - Win32 (WCE SH4) Release"
# Name "DCDoom - Win32 (WCE SH4) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Am_map.c
DEP_CPP_AM_MA=\
	"..\Am_map.h"\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_cheat.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\St_stuff.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_AM_MA=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\D_items.c
DEP_CPP_D_ITE=\
	"..\D_items.h"\
	"..\D_think.h"\
	"..\Doomdef.h"\
	"..\Info.h"\
	
# End Source File
# Begin Source File

SOURCE=..\D_main.c
DEP_CPP_D_MAI=\
	"..\Am_map.h"\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_main.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Dconsole.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\F_finale.h"\
	"..\F_wipe.h"\
	"..\G_game.h"\
	"..\Hu_stuff.h"\
	"..\I_sound.h"\
	"..\I_system.h"\
	"..\I_video.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\M_menu.h"\
	"..\M_misc.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_setup.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\St_stuff.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Wi_stuff.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_D_MAI=\
	".\alues.h"\
	".\nistd.h"\
	
# End Source File
# Begin Source File

SOURCE=..\D_net.c
DEP_CPP_D_NET=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Dconsole.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\G_game.h"\
	"..\I_net.h"\
	"..\I_system.h"\
	"..\I_video.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_menu.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\Tables.h"\
	
NODEP_CPP_D_NET=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=.\DCDoom.rc
# End Source File
# Begin Source File

SOURCE=..\Dconsole.c
DEP_CPP_DCONS=\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\G_game.h"\
	"..\Hu_stuff.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_cheat.h"\
	"..\M_fixed.h"\
	"..\P_inter.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_state.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_DCONS=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Doomdef.c
DEP_CPP_DOOMD=\
	"..\Doomdef.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Doomstat.c
DEP_CPP_DOOMS=\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\Tables.h"\
	
NODEP_CPP_DOOMS=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Dstrings.c
DEP_CPP_DSTRI=\
	"..\D_englsh.h"\
	"..\D_french.h"\
	"..\Dstrings.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Dxerr.c
# End Source File
# Begin Source File

SOURCE=..\F_finale.c
DEP_CPP_F_FIN=\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\Hu_stuff.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_state.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_F_FIN=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\F_wipe.c
DEP_CPP_F_WIP=\
	"..\D_items.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\F_wipe.h"\
	"..\I_video.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_state.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_F_WIP=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\G_game.c
DEP_CPP_G_GAM=\
	"..\Am_map.h"\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_main.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\F_finale.h"\
	"..\G_game.h"\
	"..\Hu_stuff.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\M_menu.h"\
	"..\M_misc.h"\
	"..\M_random.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_saveg.h"\
	"..\P_setup.h"\
	"..\P_spec.h"\
	"..\P_tick.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_sky.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\St_stuff.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Wi_stuff.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_G_GAM=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Hu_lib.c
DEP_CPP_HU_LI=\
	"..\D_items.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\Hu_lib.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	
NODEP_CPP_HU_LI=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Hu_stuff.c
DEP_CPP_HU_ST=\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Dconsole.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\Hu_lib.h"\
	"..\Hu_stuff.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_defs.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_HU_ST=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\I_main.c
DEP_CPP_I_MAI=\
	"..\D_event.h"\
	"..\D_main.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\M_argv.h"\
	
NODEP_CPP_I_MAI=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\i_music.c
DEP_CPP_I_MUS=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\i_music.h"\
	"..\I_sound.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\M_misc.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_I_MUS=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\I_net.c
DEP_CPP_I_NET=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_net.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\Tables.h"\
	
NODEP_CPP_I_NET=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\I_sound.c
DEP_CPP_I_SOU=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_sound.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\M_misc.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_I_SOU=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\I_system.c
DEP_CPP_I_SYS=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\G_game.h"\
	"..\I_sound.h"\
	"..\I_system.h"\
	"..\I_video.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_misc.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	
NODEP_CPP_I_SYS=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\I_video.c
DEP_CPP_I_VID=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_main.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_state.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	
NODEP_CPP_I_VID=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Info.c
DEP_CPP_INFO_=\
	"..\D_think.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	
NODEP_CPP_INFO_=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\M_argv.c
# End Source File
# Begin Source File

SOURCE=..\M_bbox.c
DEP_CPP_M_BBO=\
	"..\M_bbox.h"\
	"..\M_fixed.h"\
	
# End Source File
# Begin Source File

SOURCE=..\M_cheat.c
DEP_CPP_M_CHE=\
	"..\M_cheat.h"\
	
# End Source File
# Begin Source File

SOURCE=..\M_fixed.c
DEP_CPP_M_FIX=\
	"..\D_event.h"\
	"..\D_ticcmd.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\M_fixed.h"\
	
NODEP_CPP_M_FIX=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\M_menu.c
DEP_CPP_M_MEN=\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_main.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Dconsole.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\G_game.h"\
	"..\Hu_stuff.h"\
	"..\I_system.h"\
	"..\I_video.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\M_menu.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_M_MEN=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\M_misc.c
DEP_CPP_M_MIS=\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\Hu_stuff.h"\
	"..\I_system.h"\
	"..\I_video.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\M_misc.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_state.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_M_MIS=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\M_random.c
# End Source File
# Begin Source File

SOURCE=..\M_swap.c
DEP_CPP_M_SWA=\
	"..\M_swap.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_ceilng.c
DEP_CPP_P_CEI=\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_CEI=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_doors.c
DEP_CPP_P_DOO=\
	"..\D_englsh.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_DOO=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_enemy.c
DEP_CPP_P_ENE=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\G_game.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	
NODEP_CPP_P_ENE=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_floor.c
DEP_CPP_P_FLO=\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_FLO=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_inter.c
DEP_CPP_P_INT=\
	"..\Am_map.h"\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_inter.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	
NODEP_CPP_P_INT=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_lights.c
DEP_CPP_P_LIG=\
	"..\D_items.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_LIG=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_map.c
DEP_CPP_P_MAP=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_bbox.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	
NODEP_CPP_P_MAP=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_maputl.c
DEP_CPP_P_MAPU=\
	"..\D_items.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_bbox.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	
NODEP_CPP_P_MAPU=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_mobj.c
DEP_CPP_P_MOB=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Hu_stuff.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\St_stuff.h"\
	"..\Tables.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_MOB=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_plats.c
DEP_CPP_P_PLA=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_PLA=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_pspr.c
DEP_CPP_P_PSP=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	
NODEP_CPP_P_PSP=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_saveg.c
DEP_CPP_P_SAV=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_SAV=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_setup.c
DEP_CPP_P_SET=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\G_game.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_bbox.h"\
	"..\M_fixed.h"\
	"..\M_swap.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Tables.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_SET=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_sight.c
DEP_CPP_P_SIG=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	
NODEP_CPP_P_SIG=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_spec.c
DEP_CPP_P_SPE=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\G_game.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_SPE=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_switch.c
DEP_CPP_P_SWI=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\G_game.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	
NODEP_CPP_P_SWI=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_telept.c
DEP_CPP_P_TEL=\
	"..\D_items.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	
NODEP_CPP_P_TEL=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_tick.c
DEP_CPP_P_TIC=\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_P_TIC=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\P_user.c
DEP_CPP_P_USE=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	
NODEP_CPP_P_USE=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\R_bsp.c
DEP_CPP_R_BSP=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_bbox.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	
NODEP_CPP_R_BSP=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\R_data.c
DEP_CPP_R_DAT=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_swap.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_sky.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_R_DAT=\
	".\alues.h"\
	".\lloca.h"\
	
# End Source File
# Begin Source File

SOURCE=..\R_draw.c
DEP_CPP_R_DRA=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_R_DRA=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\R_main.c
DEP_CPP_R_MAI=\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_bbox.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_sky.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	
NODEP_CPP_R_MAI=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\R_plane.c
DEP_CPP_R_PLA=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_sky.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_R_PLA=\
	".\alues.h"\
	".\hsgintr.h"\
	
# End Source File
# Begin Source File

SOURCE=..\R_segs.c
DEP_CPP_R_SEG=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_sky.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	
NODEP_CPP_R_SEG=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\R_sky.c
DEP_CPP_R_SKY=\
	"..\D_items.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_sky.h"\
	"..\R_state.h"\
	"..\Tables.h"\
	
NODEP_CPP_R_SKY=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\R_things.c
DEP_CPP_R_THI=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_R_THI=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\S_sound.c
DEP_CPP_S_SOU=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\i_music.h"\
	"..\I_sound.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_S_SOU=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Sounds.c
DEP_CPP_SOUND=\
	"..\Doomtype.h"\
	"..\Sounds.h"\
	
NODEP_CPP_SOUND=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\St_lib.c
DEP_CPP_ST_LI=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\St_lib.h"\
	"..\St_stuff.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_ST_LI=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\St_stuff.c
DEP_CPP_ST_ST=\
	"..\Am_map.h"\
	"..\D_englsh.h"\
	"..\D_event.h"\
	"..\D_french.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dstrings.h"\
	"..\G_game.h"\
	"..\I_system.h"\
	"..\I_video.h"\
	"..\Info.h"\
	"..\M_cheat.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\P_inter.h"\
	"..\P_local.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\P_spec.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\St_lib.h"\
	"..\St_stuff.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_ST_ST=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Tables.c
DEP_CPP_TABLE=\
	"..\M_fixed.h"\
	"..\Tables.h"\
	
# End Source File
# Begin Source File

SOURCE=..\V_video.c
DEP_CPP_V_VID=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_bbox.h"\
	"..\M_fixed.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	
NODEP_CPP_V_VID=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\W_wad.c
DEP_CPP_W_WAD=\
	"..\D_event.h"\
	"..\D_ticcmd.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\M_swap.h"\
	"..\W_wad.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_W_WAD=\
	".\alues.h"\
	".\lloca.h"\
	".\nistd.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Wi_stuff.c
DEP_CPP_WI_ST=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\G_game.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_fixed.h"\
	"..\M_random.h"\
	"..\M_swap.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\R_bsp.h"\
	"..\R_data.h"\
	"..\R_defs.h"\
	"..\R_draw.h"\
	"..\R_local.h"\
	"..\R_main.h"\
	"..\R_plane.h"\
	"..\R_segs.h"\
	"..\R_state.h"\
	"..\R_things.h"\
	"..\S_sound.h"\
	"..\Sounds.h"\
	"..\Tables.h"\
	"..\V_video.h"\
	"..\W_wad.h"\
	"..\Wi_stuff.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_WI_ST=\
	".\alues.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Windoom.c
DEP_CPP_WINDO=\
	"..\D_event.h"\
	"..\D_items.h"\
	"..\D_main.h"\
	"..\D_net.h"\
	"..\D_player.h"\
	"..\D_think.h"\
	"..\D_ticcmd.h"\
	"..\Doomdata.h"\
	"..\Doomdef.h"\
	"..\Doomstat.h"\
	"..\Doomtype.h"\
	"..\Dxerr.h"\
	"..\G_game.h"\
	"..\I_midi.h"\
	"..\I_system.h"\
	"..\Info.h"\
	"..\M_argv.h"\
	"..\M_fixed.h"\
	"..\P_mobj.h"\
	"..\P_pspr.h"\
	"..\Tables.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_WINDO=\
	".\alues.h"\
	".\apledev.h"\
	".\aplusag.h"\
	".\eddcdrm.h"\
	".\eddstor.h"\
	".\egagdrm.h"\
	".\erstore.h"\
	".\etinfo.h"\
	".\latutil.h"\
	
# End Source File
# Begin Source File

SOURCE=..\Z_zone.c
DEP_CPP_Z_ZON=\
	"..\D_event.h"\
	"..\D_ticcmd.h"\
	"..\Doomdef.h"\
	"..\Doomtype.h"\
	"..\I_system.h"\
	"..\Z_zone.h"\
	
NODEP_CPP_Z_ZON=\
	".\alues.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Am_map.h
# End Source File
# Begin Source File

SOURCE=..\D_englsh.h
# End Source File
# Begin Source File

SOURCE=..\D_event.h
# End Source File
# Begin Source File

SOURCE=..\D_french.h
# End Source File
# Begin Source File

SOURCE=..\D_items.h
# End Source File
# Begin Source File

SOURCE=..\D_main.h
# End Source File
# Begin Source File

SOURCE=..\D_net.h
# End Source File
# Begin Source File

SOURCE=..\D_player.h
# End Source File
# Begin Source File

SOURCE=..\D_textur.h
# End Source File
# Begin Source File

SOURCE=..\D_think.h
# End Source File
# Begin Source File

SOURCE=..\D_ticcmd.h
# End Source File
# Begin Source File

SOURCE=..\Dconsole.h
# End Source File
# Begin Source File

SOURCE=..\Doomdata.h
# End Source File
# Begin Source File

SOURCE=..\Doomdef.h
# End Source File
# Begin Source File

SOURCE=..\Doomstat.h
# End Source File
# Begin Source File

SOURCE=..\Doomtype.h
# End Source File
# Begin Source File

SOURCE=..\Dstrings.h
# End Source File
# Begin Source File

SOURCE=..\Dxerr.h
# End Source File
# Begin Source File

SOURCE=..\F_finale.h
# End Source File
# Begin Source File

SOURCE=..\F_wipe.h
# End Source File
# Begin Source File

SOURCE=..\G_game.h
# End Source File
# Begin Source File

SOURCE=..\Hu_lib.h
# End Source File
# Begin Source File

SOURCE=..\Hu_stuff.h
# End Source File
# Begin Source File

SOURCE=..\i_music.h
# End Source File
# Begin Source File

SOURCE=..\I_net.h
# End Source File
# Begin Source File

SOURCE=..\I_sound.h
# End Source File
# Begin Source File

SOURCE=..\I_system.h
# End Source File
# Begin Source File

SOURCE=..\I_video.h
# End Source File
# Begin Source File

SOURCE=..\Info.h
# End Source File
# Begin Source File

SOURCE=..\M_argv.h
# End Source File
# Begin Source File

SOURCE=..\M_bbox.h
# End Source File
# Begin Source File

SOURCE=..\M_cd.h
# End Source File
# Begin Source File

SOURCE=..\M_cheat.h
# End Source File
# Begin Source File

SOURCE=..\M_fixed.h
# End Source File
# Begin Source File

SOURCE=..\M_menu.h
# End Source File
# Begin Source File

SOURCE=..\M_misc.h
# End Source File
# Begin Source File

SOURCE=..\M_music.h
# End Source File
# Begin Source File

SOURCE=..\M_random.h
# End Source File
# Begin Source File

SOURCE=..\M_swap.h
# End Source File
# Begin Source File

SOURCE=..\P_inter.h
# End Source File
# Begin Source File

SOURCE=..\P_local.h
# End Source File
# Begin Source File

SOURCE=..\P_mobj.h
# End Source File
# Begin Source File

SOURCE=..\P_pspr.h
# End Source File
# Begin Source File

SOURCE=..\P_saveg.h
# End Source File
# Begin Source File

SOURCE=..\P_setup.h
# End Source File
# Begin Source File

SOURCE=..\P_spec.h
# End Source File
# Begin Source File

SOURCE=..\P_tick.h
# End Source File
# Begin Source File

SOURCE=..\Qmus2mid.h
# End Source File
# Begin Source File

SOURCE=..\R_bsp.h
# End Source File
# Begin Source File

SOURCE=..\R_data.h
# End Source File
# Begin Source File

SOURCE=..\R_defs.h
# End Source File
# Begin Source File

SOURCE=..\R_draw.h
# End Source File
# Begin Source File

SOURCE=..\R_local.h
# End Source File
# Begin Source File

SOURCE=..\R_main.h
# End Source File
# Begin Source File

SOURCE=..\R_plane.h
# End Source File
# Begin Source File

SOURCE=..\R_segs.h
# End Source File
# Begin Source File

SOURCE=..\R_sky.h
# End Source File
# Begin Source File

SOURCE=..\R_state.h
# End Source File
# Begin Source File

SOURCE=..\R_things.h
# End Source File
# Begin Source File

SOURCE=..\Resource.h
# End Source File
# Begin Source File

SOURCE=..\S_sound.h
# End Source File
# Begin Source File

SOURCE=..\Sounds.h
# End Source File
# Begin Source File

SOURCE=..\St_lib.h
# End Source File
# Begin Source File

SOURCE=..\St_stuff.h
# End Source File
# Begin Source File

SOURCE=..\Tables.h
# End Source File
# Begin Source File

SOURCE=..\V_video.h
# End Source File
# Begin Source File

SOURCE=..\W_wad.h
# End Source File
# Begin Source File

SOURCE=..\Wi_stuff.h
# End Source File
# Begin Source File

SOURCE=..\Z_zone.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\gmd_v100.mpb
# End Source File
# Begin Source File

SOURCE=.\gmi_v100.mpb
# End Source File
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# End Target
# End Project
