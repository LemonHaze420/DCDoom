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
// $Log:$
//
// DESCRIPTION:  none
//
//-----------------------------------------------------------------------------


static const char
rcsid[] = "$Id: g_game.c,v 1.8 1997/02/03 22:45:09 b1 Exp $";

#include <string.h>
#include <stdlib.h>

#include "doomdef.h" 
#include "doomstat.h"

#include "z_zone.h"
#include "f_finale.h"
#include "m_argv.h"
#include "m_misc.h"
#include "m_menu.h"
#include "m_random.h"
#include "i_system.h"

#include "p_setup.h"
#include "p_saveg.h"
#include "p_tick.h"

#include "d_main.h"

#include "wi_stuff.h"
#include "hu_stuff.h"
#include "st_stuff.h"
#include "am_map.h"

// Needs access to LFB.
#include "v_video.h"

#include "w_wad.h"

#include "p_local.h" 

#include "s_sound.h"

// Data.
#include "dstrings.h"
#include "sounds.h"

// SKY handling - still the wrong place.
#include "r_data.h"
#include "r_sky.h"




#include "g_game.h"

#define _finesine(a) finesine[a]
#define _finecosine(a) finecosine[a]

#define SAVEGAMESIZE	0x2c000
#define SAVESTRINGSIZE	24

void WriteDebug(char *);
char MsgText[256];

boolean	G_CheckDemoStatus (void); 
void	G_ReadDemoTiccmd (ticcmd_t* cmd); 
void	G_WriteDemoTiccmd (ticcmd_t* cmd); 
void	G_PlayerReborn (int player); 
void	G_InitNew (skill_t skill, int episode, int map); 
 
void	G_DoReborn (int playernum); 
 
void	G_DoLoadLevel (void); 
void	G_DoNewGame (void); 
void	G_DoLoadGame (void); 
void	G_DoPlayDemo (void); 
void	G_DoPlayDemo_II(void); 
void	G_DoCompleted (void); 
void	G_DoVictory (void); 
void	G_DoWorldDone (void); 
void	G_DoSaveGame (void); 
 
 
gameaction_t    gameaction; 
gamestate_t     gamestate; 
skill_t         gameskill; 
boolean		respawnmonsters;
int             gameepisode; 
int             gamemap; 
 
boolean         paused; 
boolean         sendpause;             	// send a pause event next tic 
boolean         sendsave;             	// send a save event next tic 
boolean         usergame;               // ok to save / end game 
 
boolean         timingdemo;             // if true, exit with report on completion 
boolean         nodrawers;              // for comparative timing purposes 
boolean         noblit;                 // for comparative timing purposes 
int             starttime;          	// for comparative timing purposes  	 
 
boolean         viewactive; 
 
boolean         deathmatch;           	// only if started as net death 
boolean         netgame;                // only true if packets are broadcast 
boolean         playeringame[MAXPLAYERS]; 
player_t        players[MAXPLAYERS]; 
boolean			internetgame;	//11.12.98 dlw optimize for internet

 
int             consoleplayer;          // player taking events and displaying 
int             displayplayer;          // view being displayed 
int             gametic; 
int             levelstarttic;          // gametic at level start 
int             totalkills, totalitems, totalsecret;    // for intermission 
long	totalscore;			// 10.15.98 scorekeeping dlw (2billion?)
char	totalscoretextline[200];
char	scoreuserwad[256];
char	HUDscoretext[200];
char	keepscore;
char	showscoreHUD;
char	DOUBLESTUFF;	//11.4.98 optimize dlw
long	SCREENMULT;		//11.5.98 optimize dlw width x height
 
char            demoname[32]; 
int             demotype; 
boolean         demorecording; 
boolean         demoplayback; 
boolean		netdemo; 
byte*		demobuffer;
byte*		demo_p;
byte*		demoend; 
boolean         singledemo;            	// quit after playing a demo from cmdline 
 
boolean         precache = true;        // if true, load all graphics at start 
 
wbstartstruct_t wminfo;               	// parms for world map / intermission 
 
short		consistancy[MAXPLAYERS][BACKUPTICS]; 
 
byte*		savebuffer;
 
 
// 
// controls (have defaults) 
// 
int		key_left;
int     key_right;
int		key_up;
int		key_down; 
int     key_strafeleft;
int	    key_straferight; 
int     key_fire;
int		key_use;
int		key_strafe;
int     key_speed; 
int     key_nextweapon;
int     key_prevweapon;

int     key_mvert;
 
int     mousebfire; 
int     mousebstrafe; 
int     mousebforward; 
int     mousebnextweapon = 6; //hack
int     mousebprevweapon = 5; //hack
 
int     joybup;
int     joybdown;
int     joybleft;
int     joybright;
int     joybfire; 
int     joybstrafe; 
int     joybuse; 
int     joybspeed;
int     joybstrafeleft;
int     joybstraferight;
int     joybnextweapon;
int     joybprevweapon;

int     joybmenu;

int     joybmenuselect;
int     joybmenucancel;

int     always_run;
int     swap_stereo;
int     mvert;
int     keylink;
int     link_alt;

extern int usemouse;
extern int usejoystick;
 
#define MAXPLMOVE		(forwardmove[1]) 
 
#define TURBOTHRESHOLD	0x32

fixed_t		forwardmove[2] = {0x19, 0x32};
fixed_t		sidemove[2] = {0x18, 0x28}; 
fixed_t		angleturn[3] = {640, 1280, 320};	// + slow turn 

#define SLOWTURNTICS	6 
 
#define NUMKEYS		256 

boolean         gamekeydown[NUMKEYS]; 
int             turnheld;				// for accelerative turning 
 
boolean		mousearray[8]; 
boolean*	mousebuttons = &mousearray[1];		// allow [-1]

// mouse values are used once 
int             mousex;
int		mousey;         

int             dclicktime;
int		dclickstate;
int		dclicks; 
int             dclicktime2;
int		dclickstate2;
int		dclicks2;

// joystick values are repeated 
int             joyxmove;
int		joyymove;
boolean         joyarray[33]; 
boolean*	joybuttons = &joyarray[1];		// allow [-1] 
 
int		savegameslot; 
char		savedescription[32]; 
 
 
#define	BODYQUESIZE	32

mobj_t*		bodyque[BODYQUESIZE]; 
int		bodyqueslot; 
 
void*		statcopy;				// for statistics driver
 
 
int G_CmdChecksum (ticcmd_t* cmd) 
{ 
    int		i;
    int		sum = 0; 
	 
    for (i=0 ; i< sizeof(*cmd)/4 - 1 ; i++) 
	sum += ((int *)cmd)[i]; 
		 
    return sum; 
} 
 

