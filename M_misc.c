// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
//
// $Log:$
//
// DESCRIPTION:
//	Main loop menu stuff.
//	Default Config File.
//	PCX Screenshots.
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: m_misc.c,v 1.6 1997/02/03 22:45:10 b1 Exp $";

//#include <sys/stat.h>
//#include <sys/types.h>
//#include <fcntl.h>
#include <stdlib.h>
//#include <io.h>
//#include <unistd.h>
//#include <direct.h>

#include <ctype.h>


#include "doomdef.h"

#include "z_zone.h"

#include "m_swap.h"
#include "m_argv.h"

#include "w_wad.h"

#include "i_system.h"
#include "i_video.h"
#include "v_video.h"

#include "hu_stuff.h"

// State.
#include "doomstat.h"

// Data.
#include "dstrings.h"

#include "m_misc.h"

//
// M_DrawText
// Returns the final X coordinate
// HU_Init must have been called to init the font
//
extern patch_t*		hu_font[HU_FONTSIZE];

int
M_DrawText
( int		x,
  int		y,
  boolean	direct,
  char*		string )
{
    int 	c;
    int		w;

    while (*string)
    {
	c = toupper(*string) - HU_FONTSTART;
	string++;
	if (c < 0 || c> HU_FONTSIZE)
	{
	    x += 4;
	    continue;
	}
		
	w = SHORT (hu_font[c]->width);
	if (x+w > SCREENWIDTH)
	    break;
	if (direct)
	    V_DrawPatch(x, y, 0, hu_font[c]);
	else
	    V_DrawPatch(x, y, 0, hu_font[c]);
	x+=w;
    }

    return x;
}



//
// M_GetFileSize
//
#ifndef O_BINARY
#define O_BINARY 0
#endif

int M_GetFileSize( char const*	name )
   {
    int		count;
	/*
    handle = open ( name, O_RDWR | O_BINARY);

    if (handle == -1)
        return 0;

    count = lseek(handle, 0, SEEK_END);
    close (handle);*/

    FILE* file = fopen( name, "rb" );
    fseek( file, 0, SEEK_END );
    count = ftell( file );
    fclose( file );
	
    return count;
   }

//
// M_WriteFile
//
boolean M_WriteFile(char const*	name,void* source,int length)
{
/*    int		handle;
    int		count;
	
    handle = open( name, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666);

    if (handle == -1)
	return false;

    count = write (handle, source, length);
    close (handle);
	
    if (count < length)
	return false;
		*/
    return true;
}

//
// M_AppendFile
//
boolean M_AppendFile(char const *name, void *source, int length )
   {
/*    int		handle;
    int		count;
	
    handle = open( name, O_RDWR | O_BINARY);

    if (handle == -1)
        return false;

    lseek(handle, 0L, SEEK_END);

    count = write (handle, source, length);
    close (handle);
	
    if (count < length)
        return false;
*/		
    return true;
   }


//
// M_ReadFile
//
int
M_ReadFile
( char const*	name,
  byte**	buffer )
{
    int	count, length;
    FILE* file;
    byte		*buf;
	
    file = fopen (name, "rb" );
    if (file == NULL)
	I_Error ("Couldn't read file %s", name);

    fseek( file, 0, SEEK_END );
    length = ftell( file );
    fseek( file, 0, SEEK_SET );

    buf = Z_Malloc (length, PU_STATIC, NULL);
    count = fread ( buf, 1, length, file);
    fclose (file);
	
    if (count < length)
	I_Error ("Couldn't read file %s", name);
		
    *buffer = buf;
    return length;
}


//
// DEFAULTS
//
int		usemouse;
int		usejoystick;

extern int	key_right;
extern int	key_left;
extern int	key_up;
extern int	key_down;

extern int	key_strafeleft;
extern int	key_straferight;

extern int	key_fire;
extern int	key_use;
extern int	key_strafe;
extern int	key_speed;
extern int  key_nextweapon;
extern int  key_prevweapon;

extern int  key_mvert;

extern int  always_run;
extern int  swap_stereo;
extern int  mvert;
extern int  keylink;

extern int	mousebfire;
extern int	mousebstrafe;
extern int	mousebforward;

extern int joybup;
extern int joybdown;
extern int joybleft;
extern int joybright;
extern int joybfire; 
extern int joybstrafe; 
extern int joybuse; 
extern int joybspeed;
extern int joybstrafeleft;
extern int joybstraferight;
extern int joybnextweapon;
extern int joybprevweapon;
extern int joybmenu;
extern int joybmenuselect;
extern int joybmenucancel;

extern int	viewwidth;
extern int	viewheight;

extern int	mouseSensitivity;
extern int	showMessages;

extern int	detailLevel;

extern int	screenblocks;

extern int	showMessages;

// machine-independent sound params
extern	int	numChannels;


