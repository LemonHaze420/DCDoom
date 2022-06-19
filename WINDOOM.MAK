# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=WinDoom - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to WinDoom - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WinDoom - Win32 Release" && "$(CFG)" !=\
 "WinDoom - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinDoom.mak" CFG="WinDoom - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinDoom - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WinDoom - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "WinDoom - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinDoom - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinDoom_"
# PROP BASE Intermediate_Dir "WinDoom_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\WinDoom.exe"

CLEAN : 
	-@erase "$(INTDIR)\am_map.obj"
	-@erase "$(INTDIR)\d_console.obj"
	-@erase "$(INTDIR)\d_items.obj"
	-@erase "$(INTDIR)\d_main.obj"
	-@erase "$(INTDIR)\d_net.obj"
	-@erase "$(INTDIR)\doomdef.obj"
	-@erase "$(INTDIR)\doomstat.obj"
	-@erase "$(INTDIR)\dstrings.obj"
	-@erase "$(INTDIR)\dxerr.obj"
	-@erase "$(INTDIR)\f_finale.obj"
	-@erase "$(INTDIR)\f_wipe.obj"
	-@erase "$(INTDIR)\g_game.obj"
	-@erase "$(INTDIR)\hu_lib.obj"
	-@erase "$(INTDIR)\hu_stuff.obj"
	-@erase "$(INTDIR)\i_cd.obj"
	-@erase "$(INTDIR)\i_main.obj"
	-@erase "$(INTDIR)\i_midi.obj"
	-@erase "$(INTDIR)\i_net.obj"
	-@erase "$(INTDIR)\i_sound.obj"
	-@erase "$(INTDIR)\i_system.obj"
	-@erase "$(INTDIR)\i_video.obj"
	-@erase "$(INTDIR)\info.obj"
	-@erase "$(INTDIR)\m_argv.obj"
	-@erase "$(INTDIR)\m_bbox.obj"
	-@erase "$(INTDIR)\m_cheat.obj"
	-@erase "$(INTDIR)\m_fixed.obj"
	-@erase "$(INTDIR)\m_menu.obj"
	-@erase "$(INTDIR)\m_misc.obj"
	-@erase "$(INTDIR)\m_music.obj"
	-@erase "$(INTDIR)\m_random.obj"
	-@erase "$(INTDIR)\m_swap.obj"
	-@erase "$(INTDIR)\p_ceilng.obj"
	-@erase "$(INTDIR)\p_doors.obj"
	-@erase "$(INTDIR)\p_enemy.obj"
	-@erase "$(INTDIR)\p_floor.obj"
	-@erase "$(INTDIR)\p_inter.obj"
	-@erase "$(INTDIR)\p_lights.obj"
	-@erase "$(INTDIR)\p_map.obj"
	-@erase "$(INTDIR)\p_maputl.obj"
	-@erase "$(INTDIR)\p_mobj.obj"
	-@erase "$(INTDIR)\p_plats.obj"
	-@erase "$(INTDIR)\p_pspr.obj"
	-@erase "$(INTDIR)\p_saveg.obj"
	-@erase "$(INTDIR)\p_setup.obj"
	-@erase "$(INTDIR)\p_sight.obj"
	-@erase "$(INTDIR)\p_spec.obj"
	-@erase "$(INTDIR)\p_switch.obj"
	-@erase "$(INTDIR)\p_telept.obj"
	-@erase "$(INTDIR)\p_tick.obj"
	-@erase "$(INTDIR)\p_user.obj"
	-@erase "$(INTDIR)\qmus2mid.obj"
	-@erase "$(INTDIR)\r_bsp.obj"
	-@erase "$(INTDIR)\r_data.obj"
	-@erase "$(INTDIR)\r_draw.obj"
	-@erase "$(INTDIR)\r_main.obj"
	-@erase "$(INTDIR)\r_plane.obj"
	-@erase "$(INTDIR)\r_segs.obj"
	-@erase "$(INTDIR)\r_sky.obj"
	-@erase "$(INTDIR)\r_things.obj"
	-@erase "$(INTDIR)\s_sound.obj"
	-@erase "$(INTDIR)\sounds.obj"
	-@erase "$(INTDIR)\st_lib.obj"
	-@erase "$(INTDIR)\st_stuff.obj"
	-@erase "$(INTDIR)\tables.obj"
	-@erase "$(INTDIR)\v_video.obj"
	-@erase "$(INTDIR)\w_wad.obj"
	-@erase "$(INTDIR)\wi_stuff.obj"
	-@erase "$(INTDIR)\WINDOOM.obj"
	-@erase "$(INTDIR)\windoom.res"
	-@erase "$(INTDIR)\z_zone.obj"
	-@erase "$(OUTDIR)\WinDoom.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/WinDoom.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/windoom.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WinDoom.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dsound.lib ddraw.lib dinput.lib winmm.lib wsock32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib dsound.lib ddraw.lib dinput.lib winmm.lib wsock32.lib\
 /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/WinDoom.pdb"\
 /machine:I386 /out:"$(OUTDIR)/WinDoom.exe" 