//
// G_BuildTiccmd
// Builds a ticcmd from all of the available inputs
// or reads it from the demo buffer. 
// If recording a demo, write it out 
// 
void G_BuildTiccmd(ticcmd_t* cmd) 
{ 
    int       i; 
    boolean   strafe;
    boolean   bstrafe; 
    int       speed;
    int       tspeed; 
    int       forward;
    int       side;
    // ticcmd_t *base;	//11.7.98 dlw original code not optimal


    //11.7.98 dlw opt
    cmd->forwardmove=0;
    cmd->sidemove=0;
    cmd->angleturn=0;
    //cmd->consistancy=0;
    cmd->chatchar=0;
    cmd->buttons=0;
	//base = I_BaseTiccmd();		// empty, or external driver
    //memcpy(cmd, base, sizeof(*cmd)); //11.7.98 dlw unneeded
	
    cmd->consistancy = consistancy[consoleplayer][maketic%BACKUPTICS]; 
 
    strafe = gamekeydown[key_strafe] || mousebuttons[mousebstrafe] || joybuttons[joybstrafe] || ( gamekeydown[key_straferight] && gamekeydown[key_strafeleft] ) || ( joybuttons[joybstrafeleft] && joybuttons[joybstraferight] ); 
    if ((joybspeed == 31) || (always_run == TRUE))
       speed = 1;
    else
       speed = gamekeydown[key_speed] || joybuttons[joybspeed];
    
 
    forward = side = 0;
    
    // use two stage accelerative turning on the keyboard
	// little optimized 11.8.98 dlw
    //if(joyxmove < 0 || joyxmove > 0 || gamekeydown[key_right] || gamekeydown[key_left]) 
	if( gamekeydown[key_right] || gamekeydown[key_left] || joybuttons[joybleft] || joybuttons[joybright] ) 
        turnheld += ticdup; 
    else 
        turnheld = 0; 

    if (turnheld < SLOWTURNTICS) 
        tspeed = 2;             // slow turn 
    else 
        tspeed = speed;
    
    // let movement keys cancel each other out
    if(strafe) 
	{ 
        if(gamekeydown[key_right] || joybuttons[joybright] )
		{
            // fprintf(stderr, "strafe right\n");
            side += sidemove[speed];
		}
        if(gamekeydown[key_left] || joybuttons[joybleft] )
		{
            // fprintf(stderr, "strafe left\n");
            side -= sidemove[speed];
		}
		if(usejoystick)
		{
            side += (joyxmove * sidemove[speed]) >> 10; //(approximate / 1000)
		}
	}
    else
	{
        if (gamekeydown[key_right] || joybuttons[joybright] )
            cmd->angleturn -= angleturn[tspeed];
        if (gamekeydown[key_left] || joybuttons[joybleft] )
            cmd->angleturn += angleturn[tspeed];
		if(usejoystick)
		{
            if( speed )
                cmd->angleturn -= (joyxmove * 640 ) >> 9;
            else
                cmd->angleturn -= (joyxmove * 320 ) >> 9;
		}
	}
 
    if (gamekeydown[key_up] || joybuttons[joybup] )
	{
        // fprintf(stderr, "up\n");
        forward += forwardmove[speed];
	}
    if (gamekeydown[key_down] || joybuttons[joybdown] )
	{
        // fprintf(stderr, "down\n");
        forward -= forwardmove[speed];
	}
	if(usejoystick)
	{
        forward -= (joyymove * forwardmove[speed] ) >> 10;
	}
	if(gamekeydown[key_straferight] || joybuttons[joybstraferight] )
        side += sidemove[speed];
    if(gamekeydown[key_strafeleft] || joybuttons[joybstrafeleft] )
        side -= sidemove[speed];
    
    // buttons
    cmd->chatchar = HU_dequeueChatChar(); 
 
    if (gamekeydown[key_fire] || mousebuttons[mousebfire] || joybuttons[joybfire])
	{
        cmd->buttons |= BT_ATTACK;
	}
	
    if(gamekeydown[key_use] || joybuttons[joybuse] )
	{ 
        cmd->buttons |= BT_USE;
        // clear double clicks if hit use button 
        dclicks = 0;
	} 

    // chainsaw overrides 
    for(i = 0; i < NUMWEAPONS-1; i++)
        if (gamekeydown[KEY_1+i])
		{ 
            cmd->buttons |= BT_CHANGE;
            cmd->buttons |= i<<BT_WEAPONSHIFT;
            break;
		}

    //change weapon hack
    if( gamekeydown[key_nextweapon] || joybuttons[joybnextweapon] || mousebuttons[mousebnextweapon] )
    {
        weapontype_t nextweapon = wp_next;
        cmd->buttons |= BT_CHANGE;
        cmd->buttons |= nextweapon<<BT_WEAPONSHIFT;
    }
    if( gamekeydown[key_prevweapon] || joybuttons[joybprevweapon] || mousebuttons[mousebprevweapon] )
    {
        weapontype_t nextweapon = wp_prev;
        cmd->buttons |= BT_CHANGE;
        cmd->buttons |= nextweapon<<BT_WEAPONSHIFT;
    }
    
    // mouse
	if(usemouse)
	{
		if(mousebuttons[mousebforward])
			forward += forwardmove[speed];
		// forward double click
		if(mousebuttons[mousebforward] != dclickstate && dclicktime > 1 )
		{
			dclickstate = mousebuttons[mousebforward];
			if (dclickstate) 
				dclicks++;
			if (dclicks == 2)
			{ 
				cmd->buttons |= BT_USE; 
				dclicks = 0;
			} 
			else 
				dclicktime = 0;
		} 
		else 
		{ 
			dclicktime += ticdup;
			if (dclicktime > 20)
			{ 
				dclicks = 0; 
				dclickstate = 0; 
			} 
		}
		forward += mousey; 
		if (strafe) 
			side += mousex*2; 
		else 
			cmd->angleturn -= mousex*0x8; 
		mousex = mousey = 0;
	}// usemouse

	
	
	// 11.8.98 dlw not working FIXME
	// strafe double click
	/*bstrafe = mousebuttons[mousebstrafe] || joybuttons[joybstrafe];
	if(bstrafe != dclickstate2 && dclicktime2 > 1 )
	{ 
		dclickstate2 = bstrafe;
		if(dclickstate2) dclicks2++;
		if(dclicks2 == 2)
		{
			cmd->buttons |= BT_USE;
			dclicks2 = 0;
		}
		else
			dclicktime2 = 0;
	}
	else
	{
		dclicktime2 += ticdup;
		if(dclicktime2 > 20)
		{
			dclicks2 = 0;
			dclickstate2 = 0;
		}
	} FIXME */


	if(forward > MAXPLMOVE) forward = MAXPLMOVE; 
	else if (forward < -MAXPLMOVE) forward = -MAXPLMOVE;
	if(side > MAXPLMOVE) side = MAXPLMOVE;
	else if (side < -MAXPLMOVE)	side = -MAXPLMOVE;

    
	
	cmd->forwardmove += forward; 
    cmd->sidemove += side;
    
    // special buttons
    if(sendpause)
	{
        sendpause = false;
        cmd->buttons = BT_SPECIAL | BTS_PAUSE;
	}
	
    if(sendsave)
	{
        sendsave = false;
        cmd->buttons = BT_SPECIAL | BTS_SAVEGAME | (savegameslot << BTS_SAVESHIFT);
	}
} 
 

//
// G_DoLoadLevel 
//
extern  gamestate_t     wipegamestate; 
 
