//
// d_console.c
//
// This is the console control program it is NOT covered
// by the Doom license agreement.
//
// Copyright © 1998, Bruce A. Lewis
// This code may not be re-used in a commercial product
// of any kind without express written consent from
// the author, Bruce A. Lewis.
//
#include <windows.h>
#include <ctype.h>
////////////////////////////////////////////////////////////////////////
// Doom defines and external data
////////////////////////////////////////////////////////////////////////
#include "doomdef.h"
#include "doomstat.h"
#include "d_event.h"
#include "d_englsh.h"
#include "g_game.h"
#include "hu_stuff.h"
#include "i_system.h"
#include "m_cheat.h"
#include "p_inter.h"
#include "s_sound.h"
#include "sounds.h"
#include "r_defs.h"
#include "v_video.h"
#include "w_wad.h"
#include "z_zone.h"



#define ST_MSGWIDTH			52
#define CMDLENGTH         1024

extern byte *screens[5];
extern patch_t*		hu_font[HU_FONTSIZE];

extern cheatseq_t	cheat_mus;
extern cheatseq_t	cheat_god;
extern cheatseq_t	cheat_ammo;
extern cheatseq_t	cheat_ammonokey;
extern cheatseq_t	cheat_noclip;
extern cheatseq_t	cheat_commercial_noclip;

extern cheatseq_t	cheat_powerup[7];

extern cheatseq_t	cheat_choppers;
extern cheatseq_t	cheat_clev;
extern cheatseq_t	cheat_mypos;


void M_WriteText(int x, int y, char *string);

////////////////////////////////////////////////////////////////////////
// Doom98 code
////////////////////////////////////////////////////////////////////////

//#include "m_music.h"

void WriteDebug(char *);
char MsgText[256];

#define CONSOLE_NAME "M_DOOM"
#define CONSOLE_FLAT "CEIL5_1"
#define CONSOLE_BORD "FLAT18"
#define CONSBORD     2
//#define CONSVERS     96   <<--windoom last version
//097 was 10/31 release
//100 also 10/31 (savegame)
//101 11/8/98 (optimized, cleaner, less bugs)
#define CONSVERS 111
#define CONSMSGS     64

char szProgName[] = "WINDOOM"; //B.Lewis original
// char szProgName[] = "DOOM4WIN";		renamed 5.17.99
char szVersion[8];

typedef enum { asleep, sleepy, waking, awake } consolemode;

int iConsoleSpeed = 15;
int iConsoleHeight = 0;
int iConsoleMax;
int iConsoleMode = asleep;
int iFontHigh;
int iNamePosX, iVerPosX;
int iConsHead = 0, iConsTail = 0;

// Console background;
byte                  consback[64*64];
byte                  consbord[64*64];
byte                 *pconstex;
static patch_t       *consname;

static player_t      *plyr; 

static unsigned char  consmsgs[CONSMSGS][132];
static unsigned char  szCommand[1028];
int                   iCCursor = 0;

BOOL bConsoleActive = FALSE;

int CO_StringWidth(char *s);
int CO_StringPrintable(char *s);
int CO_WriteConsoleLine(int i, char *s, BOOL wrap);
void CO_AddConsoleMessage(char *s);
int CO_HandleCommand(char *cmd);
BOOL isdigits(char *s);

void R_DrawViewBorder(void);

char *PowerUpOn[] = { "INVULNERABILITY ON", "BERSERKER ON", "INVISIBILITY ON", "ENVIRONMENT SUIT ON", "FULL MAP ON", "LIGHT AMPLIFICATION GOGGLES ON" };
char *PowerUpOff[] = { "INVULNERABILITY OFF", "BERSERKER OFF", "INVISIBILITY OFF", "ENVIRONMENT SUIT OFF", "FULL MAP OFF", "LIGHT AMPLIFICATION GOGGLES OFF" };

typedef enum { msg_ammo, msg_health, msg_armor, msg_keys, msg_weapons, msg_all };

char *Gimme[] = { "Full ammo given", "Full health given", "Full armor given", "All keys given", "All weapons given",
                  "You got it ALL" };

extern int  key_right;
extern int  key_left;
extern int  key_up;
extern int  key_down; 
extern int  key_strafeleft;
extern int  key_straferight; 
extern int  key_fire;
extern int  key_use;
extern int  key_strafe;
extern int  key_speed; 
extern int  key_nextweapon;
extern int  key_prevweapon;

extern int  key_mvert;

extern int  usemouse;
extern int  mousebfire;
extern int  mousebstrafe;
extern int  mousebforward;

extern int  usejoystick;
extern int  joybup;
extern int  joybdown;
extern int  joybleft;
extern int  joybright;
extern int  joybfire; 
extern int  joybstrafe; 
extern int  joybuse; 
extern int  joybspeed;
extern int  joybstrafeleft;
extern int  joybstraferight;
extern int  joybnextweapon;
extern int  joybprevweapon;


extern int          always_run;
extern int          swap_stereo;
extern int          mvert;
extern int          keylink;

extern unsigned char scan2chars[256];
extern unsigned char scan2char[256];
 
typedef enum { cv_value, cv_scan } cv_types;