LINK32_OBJS= \
	"$(INTDIR)\am_map.obj" \
	"$(INTDIR)\d_console.obj" \
	"$(INTDIR)\d_items.obj" \
	"$(INTDIR)\d_main.obj" \
	"$(INTDIR)\d_net.obj" \
	"$(INTDIR)\doomdef.obj" \
	"$(INTDIR)\doomstat.obj" \
	"$(INTDIR)\dstrings.obj" \
	"$(INTDIR)\dxerr.obj" \
	"$(INTDIR)\f_finale.obj" \
	"$(INTDIR)\f_wipe.obj" \
	"$(INTDIR)\g_game.obj" \
	"$(INTDIR)\hu_lib.obj" \
	"$(INTDIR)\hu_stuff.obj" \
	"$(INTDIR)\i_cd.obj" \
	"$(INTDIR)\i_main.obj" \
	"$(INTDIR)\i_midi.obj" \
	"$(INTDIR)\i_net.obj" \
	"$(INTDIR)\i_sound.obj" \
	"$(INTDIR)\i_system.obj" \
	"$(INTDIR)\i_video.obj" \
	"$(INTDIR)\info.obj" \
	"$(INTDIR)\m_argv.obj" \
	"$(INTDIR)\m_bbox.obj" \
	"$(INTDIR)\m_cheat.obj" \
	"$(INTDIR)\m_fixed.obj" \
	"$(INTDIR)\m_menu.obj" \
	"$(INTDIR)\m_misc.obj" \
	"$(INTDIR)\m_music.obj" \
	"$(INTDIR)\m_random.obj" \
	"$(INTDIR)\m_swap.obj" \
	"$(INTDIR)\p_ceilng.obj" \
	"$(INTDIR)\p_doors.obj" \
	"$(INTDIR)\p_enemy.obj" \
	"$(INTDIR)\p_floor.obj" \
	"$(INTDIR)\p_inter.obj" \
	"$(INTDIR)\p_lights.obj" \
	"$(INTDIR)\p_map.obj" \
	"$(INTDIR)\p_maputl.obj" \
	"$(INTDIR)\p_mobj.obj" \
	"$(INTDIR)\p_plats.obj" \
	"$(INTDIR)\p_pspr.obj" \
	"$(INTDIR)\p_saveg.obj" \
	"$(INTDIR)\p_setup.obj" \
	"$(INTDIR)\p_sight.obj" \
	"$(INTDIR)\p_spec.obj" \
	"$(INTDIR)\p_switch.obj" \
	"$(INTDIR)\p_telept.obj" \
	"$(INTDIR)\p_tick.obj" \
	"$(INTDIR)\p_user.obj" \
	"$(INTDIR)\qmus2mid.obj" \
	"$(INTDIR)\r_bsp.obj" \
	"$(INTDIR)\r_data.obj" \
	"$(INTDIR)\r_draw.obj" \
	"$(INTDIR)\r_main.obj" \
	"$(INTDIR)\r_plane.obj" \
	"$(INTDIR)\r_segs.obj" \
	"$(INTDIR)\r_sky.obj" \
	"$(INTDIR)\r_things.obj" \
	"$(INTDIR)\s_sound.obj" \
	"$(INTDIR)\sounds.obj" \
	"$(INTDIR)\st_lib.obj" \
	"$(INTDIR)\st_stuff.obj" \
	"$(INTDIR)\tables.obj" \
	"$(INTDIR)\v_video.obj" \
	"$(INTDIR)\w_wad.obj" \
	"$(INTDIR)\wi_stuff.obj" \
	"$(INTDIR)\WINDOOM.obj" \
	"$(INTDIR)\windoom.res" \
	"$(INTDIR)\z_zone.obj"

"$(OUTDIR)\WinDoom.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDoom0"
# PROP BASE Intermediate_Dir "WinDoom0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\WinDoom.exe"