void G_DoLoadLevel(void) 
{ 
    int             i; 

    // Set the sky map.
    // First thing, we have a dummy sky texture name,
    //  a flat. The data is in the WAD only because
    //  we look for an actual index, instead of simply
    //  setting one.
    skyflatnum = R_FlatNumForName ( SKYFLATNAME );

    // DOOM determines the sky texture to be used
    // depending on the current episode, and the game version.
    if ( (gamemode == commercial) // Doom II
	 || ( gamemode == addon_tnt )
	 || ( gamemode == addon_plut ) )
    {
	skytexture = R_TextureNumForName ("SKY3");
	if (gamemap < 12)
	    skytexture = R_TextureNumForName ("SKY1");
	else if (gamemap < 21)
		skytexture = R_TextureNumForName ("SKY2");
    //WriteDebug("Sky set...\n");
    }

    levelstarttic = gametic;        // for time calculation
    
    if (wipegamestate == GS_LEVEL)
		wipegamestate = -1;             // force a wipe 

    gamestate = GS_LEVEL; 

    for (i=0 ; i<MAXPLAYERS ; i++) 
    {
	if (playeringame[i] && players[i].playerstate == PST_DEAD) 
	    players[i].playerstate = PST_REBORN; 
	memset (players[i].frags,0,sizeof(players[i].frags)); 
    } 
		 
    //WriteDebug("P_SetupLevel\n");
    P_SetupLevel(gameepisode, gamemap, 0, gameskill);    
    displayplayer = consoleplayer;		// view the guy you are playing    
    starttime = I_GetTime(); 
    gameaction = ga_nothing; 
    //WriteDebug("Z_CheckHeap\n");
    Z_CheckHeap ();
    
    // clear cmd building stuff
    memset (gamekeydown, 0, sizeof(gamekeydown)); 
    joyxmove = joyymove = 0; 
    mousex = mousey = 0; 
    sendpause = sendsave = paused = false; 
    memset (mousebuttons, 0, sizeof(mousebuttons)); 
    memset (joybuttons, 0, sizeof(joybuttons)); 
    //WriteDebug("G_DoLoadLevel done\n");
    R_FillBackScreen();

} 
 
 
//
// G_Responder  
// Get info needed to make ticcmd_ts for the players.
// 
boolean G_Responder(event_t* ev) 
{
    int i;

    // 11.7.98 another optimization mess.. redundant checking
	// 11.7.98 sort thru it if you can... original left for
	// schooling dlw
	
	
	// allow spy mode changes even during the demo
	// 11.7.98 look at gslevel below->redundant
/*    if(gamestate == GS_LEVEL && ev->type == ev_keydown && ev->data1 == KEY_F12 && (singledemo || !deathmatch))
	{
        // spy mode 
        do 
		{
            displayplayer++;
            if(displayplayer == MAXPLAYERS) displayplayer = 0;
		}while(!playeringame[displayplayer] && displayplayer != consoleplayer);
        return true;
	}
*/

    if ((ev->type == ev_keydown) && (ev->data1 == key_mvert))
	{
        // don't like this - mvert = !mvert;
        /* if (mvert == 0)
			mvert = 1;
        else
			mvert = 0; 11.7.98 don't like it either dlw */
		mvert= !mvert;
        return true;
	}
    
    // any other key pops up menu if in demos
    if(gameaction == ga_nothing && !singledemo && (demoplayback || gamestate == GS_DEMOSCREEN))
	{ 
        if(ev->type == ev_keydown || (ev->type == ev_mouse && ev->data1) || (ev->type == ev_joystick && ev->data1))
		{
            // except the console key...
            if((ev->type != ev_keydown) || (ev->data1 != KEY_CONSOLE))
			{
                M_StartControlPanel(); 
                return true; 
			}
		} 
        return false; 
	} 
	
    if(gamestate == GS_LEVEL)
	{ 
#if 0
		if (devparm && ev->type == ev_keydown && ev->data1 == ';')
		{ 
            G_DeathMatchSpawnPlayer(0); 
            return true; 
		} 
#endif
	
		if(ev->type == ev_keydown && ev->data1 == KEY_F12 && (singledemo || !deathmatch))
		{
			// spy mode 
			do 
			{
				displayplayer++;
				if(displayplayer == MAXPLAYERS) displayplayer = 0;
			}while(!playeringame[displayplayer] && displayplayer != consoleplayer);
			return true;
		}

        if(HU_Responder(ev)) return true;	// chat ate the event 
/* 11.7.98 This thing only returns false so... kill the if opt dlw
        if (ST_Responder (ev)) 
            return true;	// status window ate it */
		ST_Responder(ev);
        if(AM_Responder(ev)) return true;	// automap ate it 
	} //gamestate==GS_LEVEL
    else if(gamestate == GS_FINALE) //11.7.98 else added
	{ 
        if (F_Responder(ev)) 
            return true;	// finale ate the event 
	} 
	
    switch (ev->type) 
	{ 
	case ev_keydown: 
		if (ev->data1 == KEY_PAUSE) 
		{ 
			sendpause = true; 
			return true; 
		} 
		if (ev->data1 < NUMKEYS) 
			gamekeydown[ev->data1] = true; 
		return true;    // eat key down events 
	case ev_keyup: 
		if (ev->data1 < NUMKEYS) 
			gamekeydown[ev->data1] = false; 
		return false;   // always let key up events filter down 
	case ev_mouse: 
        i = 7;
        while( i-- ) mousebuttons[i] = ev->data1 & (1<<i);
		mousex = ev->data2*(mouseSensitivity+5)/10; 
		mousey = ev->data3*(mouseSensitivity+5)/10; 
		return true;    // eat events 
	case ev_joystick:
        i = 32;
        while( i-- ) joybuttons[i] = ev->data1 & (1<<i);
		//joybuttons[0] = ev->data1 & 1; 
		//joybuttons[1] = ev->data1 & 2; 
		//joybuttons[2] = ev->data1 & 4; 
		//joybuttons[3] = ev->data1 & 8; 
		joyxmove = ev->data2; 
		joyymove = ev->data3; 
		return true;    // eat events 
	default: 
		break; 
	} 
	
    return false; 
} 
 
 
 
//
// G_Ticker
// Make ticcmd_ts for the players.
//
void G_Ticker(void) 
{ 
    int		i;
    int		buf; 
    ticcmd_t*	cmd;
    
    /* 11.9.98 dlw speed optimized below
	// do player reborns if needed
    for(i=0 ; i<MAXPLAYERS ; i++)
		if (playeringame[i] && players[i].playerstate == PST_REBORN) 
		{
			//WriteDebug("Players being \"reborn\"\n");
			G_DoReborn(i);
		}
	*/
	for(i=0; i<doomcom->numplayers; i++)
		if(players[i].playerstate == PST_REBORN)
			G_DoReborn(i);
		

    // do things to change the game state
    while(gameaction != ga_nothing)
    { 
		switch(gameaction)
		{ 
		case ga_loadlevel:
			G_DoLoadLevel(); break;
		case ga_newgame:
			G_DoNewGame(); break;
		case ga_loadgame:
			G_DoLoadGame(); break;
		case ga_savegame:
			G_DoSaveGame(); break;
		case ga_playdemo:
			//WriteDebug("Playing demo...\n");
			if(demotype == DEMO_I) G_DoPlayDemo();
			else G_DoPlayDemo_II();
			break;
		case ga_completed:
			G_DoCompleted(); break;
		case ga_victory:
			F_StartFinale(); break;
		case ga_worlddone:
			G_DoWorldDone(); break;
		case ga_screenshot:
			M_ScreenShot();
			gameaction = ga_nothing;
			break;
		case ga_nothing: 
			break;
		}
    }
    
    // get commands, check consistancy,
    // and build new consistancy check
    buf = (gametic/ticdup)%BACKUPTICS; 

    /* 11.9.98 optimized
	for(i=0 ; i<MAXPLAYERS ; i++)
    {
	if (playeringame[i]) 
	{
	*/
	for(i=0; i<doomcom->numplayers; i++)
	{
		cmd = &players[i].cmd;
		memcpy(cmd, &netcmds[i][buf], sizeof(ticcmd_t));
		
	    if(demoplayback) 
		{
			//WriteDebug("G_ReadDemoTiccmd\n");
			G_ReadDemoTiccmd(cmd);
		}
		if(demorecording)
			G_WriteDemoTiccmd(cmd);
	    
	    // check for turbo cheats
	    if(cmd->forwardmove > TURBOTHRESHOLD
			&& !(gametic&31) && ((gametic>>5)&3) == i )
		{
			static char turbomessage[80];
			extern char *player_names[4];
			sprintf (turbomessage, "%s is turbo!",player_names[i]);
			players[consoleplayer].message = turbomessage;
		}
		if(netgame && !netdemo && !(gametic%ticdup) )
		{
			if(gametic > BACKUPTICS 
				&& consistancy[i][buf] != cmd->consistancy)
			{ 
				I_Error("consistency failure (%i should be %i)",
					cmd->consistancy, consistancy[i][buf]);
			}
			if(players[i].mo)
				consistancy[i][buf] = players[i].mo->x;
			else
				consistancy[i][buf] = rndindex;
		}
	} //end for
    //}
    
    // check for special buttons
    /* 11.9.98 dlw optimized
	for (i=0 ; i<MAXPLAYERS ; i++)
    {
	if (playeringame[i]) 
	{
	*/
	for(i=0; i<doomcom->numplayers; i++)
	{
		if(players[i].cmd.buttons & BT_SPECIAL)
		{
			switch(players[i].cmd.buttons & BT_SPECIALMASK)
			{ 
			case BTS_PAUSE:
				paused ^= 1;
				if(paused)
					S_PauseSound();
				else
					S_ResumeSound();
				break;
			case BTS_SAVEGAME:
				if(!savedescription[0])
					strcpy(savedescription, "NET GAME");
				savegameslot =  
					(players[i].cmd.buttons & BTS_SAVEMASK)>>BTS_SAVESHIFT;
				gameaction = ga_savegame;
				break;
			}
		}
	}//for
    //} original now optimized

    // do main actions
    switch(gamestate) 
    {
	case GS_LEVEL:
		//WriteDebug("P_Ticker...\n");
		P_Ticker();
		//WriteDebug("ST_Ticker...\n");
		ST_Ticker();
		//WriteDebug("AM_Ticker...\n");
		AM_Ticker();
		//WriteDebug("HU_Ticker...\n");
		HU_Ticker();
		break;
	case GS_INTERMISSION:
		//WriteDebug("WI_Ticker...\n");
		WI_Ticker ();
		break;
	case GS_FINALE:
		//WriteDebug("F_Ticker...\n");
		F_Ticker ();
		break;
	case GS_DEMOSCREEN:
		//WriteDebug("D_PageTicker...\n");
		D_PageTicker();
		break;
    }
} 
 
 
//
// PLAYER STRUCTURE FUNCTIONS
// also see P_SpawnPlayer in P_Things
//