typedef enum { c_text,
               c_fire,
               c_forward,
               c_back,
               c_left,
               c_right,
               c_slide,
               c_slideleft,
               c_slideright,
               c_use,
               c_run,
               c_weapon1,
               c_weapon2,
               c_weapon3,
               c_weapon4,
               c_weapon5,
               c_weapon6,
               c_weapon7,
               c_say,
               c_wait,
               c_end
             } c_commands;

typedef struct
   {
    unsigned char  key;
    unsigned char *command;
   }Alias_t;

unsigned char testcmd[] = { c_fire, c_forward, c_slideleft, c_slideleft, c_slideleft, c_forward, c_fire, c_end };

Alias_t aliases[256];

typedef struct
   {
    int  *var;
    char *name;
    int  cv_type;
    int  maxval;
   }KeyDef_t;

KeyDef_t cvars[] = { &key_right,        "KEY_RIGHT",        cv_scan, 0,
                     &key_up,           "KEY_UP",           cv_scan, 0,
                     &key_left,         "KEY_LEFT",         cv_scan, 0,
                     &key_down,         "KEY_DOWN",         cv_scan, 0,
                     &key_strafeleft,   "KEY_STRAFELEFT",   cv_scan, 0,
                     &key_straferight,  "KEY_STRAFERIGHT",  cv_scan, 0,
                     &key_fire,         "KEY_FIRE",         cv_scan, 0,
                     &key_use,          "KEY_USE",          cv_scan, 0,
                     &key_strafe,       "KEY_STRAFE",       cv_scan, 0,
                     &key_speed,        "KEY_SPEED",        cv_scan, 0,
                     &key_nextweapon,   "KEY_NEXTWEAPON",   cv_scan, 0,
                     &key_prevweapon,   "KEY_PREVWEAPON",   cv_scan, 0,

                     &usejoystick,      "USEJOYSTICK",      cv_value, 1,
                     &joybup,           "JOY_UP",           cv_value, 0,
                     &joybdown,         "JOY_DOWN",         cv_value, 0,
                     &joybleft,         "JOY_LEFT",         cv_value, 0,
                     &joybright,        "JOY_RIGHT",        cv_value, 0,
                     &joybfire,         "JOY_FIRE",         cv_value, 0,
                     &joybstrafe,       "JOY_STRAFE",       cv_value, 0,
                     &joybuse,          "JOY_USE",          cv_value, 0,
                     &joybspeed,        "JOY_SPEED",        cv_value, 0,
                     &joybstrafeleft,   "JOY_STRAFELEFT",   cv_value, 0,
                     &joybstraferight,  "JOY_STAFERIGHT",   cv_value, 0,
                     &joybnextweapon,   "JOY_NEXTWEAPON",   cv_value, 0,
                     &joybprevweapon,   "JOY_PREVWEAPON",   cv_value, 0,
                                          
                     &swap_stereo,      "SWAP_STEREO",      cv_value, 1,
                     &always_run,       "ALWAYS_RUN",       cv_value, 1,

                     &usemouse,         "USEMOUSE",         cv_value, 1,
                     &mousebfire,       "MOUSEBFIRE",       cv_value, 2,
                     &mousebstrafe,     "MOUSEBSTRAFE",     cv_value, 2,
                     &mousebforward,    "MOUSEBFORWARD",    cv_value, 2,

                     &mvert,            "MVERT",            cv_value, 1,
                     &keylink,          "KEYLINK",          cv_value, 1,
                     NULL,              "",                 cv_value, 0 };

char *cmdlist[] = { "iddqd : god mode",
                    "idfa : full ammo",
                    "idkfa : keys full ammo",
                    "idclev : change level",
                    "idchoppers : chainsaw and invulnerability",
                    "idclip : no clipping toggle",
                    "idspispopd : no clipping toggle",
                    "idbeholdi : invisibility",
                    "idbeholdv : invulnerability",
                    "idbeholds : strength (berserk pack)",
                    "idbeholdr : radiation/environment suit",
                    "idbeholdl : light amplification goggles",
                    "idbeholda : all map cheat",
                    "cd on : starts your cd player (switches from midi)",
                    "cd off : stops your cd player (switches to midi)",
                    "cd pause : pause/resume cd music toggle",
                    "cd resume : pause/resume cd music toggle",
                    "cd next : play next song on cd",
                    "cd + : play next song on cd",
                    "cd prev : play previous song on cd",
                    "cd - : play previous song on cd",
                    "cd XX : plays song number specified in XX 00 to 99",
                    "midi pause : pauses/resumes the midi playback (toggle)",
                    "midi resume : pauses/resumes the midi playback (toggle)",
                    "quit : quits the game (immediately)",
                    "god : enable god mode (degreelessness?) toggle",
                    "map : e?m? or map?? (Doom I or Doom II map names)",
                    "noclip : no clipping toggle",
                    "give all : gives full ammo,armor,health,weapons,keys",
                    "give ammo : gives full ammo",
                    "give armor : gives full armor",
                    "give health : give 100% health",
                    "give weapons : gives all weapons",
                    "give keys : gives all keys",
                    "give backpack : gives ammo backpack",
                    "always_run X : toggles always run 0 = off, 1 = on",
                    "swap_stereo X : toggles swap left/right 0 = off, 1 = on",
                    "bind : binds a value to a cvar",
                    "record : records a demo in new demo II format",
                    "finish : stops recording a demo II format demo",
                    "play : plays back a demo II format demo",
                    "cmdlist : lists console commands",
                    "cvarlist : lists cvars",
                    "" };