CLEAN : 
	-@erase "$(INTDIR)\am_map.obj"
	-@erase "$(INTDIR)\d_console.obj"
	-@erase "$(INTDIR)\d_items.obj"
	-@erase "$(INTDIR)\d_main.obj"
	-@erase "$(INTDIR)\d_net.obj"
	-@erase "$(INTDIR)\doomdef.obj"
	-@erase "$(INTDIR)\doomstat.obj"
	-@erase "$(INTDIR)\dstrings.obj"
	-@erase "$(INTDIR)\dxerr.obj"
	-@erase "$(INTDIR)\f_finale.obj"
	-@erase "$(INTDIR)\f_wipe.obj"
	-@erase "$(INTDIR)\g_game.obj"
	-@erase "$(INTDIR)\hu_lib.obj"
	-@erase "$(INTDIR)\hu_stuff.obj"
	-@erase "$(INTDIR)\i_cd.obj"
	-@erase "$(INTDIR)\i_main.obj"
	-@erase "$(INTDIR)\i_midi.obj"
	-@erase "$(INTDIR)\i_net.obj"
	-@erase "$(INTDIR)\i_sound.obj"
	-@erase "$(INTDIR)\i_system.obj"
	-@erase "$(INTDIR)\i_video.obj"
	-@erase "$(INTDIR)\info.obj"
	-@erase "$(INTDIR)\m_argv.obj"
	-@erase "$(INTDIR)\m_bbox.obj"
	-@erase "$(INTDIR)\m_cheat.obj"
	-@erase "$(INTDIR)\m_fixed.obj"
	-@erase "$(INTDIR)\m_menu.obj"
	-@erase "$(INTDIR)\m_misc.obj"
	-@erase "$(INTDIR)\m_music.obj"
	-@erase "$(INTDIR)\m_random.obj"
	-@erase "$(INTDIR)\m_swap.obj"
	-@erase "$(INTDIR)\p_ceilng.obj"
	-@erase "$(INTDIR)\p_doors.obj"
	-@erase "$(INTDIR)\p_enemy.obj"
	-@erase "$(INTDIR)\p_floor.obj"
	-@erase "$(INTDIR)\p_inter.obj"
	-@erase "$(INTDIR)\p_lights.obj"
	-@erase "$(INTDIR)\p_map.obj"
	-@erase "$(INTDIR)\p_maputl.obj"
	-@erase "$(INTDIR)\p_mobj.obj"
	-@erase "$(INTDIR)\p_plats.obj"
	-@erase "$(INTDIR)\p_pspr.obj"
	-@erase "$(INTDIR)\p_saveg.obj"
	-@erase "$(INTDIR)\p_setup.obj"
	-@erase "$(INTDIR)\p_sight.obj"
	-@erase "$(INTDIR)\p_spec.obj"
	-@erase "$(INTDIR)\p_switch.obj"
	-@erase "$(INTDIR)\p_telept.obj"
	-@erase "$(INTDIR)\p_tick.obj"
	-@erase "$(INTDIR)\p_user.obj"
	-@erase "$(INTDIR)\qmus2mid.obj"
	-@erase "$(INTDIR)\r_bsp.obj"
	-@erase "$(INTDIR)\r_data.obj"
	-@erase "$(INTDIR)\r_draw.obj"
	-@erase "$(INTDIR)\r_main.obj"
	-@erase "$(INTDIR)\r_plane.obj"
	-@erase "$(INTDIR)\r_segs.obj"
	-@erase "$(INTDIR)\r_sky.obj"
	-@erase "$(INTDIR)\r_things.obj"
	-@erase "$(INTDIR)\s_sound.obj"
	-@erase "$(INTDIR)\sounds.obj"
	-@erase "$(INTDIR)\st_lib.obj"
	-@erase "$(INTDIR)\st_stuff.obj"
	-@erase "$(INTDIR)\tables.obj"
	-@erase "$(INTDIR)\v_video.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\w_wad.obj"
	-@erase "$(INTDIR)\wi_stuff.obj"
	-@erase "$(INTDIR)\WINDOOM.obj"
	-@erase "$(INTDIR)\windoom.res"
	-@erase "$(INTDIR)\z_zone.obj"
	-@erase "$(OUTDIR)\WinDoom.exe"
	-@erase "$(OUTDIR)\WinDoom.ilk"
	-@erase "$(OUTDIR)\WinDoom.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/WinDoom.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/windoom.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WinDoom.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dsound.lib ddraw.lib dinput.lib winmm.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib dsound.lib ddraw.lib dinput.lib winmm.lib wsock32.lib\
 /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/WinDoom.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/WinDoom.exe" 
