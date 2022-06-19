//I_Music.c
//Doom music stuff
#include "z_zone.h"

#define MAX_MIDI_EVENTS 2048

#include "i_system.h"
#include "i_sound.h"
#include "i_music.h"
#include "m_argv.h"
#include "m_misc.h"
#include "m_swap.h"
#include "w_wad.h"

#include "doomdef.h"
#include "doomstat.h"
//#include "d_stuff.h"

#include <stdlib.h>

#include <mmsystem.h>

HMIDISTRM       hMidiStream=NULL;

MIDIHDR mhTonebank, mhTonebankDrum;
BYTE      *pbTonebankNew     = NULL;                     // Pointers to new copies of data used
BYTE      *pbTonebankDrumNew = NULL;                     // Pointers to new copies of data used
HMIDIOUT  hmo, hmoDrum;                                  // MIDI device handles
MIDIPROPTIMEDIV mptd;                                    // Timing variables
MIDIPROPTEMPO   mpt;                                     // Timing variables
WORD      td;                                            // Time division variables


#define MIDI_BLOCK_SIZE 2048
#define MAX_BLOCKS 1

typedef struct
{
	DWORD	time;
	DWORD	ID;
	byte	data[3];
	byte	type;
}MidiEvent_t;

typedef struct
{
	DWORD	ID;          // identifier "MUS" 0x1A
	WORD	scoreLen;
	WORD	scoreStart;
	WORD	channels;	// count of primary channels
	WORD	sec_channels;	// count of secondary channels
	WORD	instrCnt;
	WORD	dummy;
}musheader_t;

typedef struct
{
	int			numevents;
	int			nextevent;
	MidiEvent_t	*midievents;
	MIDIHDR		header[2];
}songinfo_t;

byte		MidiControlers[10]={0, 0, 1, 7, 10, 11, 91, 93, 64, 67};
boolean	started=false;

songinfo_t		*CurrentSong=NULL;
boolean		loopsong=false;

byte XLateMUSControl(byte control)
{
	switch (control)
	{
	case 10:
		return(120);
	case 11:
		return(123);
	case 12:
		return(126);
	case 13:
		return(127);
	case 14:
		return(121);
	}
	I_Error("Unknown control %d", control);
	return(0);
}

static int GetSongLength(byte *data)
{
	boolean	done;
	int			events;
	musheader_t	*header;
	boolean	time;

	header=(musheader_t *)data;
	data+=header->scoreStart;
	events=0;
	done=false;
	time=false;
	while (!done)
	{
		if (*data&0x80)
			time=true;
		switch((*(data++)>>4)&7)
		{
		case 1:
			if (*(data++)&0x80)
				data++;
			break;
		case 0:
		case 2:
		case 3:
			data++;
			break;
		case 4:
			data+=2;
			break;
		default:
			done=true;
			break;
		}
		events++;
		if (time)
		{
			while (*data&0x80)
				data++;
			data++;
			time=false;
		}
	}
	return(events+2);
}

static void Mus2Midi(byte *MusData, MidiEvent_t *MidiEvents)
{
	musheader_t	*header;
	byte		*score;
	int			spos;
	MidiEvent_t	*event;
	int			channel;
	int			etype;
	int			delta;
	int			finished;
	byte		channelvol[16];
	int			count;

	count=GetSongLength(MusData);
	header=(musheader_t *)MusData;
	if (header->ID!=0x1A53554D)//"MUS"<EOF>
		I_Error("Not a MUS file");
	score=(byte *)&MusData[header->scoreStart];
	event=MidiEvents;
	/*event->time=0;
	event->ID=0;
	event->type=MEVT_TEMPO;
	event->data[0]=0x00;
	event->data[1]=0x80;//not sure how to work this out, should be 140bpm
	event->data[2]=0x02;//but it's guessed so it sounds about right
	event++;

	event->time=0;
	event->ID=0;
	event->type=MEVT_TEMPO;
	event->data[0]=0x00;
	event->data[1]=0x80;//not sure how to work this out, should be 140bpm
	event->data[2]=0x02;//but it's guessed so it sounds about right
	event++;
    */

	delta=0;
	spos=0;

	finished=false;
	while (true)
	{
		event->time=delta;
		delta=0;
		event->ID=0;
		etype=(score[spos]>>4)&7;
		event->type=MEVT_SHORTMSG;
		channel=score[spos]&15;
		if (channel==9)
			channel=15;
		else if (channel==15)
			channel=9;
		if (score[spos]&0x80)
			delta=-1;
		spos++;
		switch(etype)
		{
		case 0:
			event->data[0]=channel|0x80;
			event->data[1]=score[spos++];
			event->data[2]=channelvol[channel];
			break;
		case 1:
			event->data[0]=channel|0x90;
			event->data[1]=score[spos]&127;
			if (score[spos]&128)
				channelvol[channel]=score[++spos];
			spos++;
			event->data[2]=channelvol[channel];
			break;
		case 2:
			event->data[0]=channel|0xe0;
			event->data[1]=(score[spos]<<7)&0x7f;
			event->data[2]=score[spos++]>>7;
			break;
		case 3:
			event->data[0]=channel|0xb0;
			event->data[1]=XLateMUSControl(score[spos++]);
			event->data[2]=0;
			break;
		case 4:
			if (score[spos])
			{
				event->data[0]=channel|0xb0;
				event->data[1]=MidiControlers[score[spos++]];
				event->data[2]=score[spos++];
			}
			else
			{
				event->data[0]=channel|0xc0;
				spos++;
				event->data[1]=score[spos++];
				event->data[2]=64;
			}
			break;
		default:
			finished=true;
			break;
		}
		if (finished)
			break;

		event++;
		count--;
		if (count<0)
			I_Error("Overflow");
		if (delta==-1)
		{
			delta=0;
			while (score[spos]&128)
			{
				delta<<=7;
				delta+=score[spos++]&127;
			}
			delta+=score[spos++];
		}
	}
}