typedef struct
   {
    int scancode;
    char *name;
   }KeyName_t;

char *scanname[] = {    "NULL", // no key
                        "", // <ESC>
                        "", // 1
                        "",
                        "",
                        "", // reserved for weapons...
                        "",
                        "",
                        "",  // 7
                       "8",  // open
                       "9",  // open
                       "0",  // open
                        "",  // minus key
                        "",  // equals key
                    "BACK",  // backspace key
                        "",  // tab key
                       "Q",
                       "W",
                       "E",
                       "R",
                       "T",
                       "Y",
                       "U",
                       "I",
                       "O",
                       "P",
                       "[",
                       "]",
                   "ENTER", // enter key
                   "LCTRL", // left control key
                       "A",
                       "S",
                       "D",
                       "F",
                       "G",
                       "H",
                       "J",
                       "K",
                       "L",
                       ";",
                       "'",
                        "", // tilde - console key
                  "LSHIFT",
                      "\\",
                       "Z",
                       "X",
                       "C",
                       "V",
                       "B",
                       "N",
                       "M",
                       ",",
                       ".",
                       "/",
                  "RSHIFT",
                        "",  // print screen - sysrq
                    "LALT",  
                   "SPACE",
                    "CAPS",
                        "",  //  F1
                        "",  //  F2
                        "",  //  F3
                        "",  //  F4
                        "",  //  F5
                        "",  //  F6
                        "",  //  F7
                        "",  //  F8
                        "",  //  F9
                        "",  // F10
                 "NUMLOCK",
                  "SCROLL",
                    "PAD7",
                    "PAD8",
                    "PAD9",
                    "PAD-",
                    "PAD4",
                    "PAD5",
                    "PAD6",
                    "PAD+",
                    "PAD1",
                    "PAD2",
                    "PAD3",
                    "PAD0",
                    "PAD.",
                        "",  // no key
                        "",  // no key
                        "",
                        "",  // F11
                        "",  // F12
                        "",  // no key 0x59 89
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key
                        "",  // no key 0x9B 155
                "PADENTER", // 0x9C
                   "RCTRL", // 0x9D
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                    "PAD/",
                        "", 
                        "", // SYS RQ
                    "RALT",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                    "HOME",
                      "UP",
                  "PAGEUP",
                        "",
                    "LEFT",
                        "",
                   "RIGHT",
                        "",
                     "END",
                    "DOWN",
                "PAGEDOWN",
                  "INSERT",
                  "DELETE",
                       "-" };


char PowerUpKey[] = "VSIRAL";

void CO_Ticker()
{
    static int lasttics = 0;
    int        gametics, newtics;

    if (bConsoleActive == FALSE) return;

    gametics = I_GetTime();
    if ((lasttics == 0) || (iConsoleMode == asleep))
	{
        newtics = 1;
        iConsoleMode = waking;
	}
    else
        newtics = gametics - lasttics;
    lasttics = gametics;

    switch(iConsoleMode)
	{
	case sleepy:
		if (iConsoleHeight > 0)
			iConsoleHeight -= (iConsoleSpeed * 2 * newtics);
		else
		{
			iConsoleMode = asleep;
			iCCursor = 0;
			bConsoleActive = FALSE;
			if(scaledviewwidth != SCREENWIDTH)
				R_DrawViewBorder();
		}
		if (iConsoleHeight < 0)
			iConsoleHeight = 0;
		break;
	case waking:
		if (iConsoleHeight < iConsoleMax)
			iConsoleHeight += (iConsoleSpeed * newtics);
		else
		{
			iConsoleMode = awake;
		}
		if (iConsoleHeight > iConsoleMax)
			iConsoleHeight = iConsoleMax;
		break;
	case awake:
		// Do whatever might need to be done to an active console here...
		// Animations?
		break;
	}
}