//
// G_InitPlayer 
// Called at the start.
// Called by the game initialization functions.
//
void G_InitPlayer (int player) 
{ 
    player_t*	p; 
 
    // set up the saved info         
    p = &players[player]; 
	 
    // clear everything else to defaults 
    G_PlayerReborn (player); 
	 
} 
 
 

//
// G_PlayerFinishLevel
// Can when a player completes a level.
//
void G_PlayerFinishLevel (int player) 
{ 
    player_t*	p; 
	 
    p = &players[player]; 
	 
    memset (p->powers, 0, sizeof (p->powers)); 
    memset (p->cards, 0, sizeof (p->cards)); 
    p->mo->flags &= ~MF_SHADOW;		// cancel invisibility 
    p->extralight = 0;			// cancel gun flashes 
    p->fixedcolormap = 0;		// cancel ir gogles 
    p->damagecount = 0;			// no palette changes 
    p->bonuscount = 0; 
} 
 

//
// G_PlayerReborn
// Called after a player dies 
// almost everything is cleared and initialized 
//
void G_PlayerReborn (int player) 
{ 
    player_t*	p; 
    int		i; 
    int		frags[MAXPLAYERS]; 
    int		killcount;
    int		itemcount;
    int		secretcount; 
	 
    memcpy (frags,players[player].frags,sizeof(frags)); 
    killcount = players[player].killcount; 
    itemcount = players[player].itemcount; 
    secretcount = players[player].secretcount; 
	 
    p = &players[player]; 
    memset (p, 0, sizeof(*p)); 
 
    memcpy (players[player].frags, frags, sizeof(players[player].frags)); 
    players[player].killcount = killcount; 
    players[player].itemcount = itemcount; 
    players[player].secretcount = secretcount; 
 
    p->usedown = p->attackdown = true;	// don't do anything immediately 
    p->playerstate = PST_LIVE;       
    p->health = MAXHEALTH; 
    p->readyweapon = p->pendingweapon = wp_pistol; 
    p->weaponowned[wp_fist] = true; 
    p->weaponowned[wp_pistol] = true; 
    p->ammo[am_clip] = 50; 
	 
    for (i=0 ; i<NUMAMMO ; i++) 
	p->maxammo[i] = maxammo[i]; 
		 
}

//
// G_CheckSpot  
// Returns false if the player cannot be respawned
// at the given mapthing_t spot  
// because something is occupying it 
//
void P_SpawnPlayer (mapthing_t* mthing); 
 
boolean
G_CheckSpot
( int		playernum,
  mapthing_t*	mthing ) 
{ 
    fixed_t		x;
    fixed_t		y; 
    subsector_t*	ss; 
    unsigned		an; 
    mobj_t*		mo; 
    int			i;
	
    if (players[playernum].mo == NULL)
    {
	// first spawn of level, before corpses
	for (i=0 ; i<playernum ; i++)
       {
        if (players[i].mo != NULL)
           {
	        if (players[i].mo->x == mthing->x << FRACBITS && players[i].mo->y == mthing->y << FRACBITS)
               {
                return false;	
               }
           }
       }
	return true;
    }
		
    x = mthing->x << FRACBITS; 
    y = mthing->y << FRACBITS; 

    if (!P_CheckPosition (players[playernum].mo, x, y) ) 
	return false; 
 
    // flush an old corpse if needed 
    if (bodyqueslot >= BODYQUESIZE) 
	P_RemoveMobj (bodyque[bodyqueslot%BODYQUESIZE]); 
    bodyque[bodyqueslot%BODYQUESIZE] = players[playernum].mo; 
    bodyqueslot++; 
	
    // spawn a teleport fog 
    ss = R_PointInSubsector (x,y); 
    an = ( ANG45 * (mthing->angle/45) ) >> ANGLETOFINESHIFT; 
 
    mo = P_SpawnMobj (x+20*_finecosine(an), y+20*_finesine(an) 
		      , ss->sector->floorheight 
		      , MT_TFOG); 
	 
    if (players[consoleplayer].viewz != 1) 
	S_StartSound (mo, sfx_telept);	// don't start sound on first frame 
 
    return true; 
} 


//
// G_DeathMatchSpawnPlayer 
// Spawns a player at one of the random death match spots 
// called at level load and each death 
//
void G_DeathMatchSpawnPlayer (int playernum) 
{ 
    int             i,j; 
    int				selections; 
	 
    selections = deathmatch_p - deathmatchstarts; 
    if (selections < 4) 
       {
	    I_Error ("Only %i deathmatch spots, 4 required", selections); 
       }
 
    for (j=0 ; j<20 ; j++) 
    { 
	i = P_Random() % selections; 
	if (G_CheckSpot (playernum, &deathmatchstarts[i]) ) 
	{ 
	    deathmatchstarts[i].type = playernum+1; 
        //WriteDebug("F\n");
	    P_SpawnPlayer (&deathmatchstarts[i]); 
	    return; 
	} 
    } 
 
    // no good spot, so the player will probably get stuck 
    //WriteDebug("Y\n");
    P_SpawnPlayer (&playerstarts[playernum]); 
    //WriteDebug("Z\n");
} 

