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
// DESCRIPTION:
//  Internally used data structures for virtually everything,
//   key definitions, lots of other stuff.
//
//-----------------------------------------------------------------------------

#ifndef __DOOMDEF__
#define __DOOMDEF__

#include <stdio.h>
#include <string.h>

//
// Global parameters/defines.
//
// DOOM version
enum { VERSION =  109 };


// Game mode handling - identify IWAD version
//  to handle IWAD dependend animations etc.
typedef enum
{
  shareware,	// DOOM 1 shareware, E1, M9
  registered,	// DOOM 1 registered, E3, M27
  commercial,	// DOOM 2 retail, E1 M34
  // DOOM 2 german edition not handled
  retail,	// DOOM 1 retail, E4, M36
  addon_tnt,    // DOOM 2 TNT
  addon_plut,   // DOOM 2 Plutonia
  indetermined	// Well, no IWAD found.
  
} GameMode_t;


// Mission packs - might be useful for TC stuff?
typedef enum
{
  doom,		// DOOM 1
  doom2,	// DOOM 2
  pack_tnt,	// TNT mission pack
  pack_plut,	// Plutonia pack
  none

} GameMission_t;


// Identify language to use, software localization.
typedef enum
{
  english,
  french,
  german,
  unknown

} Language_t;


// If rangecheck is undefined,
// most parameter validation debugging code will not be compiled
//#define RANGECHECK

// Do or do not use external soundserver.
// The sndserver binary to be run separately
//  has been introduced by Dave Taylor.
// The integrated sound support is experimental,
//  and unfinished. Default is synchronous.
// Experimental asynchronous timer based is
//  handled by SNDINTR. 
#define SNDSERV  1
//#define SNDINTR  1


// This one switches between MIT SHM (no proper mouse)
// and XFree86 DGA (mickey sampling). The original
// linuxdoom used SHM, which is default.
//#define X11_DGA		1


//
// For resize of screen, at start of game.
// It will not work dynamically, see visplanes.
//
#define	BASE_WIDTH		320

// It is educational but futile to change this
//  scaling e.g. to 2. Drawing of status bar,
//  menues etc. is tied to the scale implied
//  by the graphics.
#define	SCREEN_MUL		1
#define	INV_ASPECT_RATIO	0.625 // 0.75, ideally

// Defines suck. C sucks.
// C++ might sucks for OOP, but it sure is a better C.
// So there.
//#define SCREENWIDTH  640
extern int SCREENWIDTH;
//SCREEN_MUL*BASE_WIDTH //320
//#define SCREENHEIGHT 480
extern int SCREENHEIGHT;
//(int)(SCREEN_MUL*BASE_WIDTH*INV_ASPECT_RATIO) //200


// The maximum number of players, multiplayer/networking.
#define MAXPLAYERS		4

// State updates, number of tics / second.
#define TICRATE		35

// The current state of the game: whether we are
// playing, gazing at the intermission screen,
// the game final animation, or a demo. 
typedef enum
{
    GS_LEVEL,
    GS_INTERMISSION,
    GS_FINALE,
    GS_DEMOSCREEN
} gamestate_t;

//
// Difficulty/skill settings/filters.
//

// Skill flags.
#define	MTF_EASY		1
#define	MTF_NORMAL		2
#define	MTF_HARD		4

// Deaf monsters/do not react to sound.
#define	MTF_AMBUSH		8

typedef enum
{
    sk_baby,
    sk_easy,
    sk_medium,
    sk_hard,
    sk_nightmare
} skill_t;




//
// Key cards.
//
typedef enum
{
    it_bluecard,
    it_yellowcard,
    it_redcard,
    it_blueskull,
    it_yellowskull,
    it_redskull,
    
    NUMCARDS
    
} card_t;



// The defined weapons,
//  including a marker indicating
//  user has not changed weapon.
typedef enum
{
    wp_fist,                //0     0000
    wp_pistol,              //1     0001
    wp_shotgun,             //2     0010
    wp_chaingun,            //3     0011
    wp_missile,             //4     0100
    wp_plasma,              //5     0101
    wp_bfg,                 //6     0110
    wp_chainsaw,            //7     0111
    wp_supershotgun,        //8     1000

    NUMWEAPONS,             //9     1001

    wp_next,                //10    1010
    wp_prev,                //11    1011
    
    // No pending weapon change.
    wp_nochange             //12    1100

} weapontype_t;


// Ammunition types defined.
typedef enum
{
    am_clip,	// Pistol / chaingun ammo.
    am_shell,	// Shotgun / double barreled shotgun.
    am_cell,	// Plasma rifle, BFG.
    am_misl,	// Missile launcher.
    NUMAMMO,
    am_noammo	// Unlimited for chainsaw / fist.	

} ammotype_t;