BOOL CO_Responder(event_t* ev)
{
    int           i;
    unsigned char c;
    static BOOL bDisplayed = FALSE;
    static BOOL bShiftState = FALSE;

    if ((ev->type == ev_keydown) && (ev->data1 == KEY_CONSOLE))
	{
        if (bConsoleActive == TRUE)
		{
            iConsoleMode = sleepy;
            paused = FALSE;
            return TRUE;
		}
        else
		{
            bConsoleActive = TRUE;
            if((netgame == false) && (gamestate == GS_LEVEL) && (demoplayback == FALSE))
                paused = true;
            for(i = 0; szCommand[i]; i++)
				szCommand[i] = '\0';
            iCCursor = 0;
            return FALSE;
		}
	}
    
	if ((ev->type == ev_keydown) && (ev->data1 == KEY_ESCAPE))
	{
        if (bConsoleActive == TRUE)
		{
            iConsoleMode = asleep;
            bConsoleActive = FALSE;
            paused = FALSE;  //11.7.98 dlw bugfix
            return FALSE;
		}
	}

    if(bConsoleActive == FALSE)
       return FALSE;

    if((ev->type == ev_keydown) && (ev->data1 == KEY_RSHIFT))
	{
        bShiftState = TRUE;
        return FALSE;
	}

    if ((ev->type == ev_keyup) && (ev->data1 == KEY_RSHIFT))
	{
        bShiftState = FALSE;
        return FALSE;
	}

    if(ev->type != ev_keydown)
		return FALSE;

    if(ev->type == ev_keydown)
	{
        switch(ev->data1)
		{
		case KEY_SCRNSHOT:
			G_ScreenShot();
			break;
		case KEY_BACKSPACE:
		case KEY_LEFTARROW:
			if(iCCursor > 0)
			{
				iCCursor--;
				szCommand[iCCursor] = '\0';
			}
			break;
		case KEY_ENTER:
			if(iCCursor > 0)
			{
				CO_AddConsoleMessage(szCommand);
				CO_HandleCommand(szCommand);
				for(i = 0; i < CMDLENGTH; i++)
					szCommand[i] = '\0';
				iCCursor = 0;
				bDisplayed = FALSE;
			}
			break;
		case KEY_TAB:
			return FALSE;
		default:
			if(iCCursor < CMDLENGTH)
			{
				if(bShiftState == TRUE)
					c = scan2chars[ev->data1];
				else
					c = scan2char[ev->data1];
				if((c >= 32) && (c <= 127))
				{
					szCommand[iCCursor] = c;
					iCCursor++;
				}
			}
			break;
		}
        if((stricmp(szCommand, "idbehold") == 0) && (bDisplayed == FALSE))
		{
            plyr->message = STSTR_BEHOLD;
            bDisplayed = TRUE;
		}
	}

    return TRUE;
}

void CO_Init()
{
    int i;

    iConsoleMax = SCREENHEIGHT/2;

    // Load the main console background "flat"
    pconstex = (byte *)W_CacheLumpName(CONSOLE_FLAT, PU_CACHE);
    memcpy(consback, pconstex, 64*64);
    // Load the console border "flat"
    pconstex = (byte *)W_CacheLumpName(CONSOLE_BORD, PU_CACHE);
    memcpy(consbord, pconstex, 64*64);
    // Load the game logo "patch"
    consname = (patch_t *)W_CacheLumpName(CONSOLE_NAME, PU_STATIC);
    iFontHigh = hu_font[0]->height;
    sprintf(szVersion, "V%d.%02d", CONSVERS/100,CONSVERS%100);
    iNamePosX = SCREENWIDTH-(CO_StringWidth(szProgName)+1);
    iVerPosX = SCREENWIDTH-(CO_StringWidth(szVersion)+1);
    for (i = 0; i < CONSMSGS; i++)
       consmsgs[i][0] = '\0';
    plyr = &players[consoleplayer];
    aliases[0].command = testcmd;
}

void CO_Drawer()
{
    int h, v, yoff, d, s, i, j, clines, mline;
    static char tstr[32];
    static int  cursor = 0;
    int         curpos;

    cursor++;
    cursor %= 18;

    if (bConsoleActive == FALSE)
       return;

    if (scaledviewwidth != SCREENWIDTH)
        R_DrawViewBorder();

    // 64 is the height of a "flat"
    // flats are 64x64 bitmaps
    for (v = 0; v < (iConsoleHeight-CONSBORD); v++)
	{
        yoff = v * SCREENWIDTH;
        i = v % 64;
        for (h = 0; h < SCREENWIDTH; h++)
		{
            s = (i * 64)+(h % 64);
            d = yoff + h;
            screens[0][d] = consback[s];
		}
	}
    for (j = (64-CONSBORD)/2; v < iConsoleHeight; v++, j++)
	{
        yoff = v * SCREENWIDTH;
        i = v % 64;
        for (h = 0; h < SCREENWIDTH; h++)
		{
            s = (j * 64)+(h % 64);
            d = yoff + h;
            screens[0][d] = consbord[s];
		}
	}

    if(iConsoleHeight >= (consname->height+CONSBORD+2))
	{
        // Draw the Game logo (Doom, Doom II, TNT, Plutonia, whatever)
        V_DrawPatch(((SCREENWIDTH-consname->width)/2)-3, 2, 0, consname);
	}

    if (iConsoleHeight > 10)
	{
        clines = ((iConsoleHeight-(CONSBORD+iFontHigh+3))/(iFontHigh+1));
        M_WriteText(iNamePosX,1,szProgName);
        M_WriteText(iVerPosX,iConsoleHeight-(CONSBORD+iFontHigh+1),szVersion);
        curpos = CO_WriteConsoleLine(clines, szCommand, TRUE);
        if(cursor/9)
            M_WriteText(curpos,clines*(iFontHigh+1),"_");
        clines = ((iConsoleHeight-(CONSBORD+iFontHigh+3))/(iFontHigh+1));
        mline = iConsHead - clines;
        if(mline < 0)
			mline += CONSMSGS;
        for(i = 0; i < clines; i++)
		{
            CO_WriteConsoleLine(i, consmsgs[mline], TRUE);
            mline++;
            mline %= CONSMSGS;
		}
	}
}