//
// MUSIC API.
//



void I_InitMusic(void)
{
	MMRESULT	rc;
    int imidiMax, imidiCur, imidiOutput, imidiTonebank, imidiTonebankDrum;
    BOOL      fFoundOutput       = FALSE;
    BOOL      fFoundTonebank     = FALSE;
    BOOL      fTemp              = TRUE;
    int numdev;

	if (M_CheckParm("-nomusic"))
		return;

    imidiMax = midiOutGetNumDevs();
    if (imidiMax == 0) return;

    // Enumerate the devices, finding the first sequencing device and the first tonebank device
    for (imidiCur = 0; (!fFoundOutput || !fFoundTonebank) && (imidiCur < imidiMax); imidiCur++)
    {
        MIDIOUTCAPS moc;

        // Query the MIDI subsystem for the device capabilities
        if( midiOutGetDevCaps(imidiCur, &moc, sizeof(moc)) != MMSYSERR_NOERROR ) return;

        // Check to see if this device understands MIDI sequences
        if (moc.dwSupport & MIDICAPS_STREAM)
        {
            // If it does, and we still need one of those, remember it
            if (!fFoundOutput)
            {
                imidiOutput = imidiCur;
                fFoundOutput = TRUE;
            }
        }
        else
        {
            // If it does, and we still need a tonebank device, remember it
            if (!fFoundTonebank)
            {
                imidiTonebank = imidiCur;
                fFoundTonebank = TRUE;
            }
        }
    }

    // By the time we get here, we should have one of each
    if (!fFoundOutput || !fFoundTonebank) return;

    // Open the MIDI device for playing the sequence
    if( midiStreamOpen(&hMidiStream, &imidiOutput, 1, 0, (DWORD)NULL, CALLBACK_NULL) != MMSYSERR_NOERROR ) return;
/*
    // Get the initial tempo for the port, so we can calculate the length of the
    // MIDI sequence (in case the sequence doesn't have a tempo change meta-event
    mpt.cbStruct = sizeof(mpt);
    if( midiStreamProperty(hMidiStream, (LPBYTE)&mpt, MIDIPROP_GET | MIDIPROP_TEMPO) != MMSYSERR_NOERROR ) return;

    // Set the MIDI stream to receive SMF format rather than the Windows default MIDIEVENT format
    if( midiStreamProperty(hMidiStream, (LPBYTE)&fTemp, MIDIPROP_SET | MIDIPROP_SMF) != MMSYSERR_NOERROR ) return;
*/


    // Set the MIDI stream to map program changes to the General MIDI tonebanks
    if( midiStreamProperty(hMidiStream, (LPBYTE)&fTemp, MIDIPROP_SET | MIDIPROP_GENERALMIDI) != MMSYSERR_NOERROR ) return;


    // Open a tonebank MIDI out port
    if( midiOutOpen(&hmo, imidiTonebank, (DWORD)NULL, (DWORD)NULL, 0) != MMSYSERR_NOERROR ) return;

    // Load the tonebank into memory
    if (!LoadTonebank(TEXT("test_tonebank"), &mhTonebank)) return;
//    if (!LoadTonebank(TEXT("MUSIC_TONEBANK"), &mhTonebank)) return;

    // Copy tonebank to sound RAM
    if( midiOutPrepareHeader(hmo, &mhTonebank, sizeof(mhTonebank)) != MMSYSERR_NOERROR ) return;

    // Set tonebank
    mhTonebank.dwFlags |= MHDR_GENERALMIDI;
    if( midiOutLongMsg(hmo, &mhTonebank, sizeof(mhTonebank)) != MMSYSERR_NOERROR ) return;


    // Convert to 32-byte aligned, so that it can be DMA'ed.  Note that in real life, this 
    // may not gain you anything.  That is, if you've already got a perfectly good pointer
    // to your tonebank data that you could use, you might waste more time aligning it,
    // preparing for DMA'ing, and then going through the thread blocking and switching so
    // that something else can run.  This is especially true for smaller blocks, but might
    // even be true for large ones.  Don't assume DMA will always win.  It is done here
    // simply to demonstrate one way to ensure that DMA is being used

    /*
    // Allocate a 32-byte aligned memory block and copy the tonebank to it
    pbTonebankNew = AllocAligned(mhTonebank.dwBufferLength, 32);
    if (pbTonebankNew == NULL) return;

    memcpy(pbTonebankNew, mhTonebank.lpData, mhTonebank.dwBufferLength);
    mhTonebank.lpData = (char*)pbTonebankNew;

    // Allocate a 32-byte aligned memory block and copy the tonebank to it
    pbTonebankDrumNew = AllocAligned(mhTonebankDrum.dwBufferLength, 32);
    if (pbTonebankDrumNew == NULL) return;

    memcpy(pbTonebankDrumNew, mhTonebankDrum.lpData, mhTonebankDrum.dwBufferLength);
    mhTonebankDrum.lpData = (char*)pbTonebankDrumNew;

...

    // Now that the tonebanks are in the sound RAM, we no longer need the copies in system RAM
    //FreeAligned(pbTonebankNew);
    //FreeAligned(pbTonebankDrumNew);
    pbTonebankNew = pbTonebankDrumNew = NULL;

    */

    // Open a tonebank MIDI out port for the drums
    imidiTonebankDrum = imidiTonebank + 1;
    if( midiOutOpen(&hmoDrum, imidiTonebankDrum, (DWORD)NULL, (DWORD)NULL, 0) != MMSYSERR_NOERROR ) return;


    // Load the tonebank into memory
    if (!LoadTonebank(TEXT("test_drums"), &mhTonebankDrum)) return;

    // Copy drum tonebank to sound RAM
    if( midiOutPrepareHeader(hmoDrum, &mhTonebankDrum, sizeof(mhTonebankDrum)) != MMSYSERR_NOERROR ) return;

    // Set drum tonebank
    mhTonebankDrum.dwFlags |= (MHDR_GENERALMIDI | MHDR_GMDRUM);
    if( midiOutLongMsg(hmoDrum, &mhTonebankDrum, sizeof(mhTonebankDrum)) != MMSYSERR_NOERROR ) return;

	started=false;

}