// Power up artifacts.
typedef enum
{
    pw_invulnerability,
    pw_strength,
    pw_invisibility,
    pw_ironfeet,
    pw_allmap,
    pw_infrared,
    NUMPOWERS
    
} powertype_t;



//
// Power up durations,
//  how many seconds till expiration,
//  assuming TICRATE is 35 ticks/second.
//
typedef enum
{
    INVULNTICS	= (30*TICRATE),
    INVISTICS	= (60*TICRATE),
    INFRATICS	= (120*TICRATE),
    IRONTICS	= (60*TICRATE)
    
} powerduration_t;




//
// DOOM keyboard definition.
// This is the stuff configured by Setup.Exe.
// Most key data are simple ascii (uppercased).
//
//#define KEY_RIGHTARROW	  0xae
//#define KEY_LEFTARROW	  0xac
//#define KEY_UPARROW	      0xad
//#define KEY_DOWNARROW	  0xaf
//#define KEY_ESCAPE	27
//#define KEY_ENTER	13
//#define KEY_TAB		9

//#define KEY_F1		(0x80+0x3b)
//#define KEY_F2		(0x80+0x3c)
//#define KEY_F3		(0x80+0x3d)
//#define KEY_F4		(0x80+0x3e)
//#define KEY_F5		(0x80+0x3f)
//#define KEY_F6		(0x80+0x40)
//#define KEY_F7		(0x80+0x41)
//#define KEY_F8		(0x80+0x42)
//#define KEY_F9		(0x80+0x43)
//#define KEY_F10		(0x80+0x44)
//#define KEY_F11		(0x80+0x57)
//#define KEY_F12		(0x80+0x58)

//#define KEY_BACKSPACE	       127
#define KEY_PAUSE	0xff

//#define KEY_EQUALS	0x3d
//#define KEY_MINUS	0x2d

#define KEY_CAPITAL 0x3a

//#define KEY_RSHIFT	(0x80+0x36)
//#define KEY_RCTRL	(0x80+0x1d)
//#define KEY_RALT	(0x80+0x38)
//#define KEY_LALT	KEY_RALT


//#define KEY_CONSOLE '`'
#define KEY_SCRNSHOT (0xB7)

#define KEY_F1            0x3B
#define KEY_F2            0x3C
#define KEY_F3            0x3D
#define KEY_F4            0x3E
#define KEY_F5            0x3F
#define KEY_F6            0x40
#define KEY_F7            0x41
#define KEY_F8            0x42
#define KEY_F9            0x43
#define KEY_F10           0x44
#define KEY_F11           0x57
#define KEY_F12           0x58

#define KEY_A               0x1E
#define KEY_B               0x30
#define KEY_C               0x2E
#define KEY_D               0x20
#define KEY_E               0x12
#define KEY_F               0x21
#define KEY_G               0x22
#define KEY_I               0x17
#define KEY_H               0x23
#define KEY_J               0x24
#define KEY_K               0x25
#define KEY_L               0x26
#define KEY_M               0x32
#define KEY_N               0x31
#define KEY_O               0x18
#define KEY_P               0x19
#define KEY_Q               0x10
#define KEY_R               0x13
#define KEY_S               0x1F
#define KEY_T               0x14
#define KEY_U               0x16
#define KEY_V               0x2F
#define KEY_W               0x11
#define KEY_X               0x2D
#define KEY_Y               0x15
#define KEY_Z               0x2C

#define KEY_1               0x02
#define KEY_2               0x03
#define KEY_3               0x04
#define KEY_4               0x05
#define KEY_5               0x06
#define KEY_6               0x07
#define KEY_7               0x08
#define KEY_8               0x09
#define KEY_9               0x0A
#define KEY_0               0x0B

#define KEY_MINUS           0x0C    // - on main keyboard
#define KEY_EQUALS          0x0D

#define KEY_BACKSPACE       0x0E    // backspace
#define KEY_ESCAPE	      0x01
#define KEY_ENTER	      0x1C
#define KEY_CONSOLE       0x29

#define KEY_RIGHTARROW	  0xCD
#define KEY_LEFTARROW	  0xCB
#define KEY_UPARROW	      0xC8
#define KEY_DOWNARROW	  0xD0

#define KEY_SPACE           0x39
#define KEY_TAB		        0x0F
#define KEY_RSHIFT          0x36
#define KEY_RCTRL           0x9D
#define KEY_RALT            0xB8    // right Alt
#define KEY_LALT	        KEY_RALT