// This function should return the width of the string in pixels.
int CO_StringWidth(char *s)
{
    int           i, j;
    unsigned char c;

    j = i = 0;
    while (s[i])
	{
        c = toupper(s[i]-HU_FONTSTART);
        if ((c < 0) || (c >= HU_FONTSIZE))
			j += 4;
        else
			j += hu_font[c]->width;
        i++;
	}
    return j;
}

// This function should return the first character in the string that will
// allow the string to be printed from there to the end.
int CO_StringPrintable(char *s)
{
    int           i, j;
    unsigned char c;

    j = SCREENWIDTH-(CO_StringWidth(s)+5);
    i = 0;
    while (j < 0)
       {
        c = toupper(s[i]-HU_FONTSTART);
        if ((c < 0) || (c >= HU_FONTSIZE))
           j += 4;
        else
           j += hu_font[c]->width;
        i++;
       }
    return i;
   }

int CO_WriteConsoleLine(int l, char *s, BOOL wrap)
{
    int  b;
    BOOL lwrap;

    lwrap = wrap;
    if(lwrap == TRUE)
	{
        if(CO_StringWidth(s) < SCREENWIDTH)
			lwrap = FALSE;
        else
			b = CO_StringPrintable(s);
	}

    if(lwrap == FALSE)
	{
        M_WriteText(1,(iFontHigh+1)*l,s);
        return CO_StringWidth(s);
	}
    else
	{
        M_WriteText(SCREENWIDTH-(CO_StringWidth(&s[b])+5),(iFontHigh+1)*l,&s[b]);
        return CO_StringWidth(&s[b]);
	}
}

void CO_AddConsoleMessage(char *s)
{
    strncpy(consmsgs[iConsHead], s, 128);
    if(strlen(s) > 128)
		consmsgs[iConsHead][128] = '\0';
    iConsHead++;
    iConsHead %= CONSMSGS;
}