// UNIX hack, to be removed.
#ifdef SNDSERV
extern char*	sndserver_filename;
extern int	mb_used;
#endif

#ifdef LINUX
char*		mousetype;
char*		mousedev;
#endif

extern char*	chat_macros[];



typedef struct
{
    char*	name;
    int*	location;
    int		defaultvalue;
    int		scantranslate;		// PC scan code hack
    int		untranslated;		// lousy hack
} default_t;

default_t	defaults[] =
{
    {"mouse_sensitivity",&mouseSensitivity, 5},
    {"sfx_volume",&snd_SfxVolume, 8},
    {"music_volume",&snd_MusicVolume, 8},
    {"show_messages",&showMessages, 1},
    

#ifdef NORMALUNIX
    {"key_right",&key_right, KEY_RIGHTARROW},
    {"key_left",&key_left, KEY_LEFTARROW},
    {"key_up",&key_up, KEY_UPARROW},
    {"key_down",&key_down, KEY_DOWNARROW},
    {"key_strafeleft",&key_strafeleft, ','},
    {"key_straferight",&key_straferight, '.'},

    {"key_fire",&key_fire, KEY_RCTRL},
    {"key_use",&key_use, ' '},
    {"key_strafe",&key_strafe, KEY_RALT},
    {"key_speed",&key_speed, KEY_RSHIFT},
    {"key_nextweapon",&key_nextweapon, KEY_NEXT},

// UNIX hack, to be removed. 
#ifdef SNDSERV
    {"sndserver", (int *) &sndserver_filename, (int) "sndserver"},
    {"mb_used", &mb_used, 2},
#endif
    
#endif

#ifdef LINUX
    {"mousedev", (int*)&mousedev, (int)"/dev/ttyS0"},
    {"mousetype", (int*)&mousetype, (int)"microsoft"},
#endif

    {"use_mouse",&usemouse, 1},
    {"mouseb_fire",&mousebfire,0},
    {"mouseb_strafe",&mousebstrafe,1},
    {"mouseb_forward",&mousebforward,2},

    {"use_joystick",&usejoystick, 0},
    {"joyb_fire",&joybfire,0},
    {"joyb_strafe",&joybstrafe,1},
    {"joyb_use",&joybuse,3},
    {"joyb_speed",&joybspeed,2},

    {"screenblocks",&screenblocks, 9},
    {"detaillevel",&detailLevel, 0},

    {"snd_channels",&numChannels, 3},



    {"usegamma",&usegamma, 0},

    {"chatmacro0", (int *) &chat_macros[0], (int) HUSTR_CHATMACRO0 },
    {"chatmacro1", (int *) &chat_macros[1], (int) HUSTR_CHATMACRO1 },
    {"chatmacro2", (int *) &chat_macros[2], (int) HUSTR_CHATMACRO2 },
    {"chatmacro3", (int *) &chat_macros[3], (int) HUSTR_CHATMACRO3 },
    {"chatmacro4", (int *) &chat_macros[4], (int) HUSTR_CHATMACRO4 },
    {"chatmacro5", (int *) &chat_macros[5], (int) HUSTR_CHATMACRO5 },
    {"chatmacro6", (int *) &chat_macros[6], (int) HUSTR_CHATMACRO6 },
    {"chatmacro7", (int *) &chat_macros[7], (int) HUSTR_CHATMACRO7 },
    {"chatmacro8", (int *) &chat_macros[8], (int) HUSTR_CHATMACRO8 },
    {"chatmacro9", (int *) &chat_macros[9], (int) HUSTR_CHATMACRO9 }

};

int	numdefaults;
char*	defaultfile;

char DoomDir[128], szValue[32];
void GetININame(void);



typedef struct tagdoomconfig {
    unsigned char mouseSensitivity;
    unsigned char snd_SfxVolume;
    unsigned char snd_MusicVolume;
    unsigned char showMessages;
    unsigned char key_right;
    unsigned char key_left;
    unsigned char key_up;
    unsigned char key_down;
    unsigned char key_strafeleft;
    unsigned char key_straferight;
    unsigned char key_fire;
    unsigned char key_use;
    unsigned char key_strafe;
    unsigned char key_speed;
    unsigned char key_nextweapon;
    unsigned char key_prevweapon;
    unsigned char always_run;
    unsigned char key_mvert;
    unsigned char mvert;
    unsigned char mousebfire;
    unsigned char mousebstrafe;
    unsigned char mousebforward;
    signed char joybup;
    signed char joybdown;
    signed char joybleft;
    signed char joybright;
    signed char joybfire;
    signed char joybuse;
    signed char joybspeed;
    signed char joybstrafeleft;
    signed char joybstraferight;
    signed char joybnextweapon;
    signed char joybstrafe;
    signed char joybprevweapon;
    unsigned char screenblocks;
    unsigned char usegamma;
} doomconfig;