LINK32_OBJS= \
	"$(INTDIR)\am_map.obj" \
	"$(INTDIR)\d_console.obj" \
	"$(INTDIR)\d_items.obj" \
	"$(INTDIR)\d_main.obj" \
	"$(INTDIR)\d_net.obj" \
	"$(INTDIR)\doomdef.obj" \
	"$(INTDIR)\doomstat.obj" \
	"$(INTDIR)\dstrings.obj" \
	"$(INTDIR)\dxerr.obj" \
	"$(INTDIR)\f_finale.obj" \
	"$(INTDIR)\f_wipe.obj" \
	"$(INTDIR)\g_game.obj" \
	"$(INTDIR)\hu_lib.obj" \
	"$(INTDIR)\hu_stuff.obj" \
	"$(INTDIR)\i_cd.obj" \
	"$(INTDIR)\i_main.obj" \
	"$(INTDIR)\i_midi.obj" \
	"$(INTDIR)\i_net.obj" \
	"$(INTDIR)\i_sound.obj" \
	"$(INTDIR)\i_system.obj" \
	"$(INTDIR)\i_video.obj" \
	"$(INTDIR)\info.obj" \
	"$(INTDIR)\m_argv.obj" \
	"$(INTDIR)\m_bbox.obj" \
	"$(INTDIR)\m_cheat.obj" \
	"$(INTDIR)\m_fixed.obj" \
	"$(INTDIR)\m_menu.obj" \
	"$(INTDIR)\m_misc.obj" \
	"$(INTDIR)\m_music.obj" \
	"$(INTDIR)\m_random.obj" \
	"$(INTDIR)\m_swap.obj" \
	"$(INTDIR)\p_ceilng.obj" \
	"$(INTDIR)\p_doors.obj" \
	"$(INTDIR)\p_enemy.obj" \
	"$(INTDIR)\p_floor.obj" \
	"$(INTDIR)\p_inter.obj" \
	"$(INTDIR)\p_lights.obj" \
	"$(INTDIR)\p_map.obj" \
	"$(INTDIR)\p_maputl.obj" \
	"$(INTDIR)\p_mobj.obj" \
	"$(INTDIR)\p_plats.obj" \
	"$(INTDIR)\p_pspr.obj" \
	"$(INTDIR)\p_saveg.obj" \
	"$(INTDIR)\p_setup.obj" \
	"$(INTDIR)\p_sight.obj" \
	"$(INTDIR)\p_spec.obj" \
	"$(INTDIR)\p_switch.obj" \
	"$(INTDIR)\p_telept.obj" \
	"$(INTDIR)\p_tick.obj" \
	"$(INTDIR)\p_user.obj" \
	"$(INTDIR)\qmus2mid.obj" \
	"$(INTDIR)\r_bsp.obj" \
	"$(INTDIR)\r_data.obj" \
	"$(INTDIR)\r_draw.obj" \
	"$(INTDIR)\r_main.obj" \
	"$(INTDIR)\r_plane.obj" \
	"$(INTDIR)\r_segs.obj" \
	"$(INTDIR)\r_sky.obj" \
	"$(INTDIR)\r_things.obj" \
	"$(INTDIR)\s_sound.obj" \
	"$(INTDIR)\sounds.obj" \
	"$(INTDIR)\st_lib.obj" \
	"$(INTDIR)\st_stuff.obj" \
	"$(INTDIR)\tables.obj" \
	"$(INTDIR)\v_video.obj" \
	"$(INTDIR)\w_wad.obj" \
	"$(INTDIR)\wi_stuff.obj" \
	"$(INTDIR)\WINDOOM.obj" \
	"$(INTDIR)\windoom.res" \
	"$(INTDIR)\z_zone.obj"

"$(OUTDIR)\WinDoom.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "WinDoom - Win32 Release"
# Name "WinDoom - Win32 Debug"

!IF  "$(CFG)" == "WinDoom - Win32 Release"

!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\windoom.rc

"$(INTDIR)\windoom.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\d_console.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_D_CON=\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_cheat.h"\
	".\m_fixed.h"\
	".\m_music.h"\
	".\p_inter.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_defs.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\d_console.obj" : $(SOURCE) $(DEP_CPP_D_CON) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_D_CON=\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_cheat.h"\
	".\m_fixed.h"\
	".\m_music.h"\
	".\p_inter.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_state.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\d_console.obj" : $(SOURCE) $(DEP_CPP_D_CON) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\d_items.c
DEP_CPP_D_ITE=\
	".\d_items.h"\
	".\d_think.h"\
	".\doomdef.h"\
	".\info.h"\
	