//
// G_DoReborn 
// 
void G_DoReborn (int playernum) 
{ 
    int                             i; 
	 
    if (!netgame)
    {
	// reload the level from scratch
	gameaction = ga_loadlevel;  
    }
    else 
    {
	// respawn at the start

	// first dissasociate the corpse 
	players[playernum].mo->player = NULL;   
		 
	// spawn at random spot if in death match 
	if (deathmatch) 
	{ 
	    G_DeathMatchSpawnPlayer (playernum); 
	    return; 
	} 
		 
	if (G_CheckSpot (playernum, &playerstarts[playernum]) ) 
	{ 
	    P_SpawnPlayer (&playerstarts[playernum]); 
	    return; 
	}
	
	// try to spawn at one of the other players spots 
	for (i=0 ; i<MAXPLAYERS ; i++)
	{
	    if (G_CheckSpot (playernum, &playerstarts[i]) ) 
	    { 
		playerstarts[i].type = playernum+1;	// fake as other player 
		P_SpawnPlayer (&playerstarts[i]); 
		playerstarts[i].type = i+1;		// restore 
		return; 
	    }	    
	    // he's going to be inside something.  Too bad.
	}
	P_SpawnPlayer (&playerstarts[playernum]); 
    } 
} 
 
 
void G_ScreenShot (void) 
{ 
    gameaction = ga_screenshot; 
} 
 


// DOOM Par Times
int pars[4][10] = 
{ 
    {0}, 
    {0,30,75,120,90,165,180,180,30,165}, 
    {0,90,90,90,120,90,360,240,30,170}, 
    {0,90,45,90,150,90,90,165,30,135} 
}; 

// DOOM II Par Times
int cpars[32] =
{
    30,90,120,120,90,150,120,120,270,90,	//  1-10
    210,150,150,150,210,150,420,150,210,150,	// 11-20
    240,150,180,150,150,300,330,420,300,180,	// 21-30
    120,30					// 31-32
};
 

//
// G_DoCompleted 
//
boolean		secretexit; 
extern char*	pagename; 
 
void G_ExitLevel (void) 
{ 
    secretexit = false; 
    gameaction = ga_completed; 
} 

// Here's for the german edition.
void G_SecretExitLevel (void) 
{ 
    // IF NO WOLF3D LEVELS, NO SECRET EXIT!
    if ( (gamemode == commercial)
      && (W_CheckNumForName("map31")<0))
	secretexit = false;
    else
	secretexit = true; 
    gameaction = ga_completed; 
} 
 
void G_DoCompleted (void) 
{ 
    int             i; 
	 
    gameaction = ga_nothing; 
 
    for (i=0 ; i<MAXPLAYERS ; i++) 
	if (playeringame[i]) 
	    G_PlayerFinishLevel (i);        // take away cards and stuff 
	 
    if (automapactive) 
	AM_Stop (); 
	
    if ( gamemode != commercial)
	switch(gamemap)
	{
	  case 8:
	    gameaction = ga_victory;
	    return;
	  case 9: 
	    for (i=0 ; i<MAXPLAYERS ; i++) 
		players[i].didsecret = true; 
	    break;
	}
		
//#if 0  Hmmm - why?
    if ( (gamemap == 8)
	 && (gamemode != commercial) ) 
    {
	// victory 
	gameaction = ga_victory; 
	return; 
    } 
	 
    if ( (gamemap == 9)
	 && (gamemode != commercial) ) 
    {
	// exit secret level 
	for (i=0 ; i<MAXPLAYERS ; i++) 
	    players[i].didsecret = true; 
    } 
//#endif
    
	 
    wminfo.didsecret = players[consoleplayer].didsecret; 
    wminfo.epsd = gameepisode -1; 
    wminfo.last = gamemap -1;
    
    // wminfo.next is 0 biased, unlike gamemap
    if ( gamemode == commercial)
    {
	if (secretexit)
	    switch(gamemap)
	    {
	      case 15: wminfo.next = 30; break;
	      case 31: wminfo.next = 31; break;
	    }
	else
	    switch(gamemap)
	    {
	      case 31:
	      case 32: wminfo.next = 15; break;
	      default: wminfo.next = gamemap;
	    }
    }
    else
    {
	if (secretexit) 
	    wminfo.next = 8; 	// go to secret level 
	else if (gamemap == 9) 
	{
	    // returning from secret level 
	    switch (gameepisode) 
	    { 
	      case 1: 
		wminfo.next = 3; 
		break; 
	      case 2: 
		wminfo.next = 5; 
		break; 
	      case 3: 
		wminfo.next = 6; 
		break; 
	      case 4:
		wminfo.next = 2;
		break;
	    }                
	} 
	else 
	    wminfo.next = gamemap;          // go to next level 
    }
		 
    wminfo.maxkills = totalkills; 
    wminfo.maxitems = totalitems; 
    wminfo.maxsecret = totalsecret; 
    wminfo.maxfrags = 0; 
    if ( gamemode == commercial )
	wminfo.partime = 35*cpars[gamemap-1]; 
    else
	wminfo.partime = 35*pars[gameepisode][gamemap]; 
    wminfo.pnum = consoleplayer; 
 
    for (i=0 ; i<MAXPLAYERS ; i++) 
    { 
	wminfo.plyr[i].in = playeringame[i]; 
	wminfo.plyr[i].skills = players[i].killcount; 
	wminfo.plyr[i].sitems = players[i].itemcount; 
	wminfo.plyr[i].ssecret = players[i].secretcount; 
	wminfo.plyr[i].stime = leveltime; 
	memcpy (wminfo.plyr[i].frags, players[i].frags 
		, sizeof(wminfo.plyr[i].frags)); 
    } 
 
    gamestate = GS_INTERMISSION; 
    viewactive = false; 
    automapactive = false; 
 
    if (statcopy)
	memcpy (statcopy, &wminfo, sizeof(wminfo));
	
    WI_Start (&wminfo); 
} 


//
// G_WorldDone 
//
void G_WorldDone(void) 
{ 
    gameaction = ga_worlddone; 

    if (secretexit)
		players[consoleplayer].didsecret = true; 

    if ( gamemode == commercial )
    {
		switch (gamemap)
		{
		case 15:
		case 31:
			if (!secretexit)
				break;
		case 6:
		case 11:
		case 20:
		case 30:
			F_StartFinale();
			break;
		}
    }
} 
 
void G_DoWorldDone (void) 
{        
    gamestate = GS_LEVEL; 
    gamemap = wminfo.next+1; 
    G_DoLoadLevel(); 
    gameaction = ga_nothing; 
    viewactive = true; 
} 
 


//
// G_InitFromSavegame
// Can be called by the startup code or the menu task. 
//
extern boolean setsizeneeded;
void R_ExecuteSetViewSize (void);

char	savename[256];

void G_LoadGame (char* name) 
{ 
    strcpy (savename, name); 
    gameaction = ga_loadgame; 
} 
 
#define VERSIONSIZE		16 

extern char DoomDir[128]; // msvc 5 gone mad again 10.31.98
void G_DoLoadGame (void) 
{
    int		length; 
    int		i; 
    int		a,b,c; 
    char	vcheck[VERSIONSIZE]; 
	 
    gameaction = ga_nothing; 
	 
    length = Flash_ReadFile(savename, &savebuffer); 
    save_p = savebuffer;/* + SAVESTRINGSIZE;
    
    // skip the description field 
    memset(vcheck,0,sizeof(vcheck)); 
    sprintf(vcheck,"version %i",VERSION); 
    if (strcmp (save_p, vcheck))
		return;				// bad version 
    save_p += VERSIONSIZE; 
*/			 
    gameskill = *save_p++; 
    gameepisode = *save_p++; 
    gamemap = *save_p++; 
    for (i=0 ; i<MAXPLAYERS ; i++)
		playeringame[i] = *save_p++; 

    // load a base level 
    G_InitNew (gameskill, gameepisode, gamemap);
 
    // get the times 
    a = *save_p++; 
    b = *save_p++; 
    c = *save_p++; 
    leveltime = (a<<16) + (b<<8) + c; 
	 
    // dearchive all the modifications
    P_UnArchivePlayers(); 
    P_UnArchiveWorld(); 
    P_UnArchiveThinkers(); 
    P_UnArchiveSpecials(); 
 
    if (*save_p != 0x1d)
		I_Error ("Bad savegame");
    
    // done 
    Z_Free(savebuffer); 

    if (setsizeneeded)
		R_ExecuteSetViewSize();

    // draw the pattern into the back screen
    // WriteDebug("Calling R_FileBackScreen...\n");
    R_FillBackScreen();

    // WriteDebug("Calling R_DrawViewBorder...\n");
    R_DrawViewBorder();

	// 10.31.98 dlw Save/Load Score using .ini file
	//	maintains x-compat of save/load while allowing
	//	scores to be s/l also
    if(keepscore)
	{
		for(i=0; i<VERSIONSIZE; i++) vcheck[i]=0; //no garbage
		sprintf(vcheck, "Slot%d", 0); // pad the string
		vcheck[4]=savename[7];		// slot number
		//totalscore = GetPrivateProfileInt("SCORES", vcheck, 0, DoomDir);
	}

} 
 