#define KEY_COMMA           0x33
#define KEY_PERIOD          0x34    // . on main keyboard
#define KEY_SLASH           0x35    // / on main keyboard
// new keys not part of DOOM...

#define KEY_LBRACKET        0x1A
#define KEY_RBRACKET        0x1B
#define KEY_SEMICOLON       0x27
#define KEY_APOSTROPHE      0x28
#define KEY_DIVIDE          0xB5    // / on numeric keypad
#define KEY_MULTIPLY        0x37    // * on numeric keypad
#define KEY_NUMLOCK         0x45
#define KEY_SCROLL          0x46    // Scroll Lock
#define KEY_NUMPAD7         0x47
#define KEY_NUMPAD8         0x48
#define KEY_NUMPAD9         0x49
#define KEY_SUBTRACT        0x4A    // - on numeric keypad
#define KEY_NUMPAD4         0x4B
#define KEY_NUMPAD5         0x4C
#define KEY_NUMPAD6         0x4D
#define KEY_ADD             0x4E    // + on numeric keypad
#define KEY_NUMPAD1         0x4F
#define KEY_NUMPAD2         0x50
#define KEY_NUMPAD3         0x51
#define KEY_NUMPAD0         0x52
#define KEY_DECIMAL         0x53    // . on numeric keypad

#define KEY_HOME            0xC7    // Home on arrow keypad
#define KEY_UP              0xC8    // UpArrow on arrow keypad
#define KEY_PRIOR           0xC9    // PgUp on arrow keypad
#define KEY_LEFT            0xCB    // LeftArrow on arrow keypad
#define KEY_RIGHT           0xCD    // RightArrow on arrow keypad
#define KEY_END             0xCF    // End on arrow keypad
#define KEY_DOWN            0xD0    // DownArrow on arrow keypad
#define KEY_NEXT            0xD1    // PgDn on arrow keypad
#define KEY_INSERT          0xD2    // Insert on arrow keypad
#define KEY_DELETE          0xD3    // Delete on arrow keypad

extern unsigned char scan2char[256];

extern long	totalscore;			// 10.15.98 scorekeeping dlw (2billion?)
extern char totalscoretextline[200];
extern char HUDscoretext[200];
extern char scoreuserwad[256];
extern char keepscore;
extern char showscoreHUD;
extern char	DOUBLESTUFF;	//11.4.98 optimize dlw
extern long	SCREENMULT;		//11.5.98 optimize dlw width x height