int CO_HandleCommand(char *cmd)
{
    int      i, sc;
    char    *ts;

    if(!netgame)
	{
        // b. - enabled for more debug fun.
        // if (gameskill != sk_nightmare) {
      
        // 'dqd' cheat for toggleable god mode
        if ((stricmp(cmd, "iddqd") == 0) || (stricmp(cmd, "god") == 0))
		{
			// kill score if cheating... who cares if score is on?
			totalscore=0; keepscore=0; showscoreHUD=0;
            plyr->cheats ^= CF_GODMODE;
            if (plyr->cheats & CF_GODMODE)
			{
                if (plyr->mo)
                    plyr->mo->health = 100;
                plyr->health = 100;
                plyr->message = STSTR_DQDON;
			}
            else 
                plyr->message = STSTR_DQDOFF;
            return FALSE;
		}
        // 'fa' cheat for killer fucking arsenal (full ammo)
        else if (stricmp(cmd, "idfa") == 0)
		{
            plyr->armorpoints = 200;
            plyr->armortype = 2;
	
            for (i = 0;i < NUMWEAPONS; i++)
               plyr->weaponowned[i] = true;
	
            for (i = 0;i < NUMAMMO; i++)
               plyr->ammo[i] = plyr->maxammo[i];
			// kill score if cheating... who cares if score is on?
			totalscore=0; keepscore=0; showscoreHUD=0;
	
            plyr->message = STSTR_FAADDED;
            return FALSE;
		}
        // 'kfa' cheat for key full ammo  (keys, full ammo)
        else if (stricmp(cmd, "idkfa") == 0)
		{
            plyr->armorpoints = 200;
            plyr->armortype = 2;
	
            for (i = 0;i < NUMWEAPONS; i++)
                plyr->weaponowned[i] = true;
            for (i = 0;i < NUMAMMO; i++)
                plyr->ammo[i] = plyr->maxammo[i];
	
            for (i=0;i<NUMCARDS;i++)
                plyr->cards[i] = true;
	
			// kill score if cheating... who cares if score is on?
			totalscore=0; keepscore=0; showscoreHUD=0;

            plyr->message = STSTR_KFAADDED;
            return FALSE;
        }
        // 'mus' cheat for changing music
        else if(strnicmp(cmd, "idmus", 5) == 0)
        {
            char buf[3];
            int  musnum;
			
            plyr->message = STSTR_MUS;
            strcpy(buf, &cmd[5]);
	
            if(gamemode == commercial)
            {
                // just test a song for now - music fixed, turned on
				// musnum=12;
				musnum = mus_runnin + (buf[0]-'0')*10 + buf[1]-'0' - 1;
				
                if(((buf[0]-'0')*10 + buf[1]-'0') > 35)
					plyr->message = STSTR_NOMUS;
                else
                    S_ChangeMusic(musnum, 1);
            }
            else
            {
                musnum = mus_e1m1 + (buf[0]-'1')*9 + (buf[1]-'1');
				if (((buf[0]-'1')*9 + buf[1]-'1') > 31)
                    plyr->message = STSTR_NOMUS;
                else
                    S_ChangeMusic(musnum, 1);
            }
            return FALSE;
        }
        // Simplified, accepting both "noclip" and "idspispopd".
        // no clipping mode cheat
        else if((stricmp(cmd, "idclip") == 0) || (stricmp(cmd, "idspispopd") == 0) || (stricmp(cmd, "noclip") == 0))
		{	
            plyr->cheats ^= CF_NOCLIP;
			if (plyr->cheats & CF_NOCLIP)
                plyr->message = STSTR_NCON;
            else
                plyr->message = STSTR_NCOFF;

			// kill score if cheating... who cares if score is on?
			totalscore=0; keepscore=0; showscoreHUD=0;

            return FALSE;
		}
        // 'behold?' power-up cheats
        else if(strnicmp(cmd, "idbehold", 8) == 0)
		{
            for (i = 0;i < 6;i++)
			{
                if (PowerUpKey[i] == toupper(cmd[8]))
				{
                    if (!plyr->powers[i])
					{
                        P_GivePower(plyr, i);
                        plyr->message = PowerUpOn[i];
					}
                    else if (i!=pw_strength)
					{
						plyr->powers[i] = 1;
						plyr->message = PowerUpOff[i];
					}
					else
					{
						plyr->powers[i] = 0;
						plyr->message = PowerUpOff[i];
					}
				}
			}
			// kill score if cheating... who cares if score is on?
			totalscore=0; keepscore=0; showscoreHUD=0;
            return FALSE;
		}
        else if(strnicmp(cmd, "give ", 5) == 0)
		{
            if(stricmp(&cmd[5], "all") == 0)
			{
                for (i = 0;i < NUMAMMO; i++)
					plyr->ammo[i] = plyr->maxammo[i];
                for (i = 0;i < NUMWEAPONS; i++)
                    plyr->weaponowned[i] = true;
                plyr->armorpoints = 200;
                plyr->armortype = 2;
                if (plyr->mo)
                    plyr->mo->health = 100;
                plyr->health = 100;
                for(i=0;i<NUMCARDS;i++)
                    plyr->cards[i] = true;
                plyr->message = Gimme[msg_all];
				// kill score if cheating... who cares if score is on?
				totalscore=0; keepscore=0; showscoreHUD=0;
                return FALSE;
			}
            else if(stricmp(&cmd[5], "ammo") == 0)
			{
                for(i = 0;i < NUMAMMO; i++)
					plyr->ammo[i] = plyr->maxammo[i];
                plyr->message = Gimme[msg_ammo];
				// kill score if cheating... who cares if score is on?
				totalscore=0; keepscore=0; showscoreHUD=0;
                return FALSE;
			}
            else if(stricmp(&cmd[5], "weapons") == 0)
			{
                for (i = 0;i < NUMWEAPONS; i++)
                    plyr->weaponowned[i] = true;
                plyr->message = Gimme[msg_weapons];
				// kill score if cheating... who cares if score is on?
				totalscore=0; keepscore=0; showscoreHUD=0;
				return FALSE;
			}
            else if(stricmp(&cmd[5], "armor") == 0)
			{
                plyr->armorpoints = 200;
                plyr->armortype = 2;
                plyr->message = Gimme[msg_armor];
				// kill score if cheating... who cares if score is on?
				totalscore=0; keepscore=0; showscoreHUD=0;
                return FALSE;
			}
            else if(stricmp(&cmd[5], "health") == 0)
			{
                if (plyr->mo)
                    plyr->mo->health = 100;
                plyr->health = 100;
                plyr->message = Gimme[msg_health];
				// kill score if cheating... who cares if score is on?
				totalscore=0; keepscore=0; showscoreHUD=0;
                return FALSE;
			}
			else if(stricmp(&cmd[5], "keys") == 0)
			{
                for (i=0;i<NUMCARDS;i++)
                    plyr->cards[i] = true;
                plyr->message = Gimme[msg_keys];
				// kill score if cheating... who cares if score is on?
				totalscore=0; keepscore=0; showscoreHUD=0;
                return FALSE;
			}
            else if(stricmp(&cmd[5], "backpack") == 0)
			{
				if (!plyr->backpack)
	            {
					for(i = 0; i < NUMAMMO; i++)
						plyr->maxammo[i] *= 2;
					plyr->backpack = true;
				}
				for(i = 0; i < NUMAMMO; i++)
					P_GiveAmmo(plyr, i, 1);
				// kill score if cheating... who cares if score is on?
				totalscore=0; keepscore=0; showscoreHUD=0;
				plyr->message = GOTBACKPACK;
			}
            return FALSE;
		} // 'give'
		// 'choppers' invulnerability & chainsaw
        else if (stricmp(cmd, "choppers") == 0)
		{
            plyr->weaponowned[wp_chainsaw] = true;
            plyr->powers[pw_invulnerability] = true;
            plyr->message = STSTR_CHOPPERS;
			// kill score if cheating... who cares if score is on?
			totalscore=0; keepscore=0; showscoreHUD=0;
            return FALSE;
		}
        // 'mypos' for player position
        else if(stricmp(cmd, "mypos") == 0)
		{
            static char	buf[ST_MSGWIDTH];
            sprintf(buf, "ang=0x%x;x,y=(0x%x,0x%x)",
				players[consoleplayer].mo->angle,
				players[consoleplayer].mo->x,
				players[consoleplayer].mo->y);
			plyr->message = buf;
            return FALSE;
		}
	} //!netgame
/*
    if(strnicmp(cmd, "midi ", 5) == 0)
	{
        if((stricmp(&cmd[3], "pause") == 0) || (stricmp(&cmd[3], "resume") == 0))
            PauseResumeMusic();
	}*/
/*
    // Control the CD Player...
    else if(strnicmp(cmd, "cd ", 3) == 0)
	{
        if((stricmp(&cmd[3], "on") == 0) || (stricmp(&cmd[3], "play") == 0))
            PlayCDMusic();
        else if((stricmp(&cmd[3], "pause") == 0) || (stricmp(&cmd[3], "resume") == 0))
			PauseResumeMusic();
		else if((stricmp(&cmd[3], "off") == 0) || (stricmp(&cmd[3], "stop") == 0))
			PlayMidiMusic();
		else if((stricmp(&cmd[3], "next") == 0) || (stricmp(&cmd[3], "+") == 0))
			PlayNextSong();
		else if((stricmp(&cmd[3], "prev") == 0) || (stricmp(&cmd[3], "-") == 0))
			PlayPrevSong();
		else if (isdigits(&cmd[3]) && (strlen(&cmd[3]) < 3))
			PlayCDTrack(atoi(&cmd[3]));
		return FALSE;
	}
*/
    else if(strnicmp(cmd, "record ", 7) == 0)
	{
        static char buf[ST_MSGWIDTH];
        if(strlen(&cmd[7]) > 0)
		{
            G_RecordDemo_II(&cmd[7]);
            sprintf(buf, "RECORDING DEMO II: %s", &cmd[7]);
            plyr->message = buf;
            G_BeginRecording_II();
            bConsoleActive = FALSE;
            paused = FALSE;
		}
        return FALSE;
	}

    else if(stricmp(cmd, "finish") == 0)
	{
        static char buf[ST_MSGWIDTH];
        G_EndDemo_II();
        sprintf(buf, "DEMO II SAVED");
        plyr->message = buf;
        return FALSE;
	}

    else if(strnicmp(cmd, "play ", 5) == 0)
	{
        static char buf[ST_MSGWIDTH];
        if(strlen(&cmd[7]) > 0)
		{
            if(G_DeferedPlayDemo_II(&cmd[5]) == true)
			{
                sprintf(buf, "PLAYING DEMO II: %s", &cmd[5]);
                plyr->message = buf;
                bConsoleActive = FALSE;
                paused = FALSE;
			}
            else
			{
                sprintf(buf, "DEMO II [%s.dem] - NO FILE.", &cmd[5]);
                plyr->message = buf;
			}
		}
        return FALSE;
	}

    else if(stricmp(cmd, "cmdlist") == 0)
	{
        i = 0;
        while (cmdlist[i][0] != '\0')
            CO_AddConsoleMessage(cmdlist[i++]);
        return FALSE;
	}

    else if(stricmp(cmd, "cvarlist") == 0)
	{
        static char buf[128];
        i = 0;
        while (cvars[i].name[0] != '\0')
		{
            sprintf(buf, "%s - %d", cvars[i].name, *cvars[i].var);
            CO_AddConsoleMessage(buf);
            i++;
		}
        return FALSE;
	}
    
	if(!netgame)  // 11.7.98 again?  move up? dlw
	{
        // 'map' change-level cheat
        if(strnicmp(cmd, "map ", 4) == 0)
		{
            int  epsd;
            int  map;
			
            if(strnicmp(&cmd[4],"map",3) == 0)
			{
                map = (cmd[7] - '0')*10 + cmd[8] - '0';
                if ((map < 1) || (map > 34))
                    epsd = 0;
                else
                    epsd = 1;
			}
            else if (((cmd[4] == 'e') && (cmd[6] == 'm')) ||
                ((cmd[4] == 'E') && (cmd[6] == 'M')))
			{
                epsd = cmd[5] - '0';
                map =  cmd[7] - '0';
			}
            // Catch invalid maps.
            if(epsd < 1) return FALSE;
            if(map < 1)  return FALSE;      
            // Ohmygod - this is not going to work.
            if((gamemode == retail) && ((epsd > 4) || (map > 9)))
                return FALSE;
            if((gamemode == registered) && ((epsd > 3) || (map > 9)))
                return FALSE;
            if((gamemode == shareware) && ((epsd > 1) || (map > 9)))
                return FALSE;
            if((gamemode == commercial) && (( epsd > 1) || (map > 34)))
                return FALSE;
            // So be it.
            plyr->message = STSTR_CLEV;
			// kill score if cheating... who cares if score is on?
			totalscore=0; keepscore=0; showscoreHUD=0;
            G_DeferedInitNew(gameskill, epsd, map);
            return FALSE;
		}
		// 'clev' change-level cheat
        else if(strnicmp(cmd, "idclev", 6) == 0)
		{ 
            char buf[3];
            int  epsd;
            int  map;
			
            strcpy(buf, &cmd[6]);
      
            if(gamemode == commercial)
			{
                epsd = 1;
                map = (buf[0] - '0')*10 + buf[1] - '0';
			}
            else
			{
                epsd = buf[0] - '0';
                map = buf[1] - '0';
			}
            // Catch invalid maps.
            if(epsd < 1) return FALSE;
            if (map < 1) return FALSE;      
            // Ohmygod - this is not going to work.
            if((gamemode == retail) && ((epsd > 4) || (map > 9)))
                return FALSE;
            if((gamemode == registered) && ((epsd > 3) || (map > 9)))
                return FALSE;
            if((gamemode == shareware) && ((epsd > 1) || (map > 9)))
                return FALSE;
            if((gamemode == commercial) && (( epsd > 1) || (map > 34)))
                return FALSE;
            // So be it.
            plyr->message = STSTR_CLEV;
			// kill score if cheating... who cares if score is on?
			totalscore=0; keepscore=0; showscoreHUD=0;
            G_DeferedInitNew(gameskill, epsd, map);
            return FALSE;
		}
	} //netgame2
    
	if(stricmp(cmd, "quit") == 0)
	{
        I_Quit();
        return FALSE;
	}
	// 11.7.98 dlw Optimizer for frames frames frames
	// usemouse and usejoy can be turned off
	else if(stricmp(cmd, "mouse") == 0)
	{
        char buf[ST_MSGWIDTH];
		usemouse = !usemouse;
		if(usemouse)
			sprintf(buf, "mouse turned on");
		else
			sprintf(buf, "mouse turned off");
		CO_AddConsoleMessage(buf);
		return FALSE;
	}
	else if(stricmp(cmd, "joystick") == 0)
	{
        char buf[ST_MSGWIDTH];
		usejoystick = !usejoystick;
		if(usejoystick)
			sprintf(buf, "joystick turned on");
		else
			sprintf(buf, "joystick turned off");
		CO_AddConsoleMessage(buf);
		return FALSE;
	}

    ts = strtok(cmd, " ");
    if(stricmp(ts, "bind") == 0)  // This is a 'bind' command...
	{
        ts = strtok(NULL, " ");
        for(i = 0; ts != NULL && cvars[i].name[0]; i++) // Match to a command...
		{
            if(cvars[i].cv_type != cv_scan)  // It this a key or a control variable
                continue;
            if(stricmp(ts, cvars[i].name) == 0) // found a matching cvar name
			{
                if(isdigits(ts) == TRUE)  // Ok, they put digits in rather than a keyname
				{
                    sc = atoi(ts);
                    if(sc > 255)  // Can't have more than 255 or less than 0
					{
                        plyr->message = "BIND ERROR: INVALID KEY VALUE";
					}
                    else
					{
                        static char buf[ST_MSGWIDTH];
                        sprintf(buf, "CMD %s BOUND TO SCANCODE %3d\n", cvars[i].name, sc);
                        plyr->message = buf;
                        *cvars[i].var = sc;
					}
				}
                else
				{
                    ts = strtok(NULL, " ");  // They put in something - hopefully a keyname
                    if(ts != NULL)
					{
                        static char buf[ST_MSGWIDTH];
                        for(sc = 0; scanname[sc][0] != '-'; sc++)  // Search for a matching keyname
						{
                            if(!scanname[sc][0])
								continue;
                            if(stricmp(ts, scanname[sc]) == 0)
							{
                                sprintf(buf, "CMD %s BOUND TO SCANCODE %3d\n", cvars[i].name, sc);
                                plyr->message = buf;
                                *cvars[i].var = sc;
                                break;
							}
						}
                        if(scanname[sc][0] == '-')  // Didn't find a matching keyname
                            plyr->message = "BIND ERROR: INVALID KEY VALUE";
					}
				}
                break;
			}
		}
        if(!cvars[i].name[0])  // Didn't find a matching key command
            plyr->message = "BIND ERROR: INVALID CVAR";
	}
    else
	{
        for(i = 0; ts != NULL && cvars[i].name[0]; i++)
		{
            if(cvars[i].cv_type != cv_value)
                continue;
            if(stricmp(ts, cvars[i].name) == 0)
			{
                static char buf[ST_MSGWIDTH];
                ts = strtok(NULL, " ");
                if(ts != NULL)
				{
                    if(ts[0] >= '0' && ts[0] <= ('0'+cvars[i].maxval))
					{
                        *cvars[i].var = ts[0] - '0';
                        sprintf(buf, "%s SET TO %d\n", cvars[i].name, *cvars[i].var);
                        plyr->message = buf;
					}
                    else
                        plyr->message = "ERROR: INVALID VALUE";
				}
                else
				{
                    sprintf(buf, "%s VALUE %d\n", cvars[i].name, *cvars[i].var);
                    plyr->message = buf;
				}
                break;
			}
		}
        if(!cvars[i].name[0])
            plyr->message = "ERROR: INVALID CVAR";
	}

    return FALSE;
}

BOOL isdigits(char *s)
{
    int i;

    for (i = 0; s[i]; i++)
       if (!isdigit(s[i]))
           return FALSE;
    return TRUE;
}