//
// G_SaveGame
// Called by the menu task.
// Description is a 24 byte text string 
//
void
G_SaveGame
( int	slot,
  char*	description ) 
{ 
    savegameslot = slot; 
    strcpy (savedescription, description); 
    sendsave = true; 
} 
 
void G_DoSaveGame (void) 
{ 
    char	name[100]; 
    char	name2[VERSIONSIZE]; 
    char*	description; 
    int		length; 
    int		i; 
	
    //if (M_CheckParm("-cdrom"))
		//sprintf(name,"c:\\doomdata\\"SAVEGAMENAME"%d.dsg",savegameslot);
    //else
		sprintf (name,"%s%d.dsg",SAVEGAMENAME, savegameslot); 
    description = savedescription; 
	 
    save_p = savebuffer = screens[1]+0x4000; 
	 
    /*
    memcpy (save_p, description, SAVESTRINGSIZE); 
    save_p += SAVESTRINGSIZE; 
    memset (name2,0,sizeof(name2)); 
    sprintf (name2,"version %i",VERSION); 
    memcpy (save_p, name2, VERSIONSIZE); 
    save_p += VERSIONSIZE; 
    */
	 
    *save_p++ = gameskill; 
    *save_p++ = gameepisode; 
    *save_p++ = gamemap; 
    for (i=0 ; i<MAXPLAYERS ; i++)
		*save_p++ = playeringame[i]; 
    *save_p++ = leveltime>>16; 
    *save_p++ = leveltime>>8; 
    *save_p++ = leveltime; 
 
    P_ArchivePlayers (); 
    P_ArchiveWorld (); 
    P_ArchiveThinkers (); 
    P_ArchiveSpecials (); 
	 
    *save_p++ = 0x1d;		// consistancy marker 
	 
    length = save_p - savebuffer; 
    if (length > SAVEGAMESIZE) 
	I_Error ("Savegame buffer overrun"); 
    Flash_WriteFile (name, savebuffer, length, "Doom Savegame" ); 
    gameaction = ga_nothing; 
    savedescription[0] = 0;		 
	 
    players[consoleplayer].message = GGSAVED; 

    // draw the pattern into the back screen
    R_FillBackScreen();
	

	// 10.31.98 dlw Save/Load Score using .ini file
	//	maintains x-compat of save/load while allowing
	//	scores to be s/l also
	for(i=0; i<VERSIONSIZE; i++) name2[i]=0; //no garbage
	for(i=0; i<100; i++) name[i]=0;			//no garbage
	sprintf(name2, "Slot%d", savegameslot); //get position
    if(keepscore)  //if keeping score write the score
	{
		sprintf(name, "%d", totalscore);
		//WritePrivateProfileString("SCORES", name2, name, DoomDir);
	}
	else			//otherwise zero it out
	{
		sprintf(name, "%d", 0);
		//WritePrivateProfileString("SCORES", name2, name, DoomDir);
	}


} 
 

//
// G_InitNew
// Can be called by the startup code or the menu task,
// consoleplayer, displayplayer, playeringame[] should be set. 
//
skill_t	d_skill; 
int     d_episode; 
int     d_map; 
 
void
G_DeferedInitNew
( skill_t	skill,
  int		episode,
  int		map) 
{ 
    d_skill = skill; 
    d_episode = episode; 
    d_map = map; 
    gameaction = ga_newgame; 
} 


void G_DoNewGame (void) 
{
    demoplayback = false; 
    netdemo = false;
    netgame = false;
    deathmatch = false;
    playeringame[1] = playeringame[2] = playeringame[3] = 0;
    respawnparm = false;
    fastparm = false;
    nomonsters = false;
    consoleplayer = 0;
    G_InitNew (d_skill, d_episode, d_map); 
    gameaction = ga_nothing; 
} 

// The sky texture to be used instead of the F_SKY1 dummy.
extern  int	skytexture; 


void
G_InitNew
( skill_t	skill,
  int		episode,
  int		map ) 
{ 
    int             i; 
	 
    if (paused)
    { 
		paused = false; 
		S_ResumeSound(); 
    }	

    if(skill > sk_nightmare) skill = sk_nightmare;


    // This was quite messy with SPECIAL and commented parts.
    // Supposedly hacks to make the latest edition work.
    // It might not work properly.
    if(episode < 1) episode = 1; 

    if( gamemode == retail )
    {
		if (episode > 4) episode = 4;
    }
    else if( gamemode == shareware )
    {
		if (episode > 1) 
			episode = 1;	// only start episode 1 on shareware
    }  
    else
    {
		if (episode > 3) episode = 3;
    }
    

  
    if(map < 1)	map = 1;
    
    if ( (map > 9) && ( gamemode != commercial) ) map = 9; 
		 
    //WriteDebug("M_ClearRandom\n");
    M_ClearRandom(); 
	 
    if (skill == sk_nightmare || respawnparm )
		respawnmonsters = true;
    else
		respawnmonsters = false;
		
    if (fastparm || (skill == sk_nightmare && gameskill != sk_nightmare) )
    { 
		for (i=S_SARG_RUN1 ; i<=S_SARG_PAIN2 ; i++) 
			states[i].tics >>= 1; 
		mobjinfo[MT_BRUISERSHOT].speed = 20*FRACUNIT;
		mobjinfo[MT_HEADSHOT].speed = 20*FRACUNIT;
		mobjinfo[MT_TROOPSHOT].speed = 20*FRACUNIT;
    } 
    else if (skill != sk_nightmare && gameskill == sk_nightmare)
    { 
		for (i=S_SARG_RUN1 ; i<=S_SARG_PAIN2 ; i++)
			states[i].tics <<= 1;
		mobjinfo[MT_BRUISERSHOT].speed = 15*FRACUNIT;
		mobjinfo[MT_HEADSHOT].speed = 10*FRACUNIT;
		mobjinfo[MT_TROOPSHOT].speed = 10*FRACUNIT;
    } 
	 
			 
    // force players to be initialized upon first level load         
    for (i=0 ; i<MAXPLAYERS ; i++) 
		players[i].playerstate = PST_REBORN; 
 
    usergame = true;            // will be set false if a demo 
    paused = false; 
    demoplayback = false; 
    automapactive = false; 
    viewactive = true; 
    gameepisode = episode; 
    gamemap = map; 
    gameskill = skill; 
 
    viewactive = true;
    
    // set the sky map for the episode
    if( gamemode == commercial )
    {
		skytexture = R_TextureNumForName ("SKY3");
		if(gamemap < 12)
			skytexture = R_TextureNumForName ("SKY1");
		else
			if (gamemap < 21)
				skytexture = R_TextureNumForName ("SKY2");
    }
    else
		switch(episode) 
	{
		case 1:
			skytexture = R_TextureNumForName ("SKY1"); break;
		case 2: skytexture = R_TextureNumForName ("SKY2"); break;
		case 3: skytexture = R_TextureNumForName ("SKY3"); break;
		case 4:	// Special Edition sky
			skytexture = R_TextureNumForName ("SKY4"); break;
	} 
 
    //WriteDebug("G_DoLoadLevel\n");
    setsizeneeded = TRUE;
    G_DoLoadLevel(); 
} 
 