//
// M_SaveDefaults
//
void M_SaveDefaults (void)
{
    doomconfig cfg;

    //package configuration
    cfg.mouseSensitivity = mouseSensitivity;
    cfg.snd_SfxVolume = snd_SfxVolume;
    cfg.snd_MusicVolume = snd_MusicVolume;
    cfg.showMessages = showMessages;
    cfg.key_right = key_right;
    cfg.key_left = key_left;
    cfg.key_up = key_up;
    cfg.key_down = key_down;
    cfg.key_strafeleft = key_strafeleft;
    cfg.key_straferight = key_straferight;
    cfg.key_fire = key_fire;
    cfg.key_use = key_use;
    cfg.key_strafe = key_strafe;
    cfg.key_speed = key_speed;
    cfg.key_nextweapon = key_nextweapon;
    cfg.key_prevweapon = key_prevweapon;
    cfg.always_run = always_run;
    cfg.key_mvert = key_mvert;
    cfg.mvert = mvert;
    cfg.mousebfire = mousebfire;
    cfg.mousebstrafe = mousebstrafe;
    cfg.mousebforward = mousebforward;
    cfg.joybup = joybup;
    cfg.joybdown = joybdown;
    cfg.joybleft = joybleft;
    cfg.joybright = joybright;
    cfg.joybfire = joybfire;
    cfg.joybuse = joybuse;
    cfg.joybspeed = joybspeed;
    cfg.joybstrafeleft = joybstrafeleft;
    cfg.joybstraferight = joybstraferight;
    cfg.joybnextweapon = joybnextweapon;
    cfg.joybstrafe = joybstrafe;
    cfg.joybprevweapon = joybprevweapon;
    cfg.screenblocks = screenblocks;
    cfg.usegamma = usegamma;

    //write to flash
    Flash_WriteFile( "doom.cfg", &cfg, sizeof(cfg), "Doom config" );
}


//
// M_LoadDefaults
//
extern byte	scantokey[128];

void WriteDebug(char *);
char MsgText[256];

void M_LoadDefaults (void)
{
    doomconfig cfg;
    void* pBuf;
    int nSize;

    //set defaults
    cfg.mouseSensitivity = 5;
    cfg.snd_SfxVolume = 15;
    cfg.snd_MusicVolume = 8;
    cfg.showMessages = 1;

    cfg.key_right = KEY_RIGHTARROW;
    cfg.key_left = KEY_LEFTARROW;
    cfg.key_up = KEY_UPARROW;
    cfg.key_down = KEY_DOWNARROW;

    cfg.key_strafeleft = KEY_COMMA;
    cfg.key_straferight = KEY_PERIOD;

    cfg.key_fire = KEY_RCTRL;
    cfg.key_use = KEY_SPACE;
    cfg.key_strafe = KEY_RALT;
    cfg.key_speed = KEY_RSHIFT;
    cfg.key_nextweapon = KEY_RBRACKET;
    cfg.key_prevweapon = KEY_LBRACKET;

    cfg.key_mvert = KEY_SLASH;
    cfg.mvert = 1;

    cfg.always_run = FALSE;

    cfg.mousebfire = 0;
    cfg.mousebstrafe = 1;
    cfg.mousebforward = 2;

    cfg.joybup =                    3;
    cfg.joybdown =                  4;
    cfg.joybleft =                  5;
    cfg.joybright =                 6;
    cfg.joybfire =                  1;               //a
    cfg.joybuse =                   0;                //b
    cfg.joybspeed =                 8;              //x
    cfg.joybstrafeleft =            10;         //rt
    cfg.joybstraferight =           9;       //lt
    cfg.joybnextweapon =            7;         //y
    cfg.joybstrafe =                -1; //12
    cfg.joybprevweapon =            -1;//11;

    cfg.screenblocks =  10;
    cfg.usegamma = 1;

    numChannels = 256;


    //read from flash
    nSize = Flash_ReadFile( "doom.cfg", &pBuf );
    if( nSize == sizeof(doomconfig) && pBuf )
    {
        memcpy( &cfg, pBuf, sizeof(doomconfig) );
        Z_Free( pBuf );
    }


    //unpackage
    mouseSensitivity = cfg.mouseSensitivity;
    snd_SfxVolume = cfg.snd_SfxVolume;
    snd_MusicVolume = cfg.snd_MusicVolume;
    showMessages = cfg.showMessages;
    key_right = cfg.key_right;
    key_left = cfg.key_left;
    key_up = cfg.key_up;
    key_down = cfg.key_down;
    key_strafeleft = cfg.key_strafeleft;
    key_straferight = cfg.key_straferight;
    key_fire = cfg.key_fire;
    key_use = cfg.key_use;
    key_strafe = cfg.key_strafe;
    key_speed = cfg.key_speed;
    key_nextweapon = cfg.key_nextweapon;
    key_prevweapon = cfg.key_prevweapon;
    key_mvert = cfg.key_mvert;
    always_run = cfg.always_run;
    mvert = cfg.mvert;
    mousebfire = cfg.mousebfire;
    mousebstrafe = cfg.mousebstrafe;
    mousebforward = cfg.mousebforward;
    joybup = cfg.joybup;
    joybdown = cfg.joybdown;
    joybleft = cfg.joybleft;
    joybright = cfg.joybright;
    joybfire = cfg.joybfire;
    joybuse = cfg.joybuse;
    joybspeed = cfg.joybspeed;
    joybstrafeleft = cfg.joybstrafeleft;
    joybstraferight = cfg.joybstraferight;
    joybnextweapon = cfg.joybnextweapon;
    joybstrafe = cfg.joybstrafe;
    joybprevweapon = cfg.joybprevweapon;
    screenblocks = cfg.screenblocks;
    usegamma = cfg.usegamma;





    usejoystick = 1;
    usemouse = 1;
    swap_stereo = 0;
    keylink = TRUE;

}
/*
snd_musicdevice		3
snd_sfxdevice		3
snd_sbport		544
snd_sbirq		5
snd_sbdma		1
snd_mport		816

chatmacro0		"no macro"
chatmacro1		"no macro"
chatmacro2		"no macro"
chatmacro3		"no macro"
chatmacro4		"no macro"
chatmacro5		"no macro"
chatmacro6		"no macro"
chatmacro7		"no macro"
chatmacro8		"no macro"
chatmacro9		"no macro"
*/