/*

#define DIK_ESCAPE          0x01
#define DIK_1               0x02
#define DIK_2               0x03
#define DIK_3               0x04
#define DIK_4               0x05
#define DIK_5               0x06
#define DIK_6               0x07
#define DIK_7               0x08
#define DIK_8               0x09
#define DIK_9               0x0A
#define DIK_0               0x0B
#define DIK_MINUS           0x0C    // - on main keyboard
#define DIK_EQUALS          0x0D
#define DIK_BACK            0x0E    // backspace
#define DIK_TAB             0x0F
#define DIK_Q               0x10
#define DIK_W               0x11
#define DIK_E               0x12
#define DIK_R               0x13
#define DIK_T               0x14
#define DIK_Y               0x15
#define DIK_U               0x16
#define DIK_I               0x17
#define DIK_O               0x18
#define DIK_P               0x19
#define DIK_LBRACKET        0x1A
#define DIK_RBRACKET        0x1B
#define DIK_RETURN          0x1C    // Enter on main keyboard
#define DIK_LCONTROL        0x1D
#define DIK_A               0x1E
#define DIK_S               0x1F
#define DIK_D               0x20
#define DIK_F               0x21
#define DIK_G               0x22
#define DIK_H               0x23
#define DIK_J               0x24
#define DIK_K               0x25
#define DIK_L               0x26
#define DIK_SEMICOLON       0x27
#define DIK_APOSTROPHE      0x28
#define DIK_GRAVE           0x29    // accent grave
#define DIK_LSHIFT          0x2A
#define DIK_BACKSLASH       0x2B
#define DIK_Z               0x2C
#define DIK_X               0x2D
#define DIK_C               0x2E
#define DIK_V               0x2F
#define DIK_B               0x30
#define DIK_N               0x31
#define DIK_M               0x32
#define DIK_COMMA           0x33
#define DIK_PERIOD          0x34    // . on main keyboard
#define DIK_SLASH           0x35    // / on main keyboard
#define DIK_RSHIFT          0x36
#define DIK_MULTIPLY        0x37    // * on numeric keypad
#define DIK_LMENU           0x38    // left Alt
#define DIK_SPACE           0x39
#define DIK_CAPITAL         0x3A
#define DIK_F1              0x3B
#define DIK_F2              0x3C
#define DIK_F3              0x3D
#define DIK_F4              0x3E
#define DIK_F5              0x3F
#define DIK_F6              0x40
#define DIK_F7              0x41
#define DIK_F8              0x42
#define DIK_F9              0x43
#define DIK_F10             0x44
#define DIK_NUMLOCK         0x45
#define DIK_SCROLL          0x46    // Scroll Lock
#define DIK_NUMPAD7         0x47
#define DIK_NUMPAD8         0x48
#define DIK_NUMPAD9         0x49
#define DIK_SUBTRACT        0x4A    // - on numeric keypad
#define DIK_NUMPAD4         0x4B
#define DIK_NUMPAD5         0x4C
#define DIK_NUMPAD6         0x4D
#define DIK_ADD             0x4E    // + on numeric keypad
#define DIK_NUMPAD1         0x4F
#define DIK_NUMPAD2         0x50
#define DIK_NUMPAD3         0x51
#define DIK_NUMPAD0         0x52
#define DIK_DECIMAL         0x53    // . on numeric keypad
#define DIK_F11             0x57
#define DIK_F12             0x58

#define DIK_NUMPADENTER     0x9C    // Enter on numeric keypad
#define DIK_RCONTROL        0x9D
#define DIK_NUMPADCOMMA     0xB3    // , on numeric keypad (NEC PC98)
#define DIK_DIVIDE          0xB5    // / on numeric keypad
#define DIK_SYSRQ           0xB7
#define DIK_RMENU           0xB8    // right Alt
#define DIK_HOME            0xC7    // Home on arrow keypad
#define DIK_UP              0xC8    // UpArrow on arrow keypad
#define DIK_PRIOR           0xC9    // PgUp on arrow keypad
#define DIK_LEFT            0xCB    // LeftArrow on arrow keypad
#define DIK_RIGHT           0xCD    // RightArrow on arrow keypad
#define DIK_END             0xCF    // End on arrow keypad
#define DIK_DOWN            0xD0    // DownArrow on arrow keypad
#define DIK_NEXT            0xD1    // PgDn on arrow keypad
#define DIK_INSERT          0xD2    // Insert on arrow keypad
#define DIK_DELETE          0xD3    // Delete on arrow keypad
#define DIK_LWIN            0xDB    // Left Windows key
#define DIK_RWIN            0xDC    // Right Windows key
#define DIK_APPS            0xDD    // AppMenu key

#define DIK_BACKSPACE       DIK_BACK            // backspace
#define DIK_NUMPADSTAR      DIK_MULTIPLY        // * on numeric keypad
#define DIK_LALT            DIK_LMENU           // left Alt
#define DIK_CAPSLOCK        DIK_CAPITAL         // CapsLock
#define DIK_NUMPADMINUS     DIK_SUBTRACT        // - on numeric keypad
#define DIK_NUMPADPLUS      DIK_ADD             // + on numeric keypad
#define DIK_NUMPADPERIOD    DIK_DECIMAL         // . on numeric keypad
#define DIK_NUMPADSLASH     DIK_DIVIDE          // / on numeric keypad
#define DIK_RALT            DIK_RMENU           // right Alt
#define DIK_UPARROW         DIK_UP              // UpArrow on arrow keypad
#define DIK_PGUP            DIK_PRIOR           // PgUp on arrow keypad
#define DIK_LEFTARROW       DIK_LEFT            // LeftArrow on arrow keypad
#define DIK_RIGHTARROW      DIK_RIGHT           // RightArrow on arrow keypad
#define DIK_DOWNARROW       DIK_DOWN            // DownArrow on arrow keypad
#define DIK_PGDN            DIK_NEXT            // PgDn on arrow keypad

*/



// DOOM basic types (boolean),
//  and max/min values.
//#include "doomtype.h"

// Fixed point.
//#include "m_fixed.h"

// Endianess handling.
//#include "m_swap.h"


// Binary Angles, sine/cosine/atan lookups.
//#include "tables.h"

// Event type.
//#include "d_event.h"

// Game function, skills.
//#include "g_game.h"

// All external data is defined here.
//#include "doomdata.h"

// All important printed strings.
// Language selection (message strings).
//#include "dstrings.h"

// Player is a special actor.
//struct player_s;


//#include "d_items.h"
//#include "d_player.h"
//#include "p_mobj.h"
//#include "d_net.h"

// PLAY
//#include "p_tick.h"




// Header, generated by sound utility.
// The utility was written by Dave Taylor.
//#include "sounds.h"




#endif          // __DOOMDEF__
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