//
// DEMO RECORDING 
// 
#define DEMOMARKER		0x80


void G_ReadDemoTiccmd (ticcmd_t* cmd) 
{ 
    if (*demo_p == DEMOMARKER) 
    {
	// end of demo data stream 
	G_CheckDemoStatus (); 
	return; 
    } 
    cmd->forwardmove = ((signed char)*demo_p++); 
    cmd->sidemove = ((signed char)*demo_p++); 
    cmd->angleturn = ((unsigned char)*demo_p++)<<8; 
    cmd->buttons = (unsigned char)*demo_p++; 
} 


void G_WriteDemoTiccmd (ticcmd_t* cmd) 
{ 
    if (gamekeydown[KEY_Q])           // press q to end demo recording 
	G_CheckDemoStatus (); 
    *demo_p++ = cmd->forwardmove; 
    *demo_p++ = cmd->sidemove; 
    *demo_p++ = (cmd->angleturn+128)>>8; 
    *demo_p++ = cmd->buttons; 
    demo_p -= 4; 
    if (demo_p > demoend - 16)
    {
	// no more space 
	G_CheckDemoStatus (); 
	return; 
    } 
	
    G_ReadDemoTiccmd (cmd);         // make SURE it is exactly the same 
} 
 
 
 
//
// G_RecordDemo 
// 
void G_RecordDemo (char* name) 
{ 
    int             i; 
    int				maxsize;

    usergame = false; 
    strcpy (demoname, name); 
    strcat (demoname, ".lmp"); 
    sprintf(MsgText, "Record demo : %s\n", demoname);
    WriteDebug(MsgText);
    maxsize = 0x20000;
    i = M_CheckParm ("-maxdemo");
    if (i && i<myargc-1)
	maxsize = atoi(myargv[i+1])*1024;
    demobuffer = Z_Malloc (maxsize,PU_STATIC,NULL);
    demoend = demobuffer + maxsize;
	
    demotype = DEMO_I;

    demorecording = true; 
} 

//
// New Demo Recording stuff...
// 
// Doom demos assume that the demo starts at the
// beginning of a level and that the normal level
// state will apply - any deviation from that
// and playback will be out of "sync".  Synchronization
// information must be written out to the demo file
// so that the state of the entire game is saved
// Probably it should use the save game function to
// save the game state then save the demo data after
// it... A new extension of "DEM" should also be used.
//
// G_RecordDemo_II
// 
void G_RecordDemo_II (char* name) 
{ 
    int             i; 
    int				maxsize;

    usergame = false; 
    strcpy (demoname, name); 
    strcat (demoname, ".dem"); 
    sprintf(MsgText, "Record demo II : %s\n", demoname);
    WriteDebug(MsgText);
    maxsize = 0x20000;
    i = M_CheckParm ("-maxdemo");
    if (i && i < myargc-1)
	    maxsize = atoi(myargv[i+1])*1024;
    demobuffer = Z_Malloc (maxsize,PU_STATIC,NULL);
    demoend = demobuffer + maxsize;
	
    demotype = DEMO_II;

    demorecording = true; 
} 
 
void G_BeginRecording_II (void) 
   { 
    char	name2[VERSIONSIZE]; 
    char    description[] = "WINDOOM: DEMO VERSION II";
    int		length; 
    int		i; 
	
    save_p = demobuffer;
	 
    memcpy (save_p, description, SAVESTRINGSIZE);
    save_p += SAVESTRINGSIZE; 
    memset (name2,0,sizeof(name2)); 
    sprintf (name2,"version %i",VERSION); 
    memcpy (save_p, name2, VERSIONSIZE); 
    save_p += VERSIONSIZE; 
	 
    *save_p++ = gameskill;
    *save_p++ = gameepisode;
    *save_p++ = gamemap;
    for (i = 0; i < MAXPLAYERS; i++)
	    *save_p++ = playeringame[i];

    *save_p++ = deathmatch;
    *save_p++ = respawnparm;
    *save_p++ = fastparm;
    *save_p++ = nomonsters;
    *save_p++ = consoleplayer;
	 
    *save_p++ = leveltime >> 16;
    *save_p++ = leveltime >> 8;
    *save_p++ = leveltime;
 
    P_ArchivePlayers();
    P_ArchiveWorld();
    P_ArchiveThinkers();
    P_ArchiveSpecials();
	 
    *save_p++ = 0x1d;		// consistancy marker 
	 
    length = save_p - demobuffer;
    if (length > SAVEGAMESIZE) 
	    I_Error ("Savegame buffer overrun"); 
    M_WriteFile (demoname, demobuffer, length);

    gameaction = ga_nothing;
	 
    demo_p = demobuffer;
	
//    *demo_p++ = VERSION;
//    *demo_p++ = gameskill; 
//    *demo_p++ = gameepisode; 
//    *demo_p++ = gamemap; 
/*
    *demo_p++ = deathmatch;
    *demo_p++ = respawnparm;
    *demo_p++ = fastparm;
    *demo_p++ = nomonsters;
    *demo_p++ = consoleplayer;
*/
//    for (i = 0; i < MAXPLAYERS; i++) 
//       {
//	    *demo_p++ = playeringame[i];
//       }

    // draw the pattern into the back screen
    R_FillBackScreen ();
   } 
 
 
void G_BeginRecording (void) 
{ 
    int             i; 
		
    demo_p = demobuffer;
	
    *demo_p++ = VERSION;
    *demo_p++ = gameskill; 
    *demo_p++ = gameepisode; 
    *demo_p++ = gamemap; 
    *demo_p++ = deathmatch; 
    *demo_p++ = respawnparm;
    *demo_p++ = fastparm;
    *demo_p++ = nomonsters;
    *demo_p++ = consoleplayer;
	 
    for (i=0 ; i<MAXPLAYERS ; i++) 
	*demo_p++ = playeringame[i]; 		 

    demotype = DEMO_I;

} 
 

//
// G_PlayDemo 
//

int access( const char *path, int mode );

char*	defdemoname; 
 
boolean G_DeferedPlayDemo_II (char* name)
   { 
    static char demofilename[128];
    sprintf(demofilename, "%s.dem", name);
    if (access(demofilename, 0) != 0)
        return false;
    sprintf(MsgText, "-playdemo2: %s\n", demofilename);
    WriteDebug(MsgText);
    defdemoname = demofilename;
    gameaction = ga_playdemo;
    demotype = DEMO_II;
    return true;
} 
 