//
// SCREEN SHOTS
//


typedef struct
{
    char		manufacturer;
    char		version;
    char		encoding;
    char		bits_per_pixel;

    unsigned short	xmin;
    unsigned short	ymin;
    unsigned short	xmax;
    unsigned short	ymax;
    
    unsigned short	hres;
    unsigned short	vres;

    unsigned char	palette[48];
    
    char		reserved;
    char		color_planes;
    unsigned short	bytes_per_line;
    unsigned short	palette_type;
    
    char		filler[58];
    unsigned char	data;		// unbounded
} pcx_t;


//
// WritePCXfile
//
void
WritePCXfile
( char*		filename,
  byte*		data,
  int		width,
  int		height,
  byte*		palette )
{
    int		i;
    int		length;
    pcx_t*	pcx;
    byte*	pack;
	
    pcx = Z_Malloc (width*height*2+1000, PU_STATIC, NULL);

    pcx->manufacturer = 0x0a;		// PCX id
    pcx->version = 5;			// 256 color
    pcx->encoding = 1;			// uncompressed
    pcx->bits_per_pixel = 8;		// 256 color
    pcx->xmin = 0;
    pcx->ymin = 0;
    pcx->xmax = SHORT(width-1);
    pcx->ymax = SHORT(height-1);
    pcx->hres = SHORT(width);
    pcx->vres = SHORT(height);
    memset (pcx->palette,0,sizeof(pcx->palette));
    pcx->color_planes = 1;		// chunky image
    pcx->bytes_per_line = SHORT(width);
    pcx->palette_type = SHORT(2);	// not a grey scale
    memset (pcx->filler,0,sizeof(pcx->filler));


    // pack the image
    pack = &pcx->data;
	
    for (i=0 ; i<width*height ; i++)
    {
	if ( (*data & 0xc0) != 0xc0)
	    *pack++ = *data++;
	else
	{
	    *pack++ = 0xc1;
	    *pack++ = *data++;
	}
    }
    
    // write the palette
    *pack++ = 0x0c;	// palette ID byte
    for (i=0 ; i<768 ; i++)
	*pack++ = gammatable[usegamma][*palette++];
    
    // write output file
    length = pack - (byte *)pcx;
    M_WriteFile (filename, pcx, length);

    Z_Free (pcx);
}


//
// M_ScreenShot
//
void M_ScreenShot (void)
{
    /*
    int		i;
    byte*	linear;
    char	lbmname[12];
    
    // munge planar buffer to linear
    linear = screens[2];
    I_ReadScreen (linear);
    
    // find a file name to save it to
    strcpy(lbmname,"DOOM00.pcx");
		
    for (i=0 ; i<=99 ; i++)
    {
	lbmname[4] = i/10 + '0';
	lbmname[5] = i%10 + '0';
	if (access(lbmname,0) == -1)
	    break;	// file doesn't exist
    }
    if (i==100)
	I_Error ("M_ScreenShot: Couldn't create a PCX");
    
    // save the pcx file
    WritePCXfile (lbmname, linear,
		  SCREENWIDTH, SCREENHEIGHT,
		  W_CacheLumpName ("PLAYPAL",PU_CACHE));
	
    players[consoleplayer].message = "screen shot";
    */
}


