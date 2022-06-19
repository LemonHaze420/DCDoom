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
// DESCRIPTION:
//	System interface for sound.
//
//-----------------------------------------------------------------------------
#include "z_zone.h"

#include "i_system.h"
#include "i_sound.h"
//#include "i_windoz.h"
#include "m_argv.h"
#include "m_misc.h"
#include "w_wad.h"

#include "doomdef.h"
#include "doomstat.h"

#include <mmsystem.h>
#include <dsound.h>


extern HWND      hMainWnd;


#define SAFE_RELEASE(p) if(p) { p->lpVtbl->Release(p); p = NULL; }


// The number of internal mixing channels,
//  the samples calculated for each mixing step,
//  the size of the 16bit, 2 hardware channel (stereo)
//  mixing buffer, and the samplerate of the raw data.

// Needed for calling the actual sound output.
#define NUM_CHANNELS		128

LPDIRECTSOUND		pDS=NULL;
LPDIRECTSOUNDBUFFER	pDSBPrimary=NULL;
int			HandleCount=1;
WAVEFORMATEX		SampleFormat;

// The actual lengths of all sound effects.
int			SoundLengths[NUMSFX];
boolean	HighSound;

// The sound in channel handles,
//  determined on registration,
//  might be used to unregister/stop/modify,
//  currently unused.
int 		channelhandles[NUM_CHANNELS];

// SFX id of the playing sound effect.
// Used to catch duplicates (like chainsaw).
int		channelids[NUM_CHANNELS];

//actual data buffers
LPDIRECTSOUNDBUFFER	ChannelBuffers[NUM_CHANNELS];
boolean		ChannelActive[NUM_CHANNELS];
//
// This function loads the sound data from the WAD lump,
//  for single sound.
//
void CacheSFX(int sfxid)
{
    char                name[20];
    sfxinfo_t		*sfx;


    sfx=&S_sfx[sfxid];
    if (sfx->data)
		return;
    // Get the sound data from the WAD, allocate lump
    //  in zone memory.
    sprintf(name, "ds%s", sfx->name);

    // Now, there is a severe problem with the
    //  sound handling, in it is not (yet/anymore)
    //  gamemode aware. That means, sounds from
    //  DOOM II will be requested even with DOOM
    //  shareware.
    // The sound list is wired into sounds.c,
    //  which sets the external variable.
    // I do not do runtime patches to that
    //  variable. Instead, we will use a
    //  default sound for replacement.
    if ( W_CheckNumForName(name) == -1 )
		sfx->lumpnum = W_GetNumForName("dspistol");
    else
		sfx->lumpnum = W_GetNumForName(name);

    SoundLengths[sfxid] = W_LumpLength(sfx->lumpnum);

    sfx->data = W_CacheLumpNum( sfx->lumpnum, PU_STATIC );
}




/*
// Play these sound effects only one at a time.
if ( sfxid == sfx_sawup
|| sfxid == sfx_sawidl
|| sfxid == sfx_sawful
|| sfxid == sfx_sawhit
|| sfxid == sfx_stnmov
|| sfxid == sfx_pistol	 )
*/


//
// SFX API
// Note: this was called by S_Init.
// However, whatever they did in the
// old DPMS based DOS version, this
// were simply dummies in the Linux
// version.
// See soundserver initdata().
//
void I_SetChannels()
{
}


void I_SetSfxVolume(int volume)
{
	// Identical to DOS.
	// Basically, this should propagate
	//  the menu/config file setting
	//  to the state variable used in
	//  the mixing.
	snd_SfxVolume = volume;
}

boolean I_ChannelPlaying(int channel)
{
    LPDIRECTSOUNDBUFFER	dsb;
    DWORD		status;

	if (!pDS)
		return(false);
    dsb=ChannelBuffers[channel];
    if (!dsb)
		return(false);
    if (!ChannelActive[channel])
		return(false);
    dsb->lpVtbl->GetStatus(dsb, &status);
    if (status&DSBSTATUS_PLAYING)
		return(true);
    ChannelActive[channel]=false;
    return(false);
}