void G_DoPlayDemo_II(void)
{ 
    int		length; 
    int		i; 
    int		a,b,c; 
    char	vcheck[VERSIONSIZE];

	//everything below (comments) by others - dlw
	// commented these to get rid of comp warning
    //skill_t skill; 
    //int     episode, map, dversion, tversion;

    demotype = DEMO_II;

    gameaction = ga_nothing;
	
    sprintf(MsgText, "Playing demo II : %s\n", defdemoname);
    WriteDebug(MsgText);
    length = M_GetFileSize(defdemoname);
    demobuffer = (unsigned char *)malloc(length);
    demoend = demobuffer + length;

    length = M_ReadFile(defdemoname, &demobuffer);
    save_p = demobuffer + SAVESTRINGSIZE;
    
    // skip the description field 
    memset (vcheck,0,sizeof(vcheck)); 
    sprintf (vcheck,"version %i",VERSION); 
    if (strcmp (save_p, vcheck)) 
        return;				// bad version 
    save_p += VERSIONSIZE; 
			 
    gameskill = *save_p++;
    gameepisode = *save_p++;
    gamemap = *save_p++;
    for (i = 0; i < MAXPLAYERS; i++)
       playeringame[i] = *save_p++; 

    deathmatch = *save_p++;
    respawnparm = *save_p++;
    fastparm = *save_p++;
    nomonsters = *save_p++;
    consoleplayer = *save_p++;
	
//    for (i=0 ; i<MAXPLAYERS ; i++)
//       playeringame[i] = *demo_p++;
    if (playeringame[1]) 
    { 
	netgame = true; 
	netdemo = true; 
    }

    // load a base level 
    G_InitNew (gameskill, gameepisode, gamemap);
 
    // get the times 
    a = *save_p++;
    b = *save_p++;
    c = *save_p++;
    leveltime = (a << 16) + (b << 8) + c;
	 
    // dearchive all the modifications
    P_UnArchivePlayers (); 
    P_UnArchiveWorld (); 
    P_UnArchiveThinkers (); 
    P_UnArchiveSpecials (); 
 
    if (*save_p++ != 0x1d) 
	    I_Error ("Bad savegame");
    
    // done 
//    Z_Free (savebuffer);

    if (setsizeneeded)
	    R_ExecuteSetViewSize();

    // draw the pattern into the back screen
    // WriteDebug("Calling R_FillBackScreen...\n");
    R_FillBackScreen();

    // WriteDebug("Calling R_DrawViewBorder...\n");
    R_DrawViewBorder();

//    tversion = VERSION;
//    gameaction = ga_nothing; 
//    demobuffer = demo_p = W_CacheLumpName(defdemoname, PU_STATIC);
//    if (demobuffer == NULL)
//       {
//        sprintf(MsgText,"Demo %s is not in the WAD...\n", defdemoname);
//        WriteDebug(MsgText);
//        gameaction = ga_nothing;
//        return;
//       }

    demo_p = save_p;
/*

    dversion = *demo_p;
    if ( *demo_p++ != tversion)
    {
      sprintf(MsgText, "Demo version : %d.%d Game version : %d.%d\n",
              dversion/100, dversion %100, VERSION/100, VERSION%100);
      WriteDebug(MsgText);
      gameaction = ga_nothing;
      return;
    }
*/

//    skill = *demo_p++;
//    episode = *demo_p++;
//    map = *demo_p++;
/*
    deathmatch = *demo_p++;
    respawnparm = *demo_p++;
    fastparm = *demo_p++;
    nomonsters = *demo_p++;
    consoleplayer = *demo_p++;
//    for (i=0 ; i<MAXPLAYERS ; i++)
//       playeringame[i] = *demo_p++;
    if (playeringame[1]) 
    { 
	netgame = true; 
	netdemo = true; 
    }
    // don't spend a lot of time in loadlevel 
//    precache = false;
//    G_InitNew (skill, episode, map); 
//    precache = true; 
*/

    usergame = false;
    demoplayback = true;
} 

void G_DeferedPlayDemo (char* name) 
{ 
    sprintf(MsgText, "-playdemo: %s\n", name);
    WriteDebug(MsgText);
    defdemoname = name;
    gameaction = ga_playdemo;
    demotype = DEMO_I;
} 
 
void G_DoPlayDemo (void) 
{ 
    skill_t skill; 
    int             i, episode, map, dversion, tversion;
	 
    demotype = DEMO_I;

    tversion = VERSION;
    gameaction = ga_nothing; 
    demobuffer = demo_p = W_CacheLumpName(defdemoname, PU_STATIC);
    if (demobuffer == NULL)
       {
        sprintf(MsgText,"Demo %s is not in the WAD...\n", defdemoname);
        WriteDebug(MsgText);
        gameaction = ga_nothing;
        return;
       }

    dversion = *demo_p;
    if ( *demo_p++ != tversion)
    {
      sprintf(MsgText, "Demo version : %d.%d Game version : %d.%d\n",
              dversion/100, dversion %100, VERSION/100, VERSION%100);
      WriteDebug(MsgText);
      gameaction = ga_nothing;
      return;
    }
    skill = *demo_p++; 
    episode = *demo_p++; 
    map = *demo_p++; 
    deathmatch = *demo_p++;
    respawnparm = *demo_p++;
    fastparm = *demo_p++;
    nomonsters = *demo_p++;
    consoleplayer = *demo_p++;
	
    for (i=0 ; i<MAXPLAYERS ; i++) 
	playeringame[i] = *demo_p++; 
    if (playeringame[1]) 
    { 
	netgame = true; 
	netdemo = true; 
    }

    // don't spend a lot of time in loadlevel 
    precache = false;
    G_InitNew (skill, episode, map); 
    precache = true; 

    usergame = false; 
    demoplayback = true; 
} 

//
// G_TimeDemo 
//
boolean G_TimeDemo_II(char* name) 
{ 	 
    static char demofilename[128];
    sprintf(demofilename, "%s.dem", name);
    if (access(demofilename, 0) != 0)
        return false;
    nodrawers = M_CheckParm ("-nodraw"); 
    noblit = M_CheckParm ("-noblit"); 
    timingdemo = true; 
    singletics = true; 

    defdemoname = demofilename;
    gameaction = ga_playdemo; 
    demotype = DEMO_II;
    sprintf(MsgText, "Playing timedemo II %s -noblit %d -nodraw %d\n", name, noblit, nodrawers);
    WriteDebug(MsgText);
    return true;
} 
 
//
// G_TimeDemo 
//
void G_TimeDemo(char* name) 
{ 	 
    nodrawers = M_CheckParm("-nodraw"); 
    noblit = M_CheckParm("-noblit"); 
    timingdemo = true; 
    singletics = true; 

    defdemoname = name; 
    gameaction = ga_playdemo; 
    sprintf(MsgText, "Playing timedemo %s -noblit %d -nodraw %d\n", name, noblit, nodrawers);
    WriteDebug(MsgText);
} 
 
 
/* 
=================== 
= 
= G_CheckDemoStatus 
= 
= Called after a death or level completion to allow demos to be cleaned up 
= Returns true if a new demo loop action will take place 
=================== 
*/ 
 
boolean G_CheckDemoStatus (void) 
{ 
    int             endtime; 
	 
    WriteDebug("G_CheckDemoStatus...\n");
    if (timingdemo) 
    { 
	endtime = I_GetTime (); 
    I_Error ("timed %i gametics in %i realtics : %d FPS" ,gametic, endtime-starttime, (gametic*TICRATE)/(endtime-starttime)); 
    } 
	 
    if (demoplayback) 
    { 
	if (singledemo) 
	    I_Quit (); 
			 
	Z_ChangeTag (demobuffer, PU_CACHE); 
	demoplayback = false; 
	netdemo = false;
	netgame = false;
	deathmatch = false;
	playeringame[1] = playeringame[2] = playeringame[3] = 0;
	respawnparm = false;
	fastparm = false;
	nomonsters = false;
	consoleplayer = 0;
	D_AdvanceDemo (); 
	return true; 
    } 
 
    if (demorecording) 
    { 
     G_EndDemo();
	I_Error ("Demo %s recorded",demoname); 
    } 
	 
    return false; 
} 
 

void G_EndDemo_II()
   {
	*demo_p++ = DEMOMARKER; 
	M_AppendFile(demoname, demobuffer, demo_p - demobuffer);
	Z_Free (demobuffer);
	demorecording = false;
   }
 
void G_EndDemo()
   {
	*demo_p++ = DEMOMARKER; 
	M_WriteFile (demoname, demobuffer, demo_p - demobuffer); 
	Z_Free (demobuffer); 
	demorecording = false; 
   }
 