void I_ShutdownMusic(void)
{
    I_StopSong( (int)CurrentSong );

    // Clean up
    if (hmo != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the tonebank
        if (mhTonebank.dwFlags & MHDR_PREPARED) midiOutUnprepareHeader(hmo, &mhTonebank, sizeof(mhTonebank));

        // If we allocated a new block of RAM for the tonebank, free it
        if (pbTonebankNew != NULL)  LocalFree(pbTonebankNew);

        // Close the MIDI out port.  This is very important; if all ports are not closed before 
        // the program exits, no other Dreamcast program will be able to use *any* audio
        midiOutClose(hmo);
    }

    if (hmoDrum != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the tonebank
        if (mhTonebankDrum.dwFlags & MHDR_PREPARED) midiOutUnprepareHeader(hmoDrum, &mhTonebankDrum, sizeof(mhTonebankDrum));

        // If we allocated a new block of RAM for the tonebank, free it
        if (pbTonebankDrumNew != NULL) LocalFree(pbTonebankDrumNew);

        // Close the MIDI stream port.  See warning above about what happens if
        // all the ports that have been opened are not closed before program exit
        midiOutClose(hmoDrum);
    }

	if (hMidiStream)
	{
		midiStreamStop(hMidiStream);
		started=false;
		midiStreamClose(hMidiStream);
		hMidiStream=NULL;
	}


}