void I_KillChannel(int channel)
{
	LPDIRECTSOUNDBUFFER	*pdsb;

	if (!pDS)
		return;
    pdsb=&ChannelBuffers[channel];
    if (*pdsb)
    {
		(*pdsb)->lpVtbl->Stop(*pdsb);
		(*pdsb)->lpVtbl->Release(*pdsb);
		*pdsb=NULL;
    }
}

int I_RestartChannel(int channel, int volume)
{
    LPDIRECTSOUNDBUFFER	dsb;

	if (!pDS)
		return(HandleCount++);
    ChannelActive[channel]=true;
    dsb=ChannelBuffers[channel];
    if (!dsb)
		I_Error("Restarting dead sound");
    dsb->lpVtbl->Stop(dsb);
    dsb->lpVtbl->SetCurrentPosition(dsb, 0);
    dsb->lpVtbl->SetVolume(dsb, DSBVOLUME_MIN+(((DSBVOLUME_MAX-DSBVOLUME_MIN)*(volume+1))>>4));
    dsb->lpVtbl->Play(dsb, 0, 0, 0);
    channelhandles[channel]=HandleCount;
    return(HandleCount++);
}

//
// Starting a sound means adding it
//  to the current list of active sounds
//  in the internal channels.
// As the SFX info struct contains
//  e.g. a pointer to the raw data,
//  it is ignored.
// As our sound handling does not handle
//  priority, it is ignored.
// Pitching (that is, increased speed of playback)
//  is set, but currently not used by mixing.
//
int I_StartSound
( int		id,
 int		vol,
 int		sep,//pan, 0..255
 int		pitch,
 int		priority )
{
    int			channel;
    LPDIRECTSOUNDBUFFER	dsb;
    HRESULT		hres;
    DSBUFFERDESC	dsbd;
    int			oldchannel;
    int			oldhandle;
    int			freechannel;
    void		*p;
    DWORD		s;

	if (!pDS)
		return(HandleCount++);

    oldhandle=0;
    oldchannel=0;
    freechannel=NUM_CHANNELS;
    for (channel=0;channel<NUM_CHANNELS;channel++)
    {
		if (ChannelBuffers[channel])
		{
			if ((channelids[channel]==id)&&!I_ChannelPlaying(channel))
				return (I_RestartChannel(channel, vol));
			if (HandleCount-channelhandles[channel]>oldhandle)
			{
				oldhandle=HandleCount-channelhandles[channel];
				oldchannel=channel;
			}
		}
		else
			freechannel=channel;
    }

    if (freechannel != NUM_CHANNELS )
		channel=freechannel;
    else
		channel=oldchannel;

    I_KillChannel( channel );

    CacheSFX(id);

    memset(&dsbd, 0, sizeof(DSBUFFERDESC));
    dsbd.dwSize=sizeof(DSBUFFERDESC);
    dsbd.dwFlags=DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLFREQUENCY|DSBCAPS_CTRLPAN|DSBCAPS_GETCURRENTPOSITION2|DSBCAPS_STATIC;
    dsbd.dwBufferBytes=SoundLengths[id];
    dsbd.lpwfxFormat=&SampleFormat;

    hres=pDS->lpVtbl->CreateSoundBuffer(pDS, &dsbd, &dsb, NULL);
    if (hres!=DS_OK) I_Error("CreateSoundBuffer Failed");

    hres=dsb->lpVtbl->Lock(dsb, 0, SoundLengths[id]-8, &p, &s, NULL, NULL, 0);
    if (hres!=DS_OK) I_Error("SoundBuffer::Lock Failed");

    memcpy(p, (byte *)S_sfx[id].data+8, s);

    hres=dsb->lpVtbl->Unlock(dsb, p, s, NULL, 0);
    if (hres!=DS_OK) I_Error("SoundBuffer::Unlock Failed");

    ChannelBuffers[channel]=dsb;
    channelids[channel]=id;
    return (I_RestartChannel(channel, vol));
}