"$(INTDIR)\d_items.obj" : $(SOURCE) $(DEP_CPP_D_ITE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\d_main.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_D_MAI=\
	".\am_map.h"\
	".\d_console.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_main.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\f_finale.h"\
	".\f_wipe.h"\
	".\g_game.h"\
	".\hu_stuff.h"\
	".\i_sound.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_menu.h"\
	".\m_misc.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_setup.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\wi_stuff.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\unistd.h"\
	
NODEP_CPP_D_MAI=\
	".\multires.h"\
	

"$(INTDIR)\d_main.obj" : $(SOURCE) $(DEP_CPP_D_MAI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_D_MAI=\
	".\am_map.h"\
	".\d_console.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_main.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\f_finale.h"\
	".\f_wipe.h"\
	".\g_game.h"\
	".\hu_stuff.h"\
	".\i_sound.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_menu.h"\
	".\m_misc.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_setup.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\wi_stuff.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\unistd.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_D_MAI=\
	".\multires.h"\
	

"$(INTDIR)\d_main.obj" : $(SOURCE) $(DEP_CPP_D_MAI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\d_net.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_D_NET=\
	".\d_console.h"\
	".\d_event.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_net.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\m_menu.h"\
	

"$(INTDIR)\d_net.obj" : $(SOURCE) $(DEP_CPP_D_NET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_D_NET=\
	".\d_console.h"\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_net.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_menu.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\d_net.obj" : $(SOURCE) $(DEP_CPP_D_NET) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\doomdef.c
DEP_CPP_DOOMD=\
	".\doomdef.h"\
	

"$(INTDIR)\doomdef.obj" : $(SOURCE) $(DEP_CPP_DOOMD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\doomstat.c
DEP_CPP_DOOMS=\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\doomstat.obj" : $(SOURCE) $(DEP_CPP_DOOMS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dstrings.c
DEP_CPP_DSTRI=\
	".\d_englsh.h"\
	".\d_french.h"\
	".\dstrings.h"\
	

"$(INTDIR)\dstrings.obj" : $(SOURCE) $(DEP_CPP_DSTRI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dxerr.c
DEP_CPP_DXERR=\
	{$(INCLUDE)}"\dinput.h"\
	

"$(INTDIR)\dxerr.obj" : $(SOURCE) $(DEP_CPP_DXERR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\f_finale.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_F_FIN=\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_state.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\f_finale.obj" : $(SOURCE) $(DEP_CPP_F_FIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_F_FIN=\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_state.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\f_finale.obj" : $(SOURCE) $(DEP_CPP_F_FIN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\f_wipe.c
DEP_CPP_F_WIP=\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\f_wipe.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_state.h"\
	".\tables.h"\
	".\v_video.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\f_wipe.obj" : $(SOURCE) $(DEP_CPP_F_WIP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\g_game.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_G_GAM=\
	".\am_map.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_main.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\f_finale.h"\
	".\g_game.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_menu.h"\
	".\m_misc.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_saveg.h"\
	".\p_setup.h"\
	".\p_spec.h"\
	".\p_tick.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_sky.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\wi_stuff.h"\
	".\z_zone.h"\
	
NODEP_CPP_G_GAM=\
	".\multires.h"\
	

"$(INTDIR)\g_game.obj" : $(SOURCE) $(DEP_CPP_G_GAM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_G_GAM=\
	".\am_map.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_main.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\f_finale.h"\
	".\g_game.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_menu.h"\
	".\m_misc.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_saveg.h"\
	".\p_setup.h"\
	".\p_spec.h"\
	".\p_tick.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_sky.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\wi_stuff.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_G_GAM=\
	".\multires.h"\
	

"$(INTDIR)\g_game.obj" : $(SOURCE) $(DEP_CPP_G_GAM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\hu_lib.c
DEP_CPP_HU_LI=\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\hu_lib.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\v_video.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_HU_LI=\
	".\multires.h"\
	

"$(INTDIR)\hu_lib.obj" : $(SOURCE) $(DEP_CPP_HU_LI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\hu_stuff.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_HU_ST=\
	".\d_console.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_think.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\hu_lib.h"\
	".\hu_stuff.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\r_defs.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\hu_stuff.obj" : $(SOURCE) $(DEP_CPP_HU_ST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_HU_ST=\
	".\d_console.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\hu_lib.h"\
	".\hu_stuff.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_defs.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\hu_stuff.obj" : $(SOURCE) $(DEP_CPP_HU_ST) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\i_cd.c
DEP_CPP_I_CD_=\
	".\i_cd.h"\
	

"$(INTDIR)\i_cd.obj" : $(SOURCE) $(DEP_CPP_I_CD_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\i_main.c
DEP_CPP_I_MAI=\
	".\d_event.h"\
	".\d_main.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\m_argv.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\i_main.obj" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\i_midi.c
DEP_CPP_I_MID=\
	".\i_midi.h"\
	

"$(INTDIR)\i_midi.obj" : $(SOURCE) $(DEP_CPP_I_MID) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\i_net.c
DEP_CPP_I_NET=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_net.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\i_net.obj" : $(SOURCE) $(DEP_CPP_I_NET) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\i_sound.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_I_SOU=\
	".\d_event.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_sound.h"\
	".\i_system.h"\
	".\m_argv.h"\
	".\m_misc.h"\
	".\sounds.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\i_sound.obj" : $(SOURCE) $(DEP_CPP_I_SOU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_I_SOU=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_sound.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_misc.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\sounds.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\i_sound.obj" : $(SOURCE) $(DEP_CPP_I_SOU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\i_system.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_I_SYS=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_sound.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\m_misc.h"\
	".\sounds.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\i_system.obj" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_I_SYS=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_sound.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_misc.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\sounds.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\i_system.obj" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\i_video.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_I_VID=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_main.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_state.h"\
	".\tables.h"\
	".\v_video.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\i_video.obj" : $(SOURCE) $(DEP_CPP_I_VID) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_I_VID=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_main.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_state.h"\
	".\tables.h"\
	".\v_video.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\i_video.obj" : $(SOURCE) $(DEP_CPP_I_VID) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\info.c
DEP_CPP_INFO_=\
	".\d_think.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\sounds.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\info.obj" : $(SOURCE) $(DEP_CPP_INFO_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\m_argv.c

"$(INTDIR)\m_argv.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\m_bbox.c
DEP_CPP_M_BBO=\
	".\m_bbox.h"\
	".\m_fixed.h"\
	

"$(INTDIR)\m_bbox.obj" : $(SOURCE) $(DEP_CPP_M_BBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\m_cheat.c
DEP_CPP_M_CHE=\
	".\m_cheat.h"\
	

"$(INTDIR)\m_cheat.obj" : $(SOURCE) $(DEP_CPP_M_CHE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\m_fixed.c
DEP_CPP_M_FIX=\
	".\d_event.h"\
	".\d_ticcmd.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\m_fixed.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\m_fixed.obj" : $(SOURCE) $(DEP_CPP_M_FIX) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\m_menu.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_M_MEN=\
	".\d_console.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_main.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\g_game.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_menu.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	
NODEP_CPP_M_MEN=\
	".\multires.h"\
	

"$(INTDIR)\m_menu.obj" : $(SOURCE) $(DEP_CPP_M_MEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_M_MEN=\
	".\d_console.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_main.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\g_game.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_menu.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_M_MEN=\
	".\multires.h"\
	

"$(INTDIR)\m_menu.obj" : $(SOURCE) $(DEP_CPP_M_MEN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\m_misc.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_M_MIS=\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_misc.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_state.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\m_misc.obj" : $(SOURCE) $(DEP_CPP_M_MIS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_M_MIS=\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_misc.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_state.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\m_misc.obj" : $(SOURCE) $(DEP_CPP_M_MIS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\m_music.c
DEP_CPP_M_MUS=\
	".\i_cd.h"\
	".\i_midi.h"\
	

"$(INTDIR)\m_music.obj" : $(SOURCE) $(DEP_CPP_M_MUS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\m_random.c

"$(INTDIR)\m_random.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\m_swap.c
DEP_CPP_M_SWA=\
	".\m_swap.h"\
	

"$(INTDIR)\m_swap.obj" : $(SOURCE) $(DEP_CPP_M_SWA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_ceilng.c
DEP_CPP_P_CEI=\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_ceilng.obj" : $(SOURCE) $(DEP_CPP_P_CEI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_doors.c
DEP_CPP_P_DOO=\
	".\d_englsh.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_doors.obj" : $(SOURCE) $(DEP_CPP_P_DOO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_enemy.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_P_ENE=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_P_ENE=\
	".\multires.h"\
	

"$(INTDIR)\p_enemy.obj" : $(SOURCE) $(DEP_CPP_P_ENE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_P_ENE=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_P_ENE=\
	".\multires.h"\
	

"$(INTDIR)\p_enemy.obj" : $(SOURCE) $(DEP_CPP_P_ENE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_floor.c
DEP_CPP_P_FLO=\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_floor.obj" : $(SOURCE) $(DEP_CPP_P_FLO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_inter.c
DEP_CPP_P_INT=\
	".\am_map.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_inter.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_inter.obj" : $(SOURCE) $(DEP_CPP_P_INT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_lights.c
DEP_CPP_P_LIG=\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_lights.obj" : $(SOURCE) $(DEP_CPP_P_LIG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_map.c
DEP_CPP_P_MAP=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_map.obj" : $(SOURCE) $(DEP_CPP_P_MAP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_maputl.c
DEP_CPP_P_MAPU=\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_maputl.obj" : $(SOURCE) $(DEP_CPP_P_MAPU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_mobj.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_P_MOB=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\z_zone.h"\
	
NODEP_CPP_P_MOB=\
	".\multires.h"\
	

"$(INTDIR)\p_mobj.obj" : $(SOURCE) $(DEP_CPP_P_MOB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_P_MOB=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\hu_stuff.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_P_MOB=\
	".\multires.h"\
	

"$(INTDIR)\p_mobj.obj" : $(SOURCE) $(DEP_CPP_P_MOB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_plats.c
DEP_CPP_P_PLA=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_plats.obj" : $(SOURCE) $(DEP_CPP_P_PLA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_pspr.c
DEP_CPP_P_PSP=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_P_PSP=\
	".\multires.h"\
	

"$(INTDIR)\p_pspr.obj" : $(SOURCE) $(DEP_CPP_P_PSP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_saveg.c
DEP_CPP_P_SAV=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_saveg.obj" : $(SOURCE) $(DEP_CPP_P_SAV) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_setup.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_P_SET=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	
NODEP_CPP_P_SET=\
	".\multires.h"\
	

"$(INTDIR)\p_setup.obj" : $(SOURCE) $(DEP_CPP_P_SET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_P_SET=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_P_SET=\
	".\multires.h"\
	

"$(INTDIR)\p_setup.obj" : $(SOURCE) $(DEP_CPP_P_SET) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_sight.c
DEP_CPP_P_SIG=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_sight.obj" : $(SOURCE) $(DEP_CPP_P_SIG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_spec.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_P_SPE=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_P_SPE=\
	".\multires.h"\
	

"$(INTDIR)\p_spec.obj" : $(SOURCE) $(DEP_CPP_P_SPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_P_SPE=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_P_SPE=\
	".\multires.h"\
	

"$(INTDIR)\p_spec.obj" : $(SOURCE) $(DEP_CPP_P_SPE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_switch.c
DEP_CPP_P_SWI=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_P_SWI=\
	".\multires.h"\
	

"$(INTDIR)\p_switch.obj" : $(SOURCE) $(DEP_CPP_P_SWI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_telept.c
DEP_CPP_P_TEL=\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_telept.obj" : $(SOURCE) $(DEP_CPP_P_TEL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_tick.c
DEP_CPP_P_TIC=\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\p_tick.obj" : $(SOURCE) $(DEP_CPP_P_TIC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\p_user.c
DEP_CPP_P_USE=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_P_USE=\
	".\multires.h"\
	

"$(INTDIR)\p_user.obj" : $(SOURCE) $(DEP_CPP_P_USE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\r_bsp.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_R_BSP=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	

"$(INTDIR)\r_bsp.obj" : $(SOURCE) $(DEP_CPP_R_BSP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_R_BSP=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\r_bsp.obj" : $(SOURCE) $(DEP_CPP_R_BSP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\r_data.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_R_DAT=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_sky.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	
NODEP_CPP_R_DAT=\
	".\multires.h"\
	

"$(INTDIR)\r_data.obj" : $(SOURCE) $(DEP_CPP_R_DAT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_R_DAT=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_sky.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_R_DAT=\
	".\multires.h"\
	

"$(INTDIR)\r_data.obj" : $(SOURCE) $(DEP_CPP_R_DAT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\r_main.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_R_MAI=\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_sky.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	
NODEP_CPP_R_MAI=\
	".\multires.h"\
	

"$(INTDIR)\r_main.obj" : $(SOURCE) $(DEP_CPP_R_MAI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_R_MAI=\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_sky.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_R_MAI=\
	".\multires.h"\
	

"$(INTDIR)\r_main.obj" : $(SOURCE) $(DEP_CPP_R_MAI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\r_plane.c
DEP_CPP_R_PLA=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_sky.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_R_PLA=\
	".\multires.h"\
	

"$(INTDIR)\r_plane.obj" : $(SOURCE) $(DEP_CPP_R_PLA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\r_segs.c
DEP_CPP_R_SEG=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_draw.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_sky.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\r_segs.obj" : $(SOURCE) $(DEP_CPP_R_SEG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\r_sky.c
DEP_CPP_R_SKY=\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_sky.h"\
	".\r_state.h"\
	".\tables.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\r_sky.obj" : $(SOURCE) $(DEP_CPP_R_SKY) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\r_things.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_R_THI=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	
NODEP_CPP_R_THI=\
	".\multires.h"\
	

"$(INTDIR)\r_things.obj" : $(SOURCE) $(DEP_CPP_R_THI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_R_THI=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_R_THI=\
	".\multires.h"\
	

"$(INTDIR)\r_things.obj" : $(SOURCE) $(DEP_CPP_R_THI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\s_sound.c
DEP_CPP_S_SOU=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_sound.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_S_SOU=\
	".\multires.h"\
	

"$(INTDIR)\s_sound.obj" : $(SOURCE) $(DEP_CPP_S_SOU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\sounds.c
DEP_CPP_SOUND=\
	".\doomtype.h"\
	".\sounds.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\sounds.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\st_lib.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_ST_LI=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\st_lib.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	
NODEP_CPP_ST_LI=\
	".\multires.h"\
	

"$(INTDIR)\st_lib.obj" : $(SOURCE) $(DEP_CPP_ST_LI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_ST_LI=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\st_lib.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_ST_LI=\
	".\multires.h"\
	

"$(INTDIR)\st_lib.obj" : $(SOURCE) $(DEP_CPP_ST_LI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\st_stuff.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_ST_ST=\
	".\am_map.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_cheat.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_inter.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\st_lib.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	
NODEP_CPP_ST_ST=\
	".\multires.h"\
	

"$(INTDIR)\st_stuff.obj" : $(SOURCE) $(DEP_CPP_ST_ST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_ST_ST=\
	".\am_map.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\info.h"\
	".\m_cheat.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\p_inter.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\st_lib.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_ST_ST=\
	".\multires.h"\
	

"$(INTDIR)\st_stuff.obj" : $(SOURCE) $(DEP_CPP_ST_ST) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tables.c
DEP_CPP_TABLE=\
	".\m_fixed.h"\
	".\tables.h"\
	

"$(INTDIR)\tables.obj" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\w_wad.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_W_WAD=\
	".\d_event.h"\
	".\d_ticcmd.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\m_swap.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\unistd.h"\
	

"$(INTDIR)\w_wad.obj" : $(SOURCE) $(DEP_CPP_W_WAD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_W_WAD=\
	".\d_event.h"\
	".\d_ticcmd.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\m_swap.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\unistd.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\w_wad.obj" : $(SOURCE) $(DEP_CPP_W_WAD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wi_stuff.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_WI_ST=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\wi_stuff.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_WI_ST=\
	".\multires.h"\
	

"$(INTDIR)\wi_stuff.obj" : $(SOURCE) $(DEP_CPP_WI_ST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_WI_ST=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\g_game.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\m_random.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\s_sound.h"\
	".\sounds.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\wi_stuff.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_WI_ST=\
	".\multires.h"\
	

"$(INTDIR)\wi_stuff.obj" : $(SOURCE) $(DEP_CPP_WI_ST) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WINDOOM.c
DEP_CPP_WINDO=\
	".\d_console.h"\
	".\d_event.h"\
	".\d_items.h"\
	".\d_main.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dxerr.h"\
	".\g_game.h"\
	".\i_cd.h"\
	".\i_midi.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_argv.h"\
	".\m_fixed.h"\
	".\m_music.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\tables.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\WINDOOM.obj" : $(SOURCE) $(DEP_CPP_WINDO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\am_map.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_AM_MA=\
	".\am_map.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_cheat.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	
NODEP_CPP_AM_MA=\
	".\multires.h"\
	

"$(INTDIR)\am_map.obj" : $(SOURCE) $(DEP_CPP_AM_MA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_AM_MA=\
	".\am_map.h"\
	".\d_englsh.h"\
	".\d_event.h"\
	".\d_french.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\dstrings.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_cheat.h"\
	".\m_fixed.h"\
	".\p_local.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\p_spec.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\st_stuff.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_AM_MA=\
	".\multires.h"\
	

"$(INTDIR)\am_map.obj" : $(SOURCE) $(DEP_CPP_AM_MA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\z_zone.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_Z_ZON=\
	".\d_event.h"\
	".\d_ticcmd.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\z_zone.h"\
	

"$(INTDIR)\z_zone.obj" : $(SOURCE) $(DEP_CPP_Z_ZON) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_Z_ZON=\
	".\d_event.h"\
	".\d_ticcmd.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	

"$(INTDIR)\z_zone.obj" : $(SOURCE) $(DEP_CPP_Z_ZON) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\qmus2mid.c
DEP_CPP_QMUS2=\
	".\qmus2mid.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\qmus2mid.obj" : $(SOURCE) $(DEP_CPP_QMUS2) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\r_draw.c
DEP_CPP_R_DRA=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_net.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomstat.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_fixed.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\v_video.h"\
	".\w_wad.h"\
	".\z_zone.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_R_DRA=\
	".\multires.h"\
	

"$(INTDIR)\r_draw.obj" : $(SOURCE) $(DEP_CPP_R_DRA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\v_video.c

!IF  "$(CFG)" == "WinDoom - Win32 Release"

DEP_CPP_V_VID=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\v_video.h"\
	
NODEP_CPP_V_VID=\
	".\multires.h"\
	

"$(INTDIR)\v_video.obj" : $(SOURCE) $(DEP_CPP_V_VID) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WinDoom - Win32 Debug"

DEP_CPP_V_VID=\
	".\d_event.h"\
	".\d_items.h"\
	".\d_player.h"\
	".\d_think.h"\
	".\d_ticcmd.h"\
	".\doomdata.h"\
	".\doomdef.h"\
	".\doomtype.h"\
	".\i_system.h"\
	".\info.h"\
	".\m_bbox.h"\
	".\m_fixed.h"\
	".\m_swap.h"\
	".\p_mobj.h"\
	".\p_pspr.h"\
	".\r_bsp.h"\
	".\r_data.h"\
	".\r_defs.h"\
	".\r_local.h"\
	".\r_main.h"\
	".\r_plane.h"\
	".\r_segs.h"\
	".\r_state.h"\
	".\r_things.h"\
	".\tables.h"\
	".\v_video.h"\
	{$(INCLUDE)}"\values.h"\
	
NODEP_CPP_V_VID=\
	".\multires.h"\
	

"$(INTDIR)\v_video.obj" : $(SOURCE) $(DEP_CPP_V_VID) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