void I_PlaySong(int handle, int looping)
{
	if (!(handle&&hMidiStream))
		return;
	loopsong=looping;
	CurrentSong=(songinfo_t *)handle;
}

void I_PauseSong (int handle)
{
	if (!hMidiStream)
		return;
	midiStreamPause(hMidiStream);
}

void I_ResumeSong (int handle)
{
	if (!hMidiStream)
		return;
	midiStreamRestart(hMidiStream);
}

void I_StopSong(int handle)
{
	songinfo_t	*song;
	int			i;

	if (!(handle&&hMidiStream))
		return;

	loopsong=false;
	midiStreamStop(hMidiStream);
	midiOutReset((HMIDIOUT)hMidiStream);
	started=false;

	song=(songinfo_t *)handle;
	for (i=0;i<2;i++)
	{
		if (song->header[i].lpData)
		{
			midiOutUnprepareHeader((HMIDIOUT)hMidiStream, &song->header[i], sizeof(MIDIHDR));
			song->header[i].lpData=NULL;
			song->header[i].dwFlags=MHDR_DONE|MHDR_ISSTRM;
		}
	}
	song->nextevent=0;
	if (song==CurrentSong)
		CurrentSong=NULL;
}

void I_UnRegisterSong(int handle)
{
	songinfo_t	*song;

	if (!(handle&&hMidiStream))
		return;

	I_StopSong(handle);

	song=(songinfo_t *)handle;
	free(song->midievents);
	free(song);
}

int I_RegisterSong(void* data)
{
	songinfo_t	*song;
	int			i;

	if (!hMidiStream)
		return(0);
	song=(songinfo_t *)malloc(sizeof(songinfo_t));
	song->numevents=GetSongLength((byte *)data);
	song->nextevent=0;
	song->midievents=(MidiEvent_t *)malloc(song->numevents*sizeof(MidiEvent_t));
	Mus2Midi((byte *)data, song->midievents);
	for (i=0;i<2;i++)
	{
		song->header[i].lpData=NULL;
		song->header[i].dwFlags=MHDR_ISSTRM|MHDR_DONE;
	}
	return((int)song);
}

// Is the song playing?
int I_QrySongPlaying(int handle)
{
	if (CurrentSong)
		return(true);
	else
		return(false);
}

void I_SetMusicVolume(int volume)
{
    WORD wVolume = snd_MusicVolume * 4369;

	snd_MusicVolume = volume;
	if (!hMidiStream) return;

    // Now set volume on output device.
    midiOutSetVolume( (HMIDIOUT)hMidiStream, wVolume|(wVolume<<32) );
}

void I_ProcessMusic(void)
{
	LPMIDIHDR	header;
	int			length;
//	int			i;
	MMRESULT	rc;

	if (!CurrentSong)
		return;

//	for (i=0;i<1;i++)
//	{
//		header=&CurrentSong->header[i];
    	header=CurrentSong->header;
		if (header->dwFlags&MHDR_DONE)
		{
			if (header->lpData)
				midiOutUnprepareHeader((HMIDIOUT)hMidiStream, header, sizeof(MIDIHDR));
			header->lpData=(void *)&CurrentSong->midievents[CurrentSong->nextevent];
			length=CurrentSong->numevents-CurrentSong->nextevent;
			if (length>MAX_MIDI_EVENTS)
			{
				length=MAX_MIDI_EVENTS;
				CurrentSong->nextevent+=MAX_MIDI_EVENTS;
			}
			else
				CurrentSong->nextevent=0;
                
            mptd.cbStruct = sizeof(mptd);
            mptd.dwTimeDiv = 70;//23;//89;
            midiStreamProperty(hMidiStream, (LPBYTE)&mptd, MIDIPROP_SET | MIDIPROP_TIMEDIV);              

            length*=sizeof(MidiEvent_t);
			header->dwBufferLength=length;
			header->dwBytesRecorded=length;
			header->dwFlags=MHDR_ISSTRM;
			rc=midiOutPrepareHeader((HMIDIOUT)hMidiStream, header, sizeof(MIDIHDR));
			if (rc!=MMSYSERR_NOERROR) I_Error("midiOutPrepareHeader Failed");
			if (!started)
			{
                I_SetMusicVolume( snd_MusicVolume );
				rc=midiStreamRestart(hMidiStream);
			    if (rc!=MMSYSERR_NOERROR) I_Error("midiStreamRestart Failed");
				started=true;
			}
			rc=midiStreamOut(hMidiStream, header, sizeof(MIDIHDR));
			if (rc!=MMSYSERR_NOERROR) I_Error("midiStreamOut Failed");
		}
//	}
}