void I_StopSound (int handle)
{
    int		channel;

	if (!pDS)
		return;
    for (channel=0;channel<NUM_CHANNELS;channel++)
    {
		if (I_ChannelPlaying(channel)&&(channelhandles[channel]==handle))
		{
			ChannelBuffers[channel]->lpVtbl->Stop(ChannelBuffers[channel]);
			ChannelActive[channel]=false;
		}
    }
}


int I_SoundIsPlaying(int handle)
{
    int		channel;

	if (!pDS)
		return(false);

    for (channel=0;channel<NUM_CHANNELS;channel++)
    {
		if ((channelhandles[channel]==handle)&&I_ChannelPlaying(channel))
			return(true);
    }
    return(false);
}



//
// to mix the sounds into buffers, called every frame
//
void I_ProcessSound(void)
{
}

void
I_UpdateSoundParams
( int	handle,
 int	vol,
 int	sep,
 int	pitch)
{
	// I fail too see that this is used.
	// Would be using the handle to identify
	//  on which channel the sound might be active,
	//  and resetting the channel parameters.

}




void I_ShutdownSound(void)
{
    int		i;

    if (pDS)
    {
		for (i=0;i<NUM_CHANNELS;i++)
			I_KillChannel(i);
    }
    SAFE_RELEASE(pDSBPrimary);
    SAFE_RELEASE(pDS);
}



void I_InitSound(void)
{
    HRESULT			hres;
    DSBUFFERDESC	dsbd;
    int				i;

	if (M_CheckParm("-nosound"))
		return;
    hres=DirectSoundCreate(NULL, &pDS, NULL);
    if (hres!=DS_OK)
	{
		pDS=NULL;
		I_Error("DirectSoundCreate Failed\n");
		return;
	}
    hres=pDS->lpVtbl->SetCooperativeLevel(pDS, hMainWnd, DSSCL_PRIORITY);
    if (hres!=DS_OK)
		I_Error("DirectSound::SetCooperativeLevel Failed");
    SampleFormat.wFormatTag=WAVE_FORMAT_PCM;
    SampleFormat.nChannels=1;
    SampleFormat.nSamplesPerSec=11025;
	SampleFormat.cbSize=0;
	if (HighSound)
	{
	    SampleFormat.nBlockAlign=2;
	    SampleFormat.nAvgBytesPerSec=22050;
	    SampleFormat.wBitsPerSample=16;
	}
	else
	{
	    SampleFormat.nBlockAlign=1;
	    SampleFormat.nAvgBytesPerSec=11025;
	    SampleFormat.wBitsPerSample=8;
	}
    memset(&dsbd, 0, sizeof(DSBUFFERDESC));
    dsbd.dwSize=sizeof(DSBUFFERDESC);
    dsbd.dwFlags=DSBCAPS_PRIMARYBUFFER;
    dsbd.dwBufferBytes=0;
    dsbd.lpwfxFormat=NULL;
    hres=pDS->lpVtbl->CreateSoundBuffer(pDS, &dsbd, &pDSBPrimary, NULL);
    if (hres!=DS_OK)
	{
		I_Error("I_InitSound: Unable to access primary sound buffer");
		pDSBPrimary=NULL;
	}
	else
	{
	    hres=pDSBPrimary->lpVtbl->SetFormat(pDSBPrimary, &SampleFormat);
	    if (hres!=DS_OK)
			I_Error("I_InitSound: Unable to set primary sound buffer format\n");
		pDSBPrimary->lpVtbl->Play(pDSBPrimary, 0, 0, DSBPLAY_LOOPING);
	}
	for (i=0;i<NUM_CHANNELS;i++)
		ChannelBuffers[i]=NULL;
    for (i=0;i<NUMSFX;i++)
		S_sfx[i].data=NULL;
    SampleFormat.wFormatTag=WAVE_FORMAT_PCM;
    SampleFormat.nChannels=1;
    SampleFormat.nSamplesPerSec=11025;
    SampleFormat.nBlockAlign=1;
    SampleFormat.nAvgBytesPerSec=11025;
    SampleFormat.wBitsPerSample=8;
	SampleFormat.cbSize=0;
}